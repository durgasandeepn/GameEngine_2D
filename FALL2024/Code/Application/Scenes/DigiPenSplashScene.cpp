/****************************************************************
// File Name: DigiPenSlashScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: The scene that shows a splash image of the DigiPen logo
****************************************************************/

#include "precompiled.h"
#include "DigiPenSplashScene.h"
#include "Managers/GameResourceManager.h"
#include "Scenes/FmodSplashScene.h"

DigiPenSplashScene::DigiPenSplashScene(const std::string& name)
	:SplashScene(name)
{

}

void DigiPenSplashScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto background = GameResourceManager::Instance().CreateAndAddGameObject("UI/SplashScene/digiPenSplash.json", *sceneGraph);
	if (!background) {
		std::cerr << "Failed to create background" << std::endl;
	};
}

void DigiPenSplashScene::Update(float deltaTime)
{
	SplashScene::Update(deltaTime);
}

void DigiPenSplashScene::OnEnter()
{
}

void DigiPenSplashScene::OnExit()
{
}

void DigiPenSplashScene::OnResume()
{
}

void DigiPenSplashScene::OnPause()
{

}

void DigiPenSplashScene::GoToNextScene()
{
	TransitionManager::Instance().QueueSceneChange<FmodSplashScene>("FmodSplashScene.h");
}
