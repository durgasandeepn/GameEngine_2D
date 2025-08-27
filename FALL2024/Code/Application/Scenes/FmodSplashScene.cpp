/****************************************************************
// File Name: FmodSplashScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: The scene that shows a splash image of FMOD
****************************************************************/

#include "precompiled.h"
#include "FmodSplashScene.h"
#include "Managers/GameResourceManager.h"
#include "Scenes/ControllerScreenScene.h"

FmodSplashScene::FmodSplashScene(const std::string& name)
	:SplashScene(name)
{

}

void FmodSplashScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto background = GameResourceManager::Instance().CreateAndAddGameObject("UI/SplashScene/fModSplash.json", *sceneGraph);
	if (!background) {
		std::cerr << "Failed to create background" << std::endl;
	};
}

void FmodSplashScene::Update(float deltaTime)
{
	SplashScene::Update(deltaTime);
}

void FmodSplashScene::OnEnter()
{
}

void FmodSplashScene::OnExit()
{
}

void FmodSplashScene::OnResume()
{
}

void FmodSplashScene::OnPause()
{

}

void FmodSplashScene::GoToNextScene()
{
	TransitionManager::Instance().QueueSceneChange<ControllerScreenScene>("ControllerScreenScene");
}
