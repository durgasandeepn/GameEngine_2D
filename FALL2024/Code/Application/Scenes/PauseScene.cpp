/****************************************************************
// File Name: PauseScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A scene for pausing the game. Handles moving
// between other pause menu related scenes, and pauses the game.
****************************************************************/

#include "precompiled.h"
#include "PauseScene.h"
#include "Managers/GameResourceManager.h"
#include "Managers/GameManager.h"

PauseScene::PauseScene(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void PauseScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};
	
	pauseUI = GameResourceManager::Instance().CreateAndAddGameObject("UI/pausemenu.json", *sceneGraph);
	if (!pauseUI) {
		std::cerr << "Failed to create pauseUI" << std::endl;
	};
	pauseUI->SetIsActive(true);
}

void PauseScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void PauseScene::OnEnter()
{
}

void PauseScene::OnExit()
{
}

void PauseScene::OnResume()
{
}

void PauseScene::OnPause()
{
}
