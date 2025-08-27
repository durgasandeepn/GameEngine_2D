/****************************************************************
// File Name: SettingsScene
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: A scene dedicated to settings. Handles the logic for
// the settings menu both within the main menu and pause menu
****************************************************************/

#pragma once
#include "SceneManagement/Scene.h"
#include "Object/GameObject.h"
#include "Managers/GameManager.h"

class SettingsScene : public Scene {
public:
	SettingsScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
};