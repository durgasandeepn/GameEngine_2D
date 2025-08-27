/****************************************************************
// File Name: LobbyManagerComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (LobbyManagerComponent Core), Alex Humphries (Minor refactoring)
// Description: Component to handle the lobby manager, player joining, and character selection
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/InputComponent.h"
#include "Lobby/LobbyUICreator.h"
#include "Object/Components/AnimationComponent.h"

enum class PlayerState {
    NotJoined,
    Selecting,
    Ready
};

struct PlayerInfo {
    PlayerState state = PlayerState::NotJoined;
    std::string selectedCharacter;
    bool isReady = false;
    int uiIndex = -1;
    int controllerIndex = -1;
};

class LobbyManagerComponent : public Component {
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);
	void CreatePlayerLobbyObject(int controllerId);

	int AddPlayer();
	void RemovePlayer(int playerIndex);

    bool TryJoinPlayer(int controllerId = -1);
    int GetJoinedPlayerCount() const;

    void ChangePlayerSelect(int playerIndex, const std::string& characterString);
    void TogglePlayerReady(int playerIndex);

    bool AllPlayersReady() const;

    const std::vector<std::string>& GetSelectedCharacters() const;
    void SetPlayerState(int playerIndex, PlayerState newState);
    PlayerState GetPlayerState(int playerIndex) const;

    bool RegisterPlayerUI(int playerIndex, std::shared_ptr<AnimationComponent> animComp);
    std::shared_ptr<AnimationComponent> GetPlayerUI(int playerIndex) const;

    int FindAvailableUISlot() const;
    void SetPlayerReadyUI(int playerIndex, bool isReady);

    void RegisterReadyIndicator(int playerIndex, GameObject* readyIndicator);

	void SetIsEveryoneReady(bool isReady) { isEveryoneReady = isReady; }
	bool GetIsEveryoneReady() const { return isEveryoneReady; }
    LobbyUICreator ui_creator;

private:
    bool keyboardPlayerHasJoined;
    std::shared_ptr<InputComponent> inputComponent;
    bool isEveryoneReady = false;

    std::vector<bool> controllersInUse;
    std::vector<PlayerInfo> players;
    std::vector<std::shared_ptr<AnimationComponent>> playerSelectionUIs;
    std::unordered_map<std::string, bool> availableCharacters = {
        {"Blue", true},
        {"Pink", true},
        {"Red", true},
        {"Green", true}
    };
    std::vector<GameObject*> readyIndicators;
    std::vector<GameObject*> joinIndicators;
    GameObject* startUI;
};