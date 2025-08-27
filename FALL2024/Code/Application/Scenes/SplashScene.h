/****************************************************************
// File Name: SplashScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A base scene for splash screens that contains
// a transition in and out effect
****************************************************************/

#pragma once
#include "SceneManagement/Scene.h"

class SplashScene : public Scene
{
public:
	SplashScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;

	virtual void GoToNextScene();

	float countToChangeScene = 5.0f;
	bool doneCountDown = false;
};

