/****************************************************************
// File Name: Lobby
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A scene for the lobby. Allows up to 4 players to join
// the game and select their character.
****************************************************************/
#pragma once

#include "SceneManagement/Scene.h"
#include "Object/GameObject.h"

class Lobby : public Scene {
public:
	Lobby(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
};