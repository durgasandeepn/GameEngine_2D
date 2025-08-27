/****************************************************************
// File Name: PauseScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A scene for pausing the game. Handles moving
// between other pause menu related scenes, and pauses the game.
****************************************************************/

#pragma once
#include "SceneManagement/Scene.h"

class PauseScene : public Scene
{
public:
	PauseScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;

private:
	GameObject* pauseUI;
};

