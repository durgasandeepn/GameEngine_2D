/****************************************************************
// File Name: ControllerScreenScene
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: The scene that shows a splash image of the controller recommendation
****************************************************************/

#pragma once
#include "SplashScene.h"

class ControllerScreenScene : public SplashScene {
public:
	ControllerScreenScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
	void GoToNextScene() override;
};
