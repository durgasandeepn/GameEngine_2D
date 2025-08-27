/****************************************************************
// File Name: MainMenu
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: A scene for the main menu. Handles moving to the lobby,
// moving to settings or credits, or quitting the game.
****************************************************************/

#include "precompiled.h"
#include "MainMenu.h"
#include "Managers/GlobalSoundManager.h"
#include "CreditsScene.h"

MainMenu::MainMenu(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void MainMenu::Initialize()
{
	if (!GlobalSoundManager::Instance().GetHasInit()) {
		GlobalSoundManager::Instance().Init();
	}
	GlobalSoundManager::Instance().PauseBGM();
	GlobalSoundManager::Instance().PauseEnv();
	GlobalSoundManager::Instance().PlayBGM("RPG_Dungeon.mp3");
	
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("basicOrthoCamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto background = GameResourceManager::Instance().CreateAndAddGameObject("UI/mainmenubackground.json", *sceneGraph);
	if (!background) {
		std::cerr << "Failed to create background" << std::endl;
	};
	background->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	background->SetLocalScale(Vector3(40.0f, 22.0f, 0.0f));

	auto loveWizardsLogo = GameResourceManager::Instance().CreateAndAddGameObject("UI/lovewizards.json", *sceneGraph);
	if (!loveWizardsLogo) {
		std::cerr << "Failed to create loveWizardsLogo" << std::endl;
	};
	loveWizardsLogo->SetLocalPosition(Vector3(0.0f, 5.0f, 0.0f));
	loveWizardsLogo->SetLocalScale(Vector3(10, 5, 0.0f));

	auto buttonManager = GameResourceManager::Instance().CreateAndAddGameObject("UI/mainmenubuttonmanager.json", *sceneGraph);
	if (!buttonManager) {
		std::cerr << "Failed to create buttonManager" << std::endl;
	};

	// This is if we've gotten to the main menu after beating the game
	if (GameManager::Instance().GetReachedTheEnd()) {
		Scene::Update(1.0f);
		SceneManager::Instance().PushScene<CreditsScene>("Credits");
	}
}

void MainMenu::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MainMenu::OnEnter()
{
}

void MainMenu::OnExit()
{
}

void MainMenu::OnResume()
{
}

void MainMenu::OnPause()
{
}
