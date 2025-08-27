/****************************************************************
// File Name: EndGameScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: The final scene of the game after you beat the boss
****************************************************************/

#pragma once
#include "SplashScene.h"
class EndGameScene :
    public SplashScene
{
public:
	EndGameScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
	void GoToNextScene() override;
};

