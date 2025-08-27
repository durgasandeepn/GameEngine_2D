/****************************************************************
// File Name: FmodSplashScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: The scene that shows a splash image of FMOD
****************************************************************/

#pragma once
#include "SplashScene.h"

class FmodSplashScene : public SplashScene {
public:
	FmodSplashScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
	void GoToNextScene() override;
};
