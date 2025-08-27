/****************************************************************
// File Name: Imgui Wrapper
// © 2025 DigiPen (USA) Corporation
// Authors: Durga Sandeep (Debug window core), Jacob Wilburn (Implementation of Cheat Codes)
// Description: Handles the debug window using Imgui
****************************************************************/

#pragma once
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include"Imgui/imgui.h"
#include"Imgui/imgui_impl_opengl3.h"
#include"Imgui/imgui_impl_glfw.h"


class ImguiWrapper
{
public:

	static ImguiWrapper& Instance() {
		static ImguiWrapper instance;
		return instance;
	}

	bool Initialize(GLFWwindow* window);
	void NewFrameSetup();
	void SetElements( );
	void RenderCall();
	void Clear();

	void PhysicsDebug();
	void FPSDebug();
	void QuitMethod();
	void SetGodMode();
	void TurnOffGodMode();
	void ToggleInstantKill();
	void RenderUI_Test();


	void SetDebugWindow();


private:
	ImguiWrapper() = default;
	~ImguiWrapper();

	bool windowNeeded;
	bool godMode = false;
	bool bgmPaused = false;

	float ImGuiWidth = 100.f;
	float ImGuiHeight = 100.f;
	bool enableDebugCall = false;
	ImFont* FontLoaded = nullptr;  
};
