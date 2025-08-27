/****************************************************************
// File Name: PlayerCreator
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (PlayerCreator core), Jacob Wilburn (Layout changes), Alex Humphries (Refactoring UI)
// Description: Class that handles the creation of players and their UI
****************************************************************/

#include "precompiled.h"
#include "PlayerCreator.h"

PlayerCreator::PlayerCreator()
{
}

GameObject* PlayerCreator::CreatePlayer(PlayerInfo playerInfo, int playerIndex)
{
	std::string playerType = "";
	if (playerInfo.controllerIndex == -1) {
		playerType = "keyboard";
	}
	else {
		playerType = "controller";
	}
	std::string playerColor = playerInfo.selectedCharacter;

	std::string jsonCharacter = "PlayerCharacter/" + playerType + playerColor + "Character.json";
	auto player = GameObject::Instantiate(jsonCharacter);
	if (!player) {
		std::cerr << "Failed to create player" << std::endl;
		return nullptr;
	};
	// Get Player Stuff
	Vector3 playerPos;
	Vector3 backgroundUIPosition;
	std::string playerUIJSON;
	Vector3 playerUIPos;
	Vector3 playerHealthUIPos;

	SetPlayerByIndex(playerIndex, playerPos, backgroundUIPosition, playerUIPos, playerHealthUIPos);

	if (playerColor == "Blue") {
		playerUIJSON = "UI/p1UI.json";
	}
	else if (playerColor == "Pink") {
		playerUIJSON = "UI/p2UI.json";
	}
	else if (playerColor == "Red") {
		playerUIJSON = "UI/p3UI.json";
	}
	else if (playerColor == "Green") {
		playerUIJSON = "UI/p4UI.json";
	}

	player->SetLocalPosition(playerPos);
	auto playerComponent = player->FindComponent<MovementComponent2D>();
	auto playerinput = player->FindComponent<InputComponent>();

	//controller
	playerinput->SetControllerId(playerInfo.controllerIndex);

	// Health component
	player->AddComponent<HealthComponent>();
	auto playerHealthComponent = player->FindComponent<HealthComponent>();

	auto playerBackgroundUI = GameObject::Instantiate("UI/backgroundUI.json");
	if (!playerBackgroundUI) {
		std::cerr << "Failed to create UIComponent" << std::endl;
	};
	playerBackgroundUI->SetLocalPosition(backgroundUIPosition);
	playerBackgroundUI->SetLocalScale(Vector3(6.5f, 1.25f, 0.0f));

	auto playerUI = GameObject::Instantiate(playerUIJSON);
	if (!playerUI) {
		std::cerr << "Failed to create UIComponent" << std::endl;
	};
	playerUI->SetLocalPosition(playerUIPos);
	playerUI->SetLocalScale(Vector3(1.0f, 1.0f, 0.0f));

	playerHealthComponent->SetCreateHealthUI(true);
	playerHealthComponent->SetHealthUIPos(playerHealthUIPos);
	playerHealthComponent->SetHealth(3);

	auto playerReviveUI = GameObject::Instantiate("UI/reviveUI.json");
	if (!playerReviveUI) {
		std::cerr << "Failed to create UIComponent" << std::endl;
	};
	playerReviveUI->SetLocalScale(Vector3(10.0f, 1.0f, 0.0f));

	playerComponent->SetHealthReviveUIComponent(playerReviveUI->FindComponent<UIComponent>());

	return player;
}

void PlayerCreator::SetPlayerByIndex(int playerIndex, Vector3& playerPos, Vector3& backgroundUIPosition, Vector3& playerUIPos, Vector3& playerHealthUIPos)
{
	if (playerIndex == 0) {
		playerPos = Vector3(-5.0f, -4.0f, 0.0f);
		backgroundUIPosition = Vector3(-15.9f, 10.15f, 0.0f);
		playerUIPos = Vector3(-18.35f, 10.15f, 0.0f);
		playerHealthUIPos = Vector3(-16.9f, 10.15f, 0.0f);
	}
	else if (playerIndex == 1) {
		playerPos = Vector3(-2.0f, -4.0f, 0.0f);
		backgroundUIPosition = Vector3(15.9f, 10.15f, 0.0f);
		playerUIPos = Vector3(18.35f, 10.15f, 0.0f);
		playerHealthUIPos = Vector3(13.9f, 10.15f, 0.0f);
	}
	else if (playerIndex == 2) {
		playerPos = Vector3(2.0f, -4.0f, 0.0f);
		backgroundUIPosition = Vector3(-15.9f, -10.15f, 0.0f);
		playerUIPos = Vector3(-18.35f, -10.15f, 0.0f);
		playerHealthUIPos = Vector3(-16.9f, -10.15f, 0.0f);
	}
	else if (playerIndex == 3) {
		playerPos = Vector3(5.0f, -4.0f, 0.0f);
		backgroundUIPosition = Vector3(15.9f, -10.15f, 0.0f);
		playerUIPos = Vector3(18.35f, -10.15f, 0.0f);
		playerHealthUIPos = Vector3(13.9f, -10.15f, 0.0f);
	}
}
