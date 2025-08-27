/****************************************************************
// File Name: SettingsScene
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: A scene dedicated to settings. Handles the logic for
// the settings menu both within the main menu and pause menu
****************************************************************/

#include "precompiled.h"
#include "SettingsScene.h"

SettingsScene::SettingsScene(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void SettingsScene::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	/*auto background = GameResourceManager::Instance().CreateAndAddGameObject("UI/mainmenubackground.json", *sceneGraph);
	if (!background) {
		std::cerr << "Failed to create background" << std::endl;
	};
	background->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	background->SetLocalScale(Vector3(40.0f, 35.0f, 0.0f));

	auto settingsText = GameResourceManager::Instance().CreateAndAddGameObject("UI/lovewizards.json", *sceneGraph);
	if (!settingsText) {
		std::cerr << "Failed to create settingsText" << std::endl;
	};
	settingsText->SetLocalPosition(Vector3(0.0f, 5.0f, 0.0f));
	settingsText->SetLocalScale(Vector3(10, 5, 0.0f));

	auto buttonManager = GameResourceManager::Instance().CreateAndAddGameObject("UI/Settings/settingsbuttonmanager.json", *sceneGraph);
	if (!buttonManager) {
		std::cerr << "Failed to create buttonManager" << std::endl;
	};*/

	auto* menu = GameResourceManager::Instance().CreateAndAddGameObject("UI/Settings/settingsmenu.json", *sceneGraph);
	if (!menu) {
		std::cerr << "Failed to create menu" << std::endl;
	};
}

void SettingsScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void SettingsScene::OnEnter()
{
}

void SettingsScene::OnExit()
{
}

void SettingsScene::OnResume()
{
}

void SettingsScene::OnPause()
{
}
