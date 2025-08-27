/****************************************************************
// File Name: ControllerScreenScene
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: The scene that shows a splash image of the controller recommendation
****************************************************************/

#include "precompiled.h"
#include "ControllerScreenScene.h"
#include "Managers/GameResourceManager.h"
#include "Scenes/MainMenu.h"

ControllerScreenScene::ControllerScreenScene(const std::string& name)
	:SplashScene(name)
{

}

void ControllerScreenScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto background = GameResourceManager::Instance().CreateAndAddGameObject("UI/SplashScene/controllerscreen.json", *sceneGraph);
	if (!background) {
		std::cerr << "Failed to create background" << std::endl;
	};
}

void ControllerScreenScene::Update(float deltaTime)
{
	SplashScene::Update(deltaTime);
}

void ControllerScreenScene::OnEnter()
{
}

void ControllerScreenScene::OnExit()
{
}

void ControllerScreenScene::OnResume()
{
}

void ControllerScreenScene::OnPause()
{

}

void ControllerScreenScene::GoToNextScene()
{
	TransitionManager::Instance().QueueSceneChange<MainMenu>("MainMenu");
}
