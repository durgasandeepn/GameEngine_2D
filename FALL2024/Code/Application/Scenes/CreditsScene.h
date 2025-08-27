/****************************************************************
// File Name: CreditsScene
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: The scene that shows all the credits for the game
****************************************************************/

#pragma once
#include "SceneManagement/Scene.h"
#include "Object/GameObject.h"
#include "Managers/GameManager.h"

class CreditsScene : public Scene {
public:
	CreditsScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
};