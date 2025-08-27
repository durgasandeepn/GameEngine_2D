/****************************************************************
// File Name: DigiPenSlashScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: The scene that shows a splash image of the DigiPen logo
****************************************************************/

#pragma once
#include "SplashScene.h"

class DigiPenSplashScene : public SplashScene {
public:
	DigiPenSplashScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
	void GoToNextScene() override;
};

