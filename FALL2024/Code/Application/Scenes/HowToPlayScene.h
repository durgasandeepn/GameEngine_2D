/****************************************************************
// File Name: HowToPlayScene
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: A scene for showing how to play the game
****************************************************************/

#pragma once
#include "SceneManagement/Scene.h"

class HowToPlayScene : public Scene
{
public:
	HowToPlayScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
};