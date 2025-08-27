/****************************************************************
// File Name: MainMenu
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: A scene for the main menu. Handles moving to the lobby,
// moving to settings or credits, or quitting the game.
****************************************************************/

#pragma once
#include "SceneManagement/Scene.h"
#include "Object/GameObject.h"
#include "Managers/GameManager.h"

class MainMenu : public Scene {
public:
	MainMenu(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
};