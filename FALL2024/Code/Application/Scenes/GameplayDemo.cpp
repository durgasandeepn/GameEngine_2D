/****************************************************************
// File Name: GameplayDemo
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: The main gameplay scene. Internal room changes
// are handled by the GameManager class.
****************************************************************/

#include "precompiled.h"
#include "GameplayDemo.h"
#include "Managers/GameResourceManager.h"
#include "Object/GameObjectFactory.h"
#include "Engine.h"
#include "Input/InputCodes.h"
#include "Object/Components/AudioSourceComponent.h"
#include "Events/PlayerDestroyEvent.h"
#include "Object/Components/AnimationComponent.h"
#include "Components/HealthComponent.h"
#include "Components/EnemyComponent.h"
#include "Dungeon/DungeonOne.h"
#include "Dungeon/DungeonTwo.h"
#include "Dungeon/DungeonBoss.h"
#include "Dungeon/PlayerCreator.h"
#include "Dungeon/Room.h"

GameplayDemo::GameplayDemo(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void GameplayDemo::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("gameplaycamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto area = GameResourceManager::Instance().CreateAndAddGameObject("gameplayarea.json", *sceneGraph);
	if (!area) {
		std::cerr << "Failed to create block" << std::endl;
	};
	area->SetLocalScale(Vector3(60.0f, 40.0f, 0.0f));

	GameManager::Instance().Init();

}

bool hasDoorOpen = false;

void GameplayDemo::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	GameManager::Instance().Update(deltaTime);
}

void GameplayDemo::OnEnter()
{
}

void GameplayDemo::OnExit()
{
}

void GameplayDemo::OnResume()
{
}

void GameplayDemo::OnPause()
{
}
