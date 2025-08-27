/****************************************************************
// File Name: GameWindow
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Internal reference to a GLFW window. 
// Mostly handles calling GLFW window api functions
****************************************************************/

#pragma once

#include <glfw3.h>
#include <string>
#include <stdexcept>
#include <functional>
#include <iostream>

enum class Resolution {
	R_1280x720,
	R_1600x900,
	R_1920x1080,
	/*R_2560x1440,
	R_3840x2160*/
};

class GameWindow
{
public:
	GameWindow(int width, int height, const std::string& title);

	~GameWindow();

	bool ShouldClose() const;

	void PollEvents();

	GLFWwindow* GetNativeWindow() const;

	void SetWindowHints(const std::function<void()>& hintSetter);

	int GetWidth() const;
	int GetHeight() const;
	void SetWidth(int newWidth) { width = newWidth; }
	void SetHeight(int newHeeight) { height = newHeeight; }
	std::string GetTitle() const { return title; }

	void SetResizeCallback(std::function<void(GLFWwindow*, int, int)> callback);

	void SetWindowTitle(std::string& title);

	void SetIsFullscreen(bool newIsFullscreen);
	void SetResolution(Resolution res);
	bool IsFullscreen() const { return isFullscreen; }

	inline std::pair<int, int> GetResolutionDimensions(Resolution res) {
		switch (res) {
		case Resolution::R_1280x720: return { 1280, 720 };
		case Resolution::R_1600x900: return { 1600, 900 };
		case Resolution::R_1920x1080: return { 1920, 1080 };
		//case Resolution::R_2560x1440: return { 2560, 1440 };
		//case Resolution::R_3840x2160: return { 3840, 2160 };
		default: return { 1280, 720 };
		}
	}
	bool IsWindowMinimized();
private:
	// This is what the resolution of the game currently is. Can be
	// any resolution which we will then bump to our intended resolution
	int width;
	int height;
	std::string title;
	GLFWwindow* pWindow;
	std::function<void(GLFWwindow*, int, int)> resizeCallback;
	bool isFullscreen = true;

	GLFWmonitor* monitor;
	const GLFWvidmode* mode;

	void Initialize();
	void Shutdown();

	static void ResizeCallbackWrapper(GLFWwindow* pWindow, int width, int height);
};