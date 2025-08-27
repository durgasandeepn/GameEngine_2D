/****************************************************************
// File Name: CreditsScene
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: The scene that shows all the credits for the game
****************************************************************/

#include "precompiled.h"
#include "CreditsScene.h"

CreditsScene::CreditsScene(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void CreditsScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto menu = GameResourceManager::Instance().CreateAndAddGameObject("UI/Credits/creditsmenu.json", *sceneGraph);
	if (!menu) {
		std::cerr << "Failed to create menu" << std::endl;
	};
}

void CreditsScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void CreditsScene::OnEnter()
{
}

void CreditsScene::OnExit()
{
}

void CreditsScene::OnResume()
{
}

void CreditsScene::OnPause()
{
}
