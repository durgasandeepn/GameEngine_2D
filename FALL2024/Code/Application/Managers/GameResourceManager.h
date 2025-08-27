/****************************************************************
// File Name: GameResourceManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez, Alex Humphries
// Description: External system for adding Objects (and other entities) to a game world.
****************************************************************/

#pragma once

#include "ResourceManagement/ResourceManager.h"
#include "Components/MovementComponent2D.h"
#include "Components/PlaySoundComponent.h"
#include "Components/BulletComponent.h"
#include "Components/PlayBGMComponent.h"
#include "Components/CameraMovementComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/PlayerLobbyComponent.h"
#include "Components/LobbyManagerComponent.h"
#include "Components/MainMenuComponent.h"
#include "Components/PauseMenuComponent.h"
#include "Components/TransitionComponent.h"
#include "Components/QuitConfirmationComponent.h"
#include "Components/SettingsMenuComponent.h"
#include "Components/HowToPlayComponent.h"
#include "Components/CreditsMenuComponent.h"

class GameResourceManager {
public:
	static GameResourceManager& Instance() {
		static GameResourceManager instance;
		return instance;
	}
	/**
	* @brief Registers application level components with the ComponentCreator
	*/
	void Initialize();
	/**
	* @brief Given a JSON filename, creates a GameObject from said JSON
	* @param filename - Filename of a JSON that represents a GameObject
	* @returns shared pointer to the GameObject
	*/
	GameObject* CreateGameObject(const std::string& filename);
	/**
	* @brief Given a JSON filename and a SceneGraph, creates a GameObject from said JSON, and add it to the scenegraph
	* @param filename - Filename of a JSON that represents a GameObject
	* @param sceneGraph - SceneGraph instance to add the GameObject to.
	* @returns shared pointer to the GameObject
	*/
	GameObject* CreateAndAddGameObject(const std::string& filename, SceneGraph& sceneGraph);
	/**
	* @brief Given a shader filepath and a texture filepath, creates a Material from said shader and texture
	* @param shaderPath - Filename of a shader file
	* @param texturePath - Filename of a texture file
	* @returns shared pointer to the Material
	*/
	std::shared_ptr<Material> CreateMaterial(const std::string& shaderPath, const std::string& texturePath);

private:
	GameResourceManager() = default;
	GameResourceManager(const GameResourceManager&) = delete;
	GameResourceManager& operator=(const GameResourceManager&) = delete;

	void ConfigureGameObject(GameObject* gameObject);
};