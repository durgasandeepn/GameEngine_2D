/****************************************************************
// File Name: Renderer
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: System for rendering entities to the screen in 2D.
****************************************************************/

#include "precompiled.h"
#include "Renderer.h"

void APIENTRY openglCallbackFunction(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam)
{
    std::string sourceStr;
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             sourceStr = "API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           sourceStr = "Other"; break;
    }

    std::string typeStr;
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               typeStr = "Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Undefined Behavior"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              typeStr = "Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               typeStr = "Other"; break;
    }

    std::string severityStr;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         severityStr = "High"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "Medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          severityStr = "Low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification"; break;
    }

    std::cerr << "OpenGL Debug Message\n"
        << "Source: " << sourceStr << "\n"
        << "Type: " << typeStr << "\n"
        << "ID: " << id << "\n"
        << "Severity: " << severityStr << "\n"
        << "Message: " << message << std::endl;
}

Renderer::Renderer(GameWindow& window) : pWindow(window)
{
	Initialize();
	SetupCallbacks();
}

void Renderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffers()
{
	glfwSwapBuffers(pWindow.GetNativeWindow());
}

void Renderer::Draw(unsigned int dataCount, GLenum drawingMode, bool indexed)
{
	if (indexed)
	{
		glDrawElements(drawingMode, dataCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(drawingMode, 0, dataCount);
	}

    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error after draw: " << std::hex << err << std::endl;
    }
}

void Renderer::Initialize()
{
    [[maybe_unused]] int success; // Handles whether we succeed or fail in initialization
	[[maybe_unused]] char infoLog[512]; // Stores error messages if any

	pWindow.SetWindowHints([]() // Lambda expression (callable)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			// Explicitly use core profile. Gain access to smaller subest of OpenGL features
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		});

	glfwMakeContextCurrent(pWindow.GetNativeWindow());

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW.");
	}

    // Enable debug
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Makes sure errors are reported immediately
    glDebugMessageCallback(openglCallbackFunction, nullptr);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, pWindow.GetWidth(), pWindow.GetHeight());
}

void Renderer::SetupCallbacks()
{
	pWindow.SetResizeCallback([this](GLFWwindow* window, int width, int height)
		{
			this->FrameBufferSizeCallback(window, width, height);
		});
}

void Renderer::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	// Additional rendering adjustments can be made here
}
