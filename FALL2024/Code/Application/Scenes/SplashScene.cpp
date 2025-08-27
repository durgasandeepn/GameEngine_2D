/****************************************************************
// File Name: SplashScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A base scene for splash screens that contains
// a transition in and out effect
****************************************************************/

#include "precompiled.h"
#include "SplashScene.h"
#include "Input/Input.h"
#include "Managers/TransitionManager.h"
#include "Managers/GameResourceManager.h"
SplashScene::SplashScene(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void SplashScene::Initialize()
{

}

void SplashScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	if (!doneCountDown)
	{
		if (Input::Instance().IsKeyPressed(KeyCode::Space) ||
			Input::Instance().IsKeyPressed(KeyCode::Enter) ||
			Input::Instance().IsKeyPressed(KeyCode::Escape) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 0) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 1) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 2) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 3) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 0) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 1) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 2) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 3) ||
			Input::Instance().IsMouseButtonPressed(MouseButton::Left) ||
			Input::Instance().IsMouseButtonPressed(MouseButton::Right))
		{
			countToChangeScene = 0;
		}

		countToChangeScene -= deltaTime;

		if (countToChangeScene <= 0)
		{
			doneCountDown = true;
			GoToNextScene();
		}
	}
}

void SplashScene::OnEnter()
{
}

void SplashScene::OnExit()
{
}

void SplashScene::OnResume()
{
}

void SplashScene::OnPause()
{
}

void SplashScene::GoToNextScene()
{

}
