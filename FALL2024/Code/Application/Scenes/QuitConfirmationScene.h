/****************************************************************
// File Name: QuitConfirmationScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A scene that asks the player if they're sure they
// want to quit. Allows them to cancel the operation if they didn't
// mean to press it.
****************************************************************/

#pragma once
#include "SceneManagement/Scene.h"

class QuitConfirmationScene : public Scene
{
public:
	QuitConfirmationScene(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;
};