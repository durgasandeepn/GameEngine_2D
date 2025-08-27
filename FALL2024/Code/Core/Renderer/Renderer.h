/****************************************************************
// File Name: Renderer
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: System for rendering entities to the screen in 2D.
****************************************************************/

#pragma once

#include <glew.h>
#include <glfw3.h>
#include <gl/GL.h>
#include "GameWindow.h"
#include "Math/Vector3.h"
#include "Math/Matrix4.h"

class Renderer
{
public:
	Renderer(GameWindow& window);

	// Delete copy and assign constructors
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	// Handles drawing everything stored in our buffers
	void Draw(unsigned int dataCount, GLenum drawingMode, bool indexed);

	GameWindow& GetWindowPtr() { return pWindow; }

private:
	GameWindow& pWindow;

	void Initialize();
	void SetupCallbacks();
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};