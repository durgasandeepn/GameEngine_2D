/****************************************************************
// File Name: EndGameScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: The final scene of the game after you beat the boss
****************************************************************/

#include "precompiled.h"
#include "EndGameScene.h"
#include "Managers/GameResourceManager.h"
#include "Scenes/MainMenu.h"
#include "Managers/GlobalSoundManager.h"

EndGameScene::EndGameScene(const std::string& name)
	:SplashScene(name)
{

}

void EndGameScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto background = GameResourceManager::Instance().CreateAndAddGameObject("UI/SplashScene/endgameScene.json", *sceneGraph);
	if (!background) {
		std::cerr << "Failed to create background" << std::endl;
	};

	GlobalSoundManager::Instance().Play("VolperSong.mp3");
}

void EndGameScene::Update(float deltaTime)
{
	SplashScene::Update(deltaTime);
}

void EndGameScene::OnEnter()
{
}

void EndGameScene::OnExit()
{
}

void EndGameScene::OnResume()
{
}

void EndGameScene::OnPause()
{

}

void EndGameScene::GoToNextScene()
{
	TransitionManager::Instance().QueueSceneChange<MainMenu>("MainMenu");
}
