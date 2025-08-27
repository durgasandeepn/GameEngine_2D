/****************************************************************
// File Name: QuitConfirmationScene
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A scene that asks the player if they're sure they
// want to quit. Allows them to cancel the operation if they didn't
// mean to press it.
****************************************************************/

#include "precompiled.h"
#include "QuitConfirmationScene.h"
#include "Managers/GameResourceManager.h"

QuitConfirmationScene::QuitConfirmationScene(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void QuitConfirmationScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto quitconfirmationUI = GameResourceManager::Instance().CreateAndAddGameObject("UI/QuitConfirmation/quitconfirmation.json", *sceneGraph);
	if (!quitconfirmationUI) {
		std::cerr << "Failed to create quitconfirmationUI" << std::endl;
	};
}

void QuitConfirmationScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void QuitConfirmationScene::OnEnter()
{
}

void QuitConfirmationScene::OnExit()
{
}

void QuitConfirmationScene::OnResume()
{
}

void QuitConfirmationScene::OnPause()
{
}
