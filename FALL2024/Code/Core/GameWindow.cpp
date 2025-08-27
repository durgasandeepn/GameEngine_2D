/****************************************************************
// File Name: GameWindow
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Internal reference to a GLFW window.
// Mostly handles calling GLFW window api functions
****************************************************************/


#include "precompiled.h"
#include "GameWindow.h"
#include <stdexcept>
#include <iostream>
#include "stb_image.h"


GameWindow::GameWindow(int width, int height, const std::string& title)
	: width(width), height(height), title(title), pWindow(nullptr)
{
	Initialize();
}

GameWindow::~GameWindow()
{
	Shutdown();
}

bool GameWindow::ShouldClose() const
{
	return glfwWindowShouldClose(pWindow);
}

void GameWindow::PollEvents()
{
	glfwPollEvents();
}

GLFWwindow* GameWindow::GetNativeWindow() const
{
	return pWindow;
}

void GameWindow::SetWindowHints(const std::function<void()>& hintSetter)
{
	hintSetter();
}

int GameWindow::GetWidth() const
{
	return width;
}

int GameWindow::GetHeight() const
{
	return height;
}

// Sets the resize callback variable, maps the wrapper function for resize,
// then maps the context of the window pointer to this object
void GameWindow::SetResizeCallback(std::function<void(GLFWwindow*, int, int)> callback)
{
	resizeCallback = std::move(callback);
	glfwSetFramebufferSizeCallback(pWindow, ResizeCallbackWrapper);
	glfwSetWindowUserPointer(pWindow, this);
}

void GameWindow::SetWindowTitle(std::string& title)
{
	glfwSetWindowTitle(pWindow, title.c_str());
}

void GameWindow::SetIsFullscreen(bool newIsFullscreen)
{
	if (newIsFullscreen == isFullscreen) return;
	
	GLFWmonitor* monitor = newIsFullscreen ? glfwGetPrimaryMonitor() : nullptr;
	int xpos = newIsFullscreen ? 0 : 50;
	int ypos = newIsFullscreen ? 0 : 50;

	glfwSetWindowMonitor(pWindow, monitor, xpos, ypos, width, height, GLFW_DONT_CARE);
	
	isFullscreen = newIsFullscreen;
}

void GameWindow::SetResolution(Resolution res)
{
	auto [newWidth, newHeight] = GetResolutionDimensions(res);
	if (newWidth == width && newHeight == height)
		return; // No change

	width = newWidth;
	height = newHeight;

	GLFWmonitor* monitor = isFullscreen ? glfwGetPrimaryMonitor() : nullptr;

	glfwSetWindowSize(pWindow, width, height);

	if (resizeCallback) {
		resizeCallback(pWindow, width, height);
	}
}
bool GameWindow::IsWindowMinimized()
{
	return glfwGetWindowAttrib(pWindow, GLFW_ICONIFIED);
}

void GameWindow::Initialize()
{
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW.");
	}
	
	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);

	//width = mode->width;
	//height = mode->height;

	#ifdef _DEBUG
		pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	#else

		if (isFullscreen) {
			pWindow = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);
		}
		else {
			pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		}
	#endif
	glfwSwapInterval(1); // Enable v-sync
	if (!pWindow)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window.");
	}

	// Set the window icon.
	GLFWimage icon;
	icon.pixels = stbi_load("Assets/Textures/icon.png", &icon.width, &icon.height, nullptr, 4);
	if (icon.pixels)
	{
		glfwSetWindowIcon(pWindow, 1, &icon);
		stbi_image_free(icon.pixels);
	}
	else
	{
		std::cerr << "Failed to load window icon from Assets/Textures/icon.png" << std::endl;
	}

}

void GameWindow::Shutdown()
{
	if (pWindow)
	{
		glfwDestroyWindow(pWindow);
	}
	glfwTerminate();
}

void GameWindow::ResizeCallbackWrapper(GLFWwindow* window, int width, int height)
{
	auto* gameWindow = static_cast<GameWindow*> (glfwGetWindowUserPointer(window));
	if (gameWindow && gameWindow->resizeCallback)
	{
		gameWindow->SetWidth(width);
		gameWindow->SetHeight(height);
		gameWindow->resizeCallback(window, width, height);
		std::cout << "Window size: (" << width << ", " << height << ")" << std::endl;
	}
}