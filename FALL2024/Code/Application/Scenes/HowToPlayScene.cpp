/****************************************************************
// File Name: HowToPlayScene
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: A scene for showing how to play the game
****************************************************************/

#include "precompiled.h"
#include "HowToPlayScene.h"
#include "Managers/GameResourceManager.h"

HowToPlayScene::HowToPlayScene(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void HowToPlayScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto howtoplayUI = GameResourceManager::Instance().CreateAndAddGameObject("UI/HowToPlay/howtoplay.json", *sceneGraph);
	if (!howtoplayUI) {
		std::cerr << "Failed to create howtoplayUI" << std::endl;
	};
}

void HowToPlayScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void HowToPlayScene::OnEnter()
{
}

void HowToPlayScene::OnExit()
{
}

void HowToPlayScene::OnResume()
{
}

void HowToPlayScene::OnPause()
{
}
