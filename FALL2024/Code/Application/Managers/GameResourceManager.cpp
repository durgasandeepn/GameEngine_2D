/****************************************************************
// File Name: GameResourceManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez (Base code), Alex Humphries (Refactoring code)
// Description: External system for adding Objects (and other entities) to a game world.
****************************************************************/

#include "precompiled.h"
#include "GameResourceManager.h"

void GameResourceManager::Initialize()
{
	ComponentCreator::Instance().RegisterComponent<MovementComponent2D>("MovementComponent2D");
	ComponentCreator::Instance().RegisterComponent<PlaySoundComponent>("PlaySoundComponent");
	ComponentCreator::Instance().RegisterComponent<BulletComponent>("BulletComponent");
	ComponentCreator::Instance().RegisterComponent<PlayBGMComponent>("PlayBGMComponent");
	ComponentCreator::Instance().RegisterComponent<CameraMovementComponent>("CameraMovementComponent");
	ComponentCreator::Instance().RegisterComponent<EnemyComponent>("EnemyComponent");
	ComponentCreator::Instance().RegisterComponent<PlayerLobbyComponent>("PlayerLobbyComponent");
	ComponentCreator::Instance().RegisterComponent<LobbyManagerComponent>("LobbyManagerComponent");
	ComponentCreator::Instance().RegisterComponent<MainMenuComponent>("MainMenuComponent");
	ComponentCreator::Instance().RegisterComponent<PauseMenuComponent>("PauseMenuComponent");
	ComponentCreator::Instance().RegisterComponent<TransitionComponent>("TransitionComponent");
	ComponentCreator::Instance().RegisterComponent<QuitConfirmationComponent>("QuitConfirmationComponent");
	ComponentCreator::Instance().RegisterComponent<SettingsMenuComponent>("SettingsMenuComponent");
	ComponentCreator::Instance().RegisterComponent<HowToPlayComponent>("HowToPlayComponent");
	ComponentCreator::Instance().RegisterComponent<CreditsMenuComponent>("CreditsMenuComponent");
}

GameObject* GameResourceManager::CreateGameObject(const std::string& filename)
{
	auto gameObject = ResourceManager::Instance().LoadGameObjectFromJSON(filename);

	if (!gameObject)
		return nullptr;

	ConfigureGameObject(gameObject);
	return gameObject;
}

GameObject* GameResourceManager::CreateAndAddGameObject(const std::string& filename, SceneGraph& sceneGraph)
{
	auto gameObject = ResourceManager::Instance().LoadGameObjectFromJSON(filename);

	if (!gameObject)
		return nullptr;

	ConfigureGameObject(gameObject);
	sceneGraph.AddNode(gameObject);
	return gameObject;
}

std::shared_ptr<Material> GameResourceManager::CreateMaterial(const std::string& shaderPath, const std::string& texturePath)
{
	std::shared_ptr<Shader> shader = ResourceManager::Instance().LoadShader(shaderPath);
	std::shared_ptr<Texture> tex = ResourceManager::Instance().LoadTexture(texturePath);

	return std::make_shared<Material>(shader, tex);
}

void GameResourceManager::ConfigureGameObject(GameObject* gameObject)
{
	// Configure Game-Specific Components
	// Set up here anything that can't be done on initialize, i.e., passing in systems
	if (auto moveComp = gameObject->FindComponent<MovementComponent2D>()) {
		// Set movement specific properties
	}
}
