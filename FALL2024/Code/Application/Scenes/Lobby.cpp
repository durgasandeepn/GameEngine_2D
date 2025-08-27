/****************************************************************
// File Name: Lobby
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A scene for the lobby. Allows up to 4 players to join
// the game and select their character.
****************************************************************/

#include "precompiled.h"
#include "Lobby.h"
#include "Managers/GameResourceManager.h"

Lobby::Lobby(const std::string& name)
	:Scene(name)
{
	sceneGraph = std::make_unique<SceneGraph>(Engine::Instance().GetRenderer());
}

void Lobby::Initialize()
{
	auto camera = GameResourceManager::Instance().CreateAndAddGameObject("gameplaycamera.json", *sceneGraph);
	if (!camera) {
		std::cerr << "Failed to create camera" << std::endl;
	};

	auto area = GameResourceManager::Instance().CreateAndAddGameObject("character_select_bg.json", *sceneGraph);
	if (!area) {
		std::cerr << "Failed to create block" << std::endl;
	};
	area->SetLocalPosition(Vector3(0.0f, -2.0f, 0.0f));
	area->SetLocalScale(Vector3(40.0f, 25.0f, 0.0f));
	
	auto lobbyManager = GameResourceManager::Instance().CreateAndAddGameObject("PlayerCharacter/Lobby/lobby_manager.json", *sceneGraph);
	if (!lobbyManager) {
		std::cerr << "Failed to create lobbyManager" << std::endl;
	};

}

void Lobby::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Lobby::OnEnter()
{
}

void Lobby::OnExit()
{
}

void Lobby::OnResume()
{
}

void Lobby::OnPause()
{
}
