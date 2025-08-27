/****************************************************************
// File Name: PlayerLobbyComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn, Alex Humphries
// Description: Component to handle the lobby menu, player joining, and character selection
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/InputComponent.h"
#include "Components/LobbyManagerComponent.h"

class PlayerLobbyComponent : public Component {
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

	void SetPlayerIndex(int index) { playerIndex = index; }
	void SetUsingKeyboard(bool keyboard) { isKeyboardPlayer = keyboard; }
	void SetControllerId(int id);
	void SetLobbyManager(LobbyManagerComponent* newManager) { lobbyManager = newManager; }

private:
	LobbyManagerComponent* lobbyManager;
	std::shared_ptr<InputComponent> inputComponent;
	int playerIndex = -1;
	bool isKeyboardPlayer = false;
	int controllerId = -1;
};

