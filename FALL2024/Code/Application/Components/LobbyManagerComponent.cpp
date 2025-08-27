/****************************************************************
// File Name: LobbyManagerComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (LobbyManagerComponent Core), Alex Humphries (Minor refactoring)
// Description: Component to handle the lobby manager, player joining, and character selection
****************************************************************/

#include "precompiled.h"
#include "LobbyManagerComponent.h"
#include "PlayerLobbyComponent.h"
#include "Object/GameObject.h"
#include "Managers/TransitionManager.h"
#include "Scenes/GameplayDemo.h"
#include "Scenes/MainMenu.h"
#include "Managers/GlobalSoundManager.h"

void LobbyManagerComponent::Initialize() {
    inputComponent = owner->FindComponent<InputComponent>();

    players.resize(4);
    playerSelectionUIs.resize(4);
    readyIndicators.resize(4);

    ui_creator.CreateSelectYourCharacterUI(Vector3(0, 8.0f, 1.0f), Vector3(15.0f, 3.0f, 1.0f));

    startUI = ui_creator.CreateStartUI(Vector3(0, -8.0f, 1.0f), Vector3(15.0f, 3.0f, 1.0f));

    const float xPositions[4] = { -13.5f, -5.0f, 5.0f, 13.5f };

    for (int i = 0; i < 4; i++) {

        ui_creator.CreateCharacterBackgroundUI(
            Vector3(xPositions[i], 0.0f, 1.0f),
            Vector3(8.0f, 12.0f, 1.0f)
        );

        auto join_prompt = ui_creator.CreateJoinPrompt(
            Vector3(xPositions[i], 0.0f, 1.0f),
            Vector3(6.0f, 6.0f, 1.0f)
        );
        joinIndicators.push_back(join_prompt);
    }
}

void LobbyManagerComponent::Update(float deltaTime) {

    startUI->SetIsActive(isEveryoneReady);

    if (isEveryoneReady &&
        (inputComponent->IsActionPressed("StartKeyboard") ||
            inputComponent->IsActionPressed("StartController"))
        ) {
        GlobalSoundManager::Instance().Play("begin.mp3");
        GameManager::Instance().SetInitialPlayerInfos(players);
        // Start Game
        TransitionManager::Instance().QueueSceneChange<GameplayDemo>("Gameplay Scene");
        return;
    }

    if (inputComponent) {
        // Check keyboard (player 1)
        if (keyboardPlayerHasJoined == false) {
            if (inputComponent->IsActionPressed("JoinKeyboard")) {
                if (TryJoinPlayer(-1)) {

                    std::cout << "***Create player lobby object: keyboard***" << std::endl;
                    CreatePlayerLobbyObject(-1);
                    keyboardPlayerHasJoined = true;
                    isEveryoneReady = false;
                }
            }
        }

        // Check controllers
        bool cancelPressed = false;
        for (int i = 0; i < 4; i++) {
            if (inputComponent->IsActionPressed("JoinController", i)) {
                if (TryJoinPlayer(i)) {
                    std::cout << "****Create player lobby object: controller" << i << std::endl;

                    CreatePlayerLobbyObject(i);
                    isEveryoneReady = false;
                    break;
                }
            }
            if (inputComponent->IsActionPressed("CancelLobbyController", i)) {
                cancelPressed = true;
            }
        }

        bool noPlayers = true;
		for (auto player : players) {
			if (player.state != PlayerState::NotJoined) {
				noPlayers = false;
				break;
			}
			noPlayers = true;
		}
        if (noPlayers) {
            if (inputComponent->IsActionPressed("CancelLobby")) {
                TransitionManager::Instance().QueueSceneChange<MainMenu>("MainMenu");
            }
            else if (cancelPressed) {
                TransitionManager::Instance().QueueSceneChange<MainMenu>("MainMenu");
            }
        }

    }
}

void LobbyManagerComponent::Shutdown()
{
}

void LobbyManagerComponent::Serialize()
{
}

void LobbyManagerComponent::Deserialize(const rapidjson::Value& json)
{
}

void LobbyManagerComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void LobbyManagerComponent::CreatePlayerLobbyObject(int controllerId)
{
    const float xPositions[4] = { -13.5f, -5.0f, 5.0f, 13.5f };

    bool isKeyboard = (controllerId == -1);
    int playerIndex = GetJoinedPlayerCount() - 1;

    Vector3 pos = Vector3(xPositions[playerIndex], 1.0f, 1.0f);
    auto characterUI = ui_creator.CreateCharacterUI(
        pos,
        Vector3(6.0f, 6.0f, 1.0f),
        playerIndex
    );

    // Add ready indicator (hidden by default)
    Vector3 readyPos = pos + Vector3(0.0f, -4.5f, 0.0f);
    auto readyIndicator = ui_creator.CreateReadyIndicator(readyPos, Vector3(3.0f, 2.0f, 1.0f));

    if (playerIndex >= 0 && playerIndex < 4) {
        RegisterReadyIndicator(playerIndex, readyIndicator);
    }

    joinIndicators[playerIndex]->SetIsActive(false);

    std::string path = isKeyboard ?
        "PlayerCharacter/Lobby/playerKeyboardLobby.json" :
        "PlayerCharacter/Lobby/playerControllerLobby.json";

    auto lobbyObj = GameObject::Instantiate(path);
    if (lobbyObj) {
        // Add PlayerLobbyComponent and configure it
        auto lobbyComp = lobbyObj->AddComponent<PlayerLobbyComponent>();
        lobbyComp->SetPlayerIndex(playerIndex);
        lobbyComp->SetLobbyManager(this);

        if (!isKeyboard) {
            lobbyComp->SetControllerId(controllerId);
        }

        // Position the lobby object appropriately
        lobbyObj->SetLocalPosition(Vector3(xPositions[playerIndex], 0.0f, 0.0f));
    }

    if (auto animComp = characterUI->FindComponentInChild<AnimationComponent>()) {
            RegisterPlayerUI(playerIndex, animComp);
    }
}

int LobbyManagerComponent::AddPlayer() {
    for (int i = 0; i < 4; ++i) {
        if (players[i].state == PlayerState::NotJoined) {
            players[i].state = PlayerState::Selecting;
            players[i].selectedCharacter = "Blue";
            players[i].uiIndex = FindAvailableUISlot();
            return i;
        }
    }
    return -1;
}

bool LobbyManagerComponent::TryJoinPlayer(int controllerId) {
    if (controllerId >= 0) {
        if (controllerId < controllersInUse.size() && controllersInUse[controllerId]) {

            return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (players[i].state == PlayerState::NotJoined) {
            players[i].state = PlayerState::Selecting;
            players[i].selectedCharacter = "Blue";
            players[i].uiIndex = FindAvailableUISlot();
            players[i].isReady = false;

            if (controllerId >= 0) {
                if (controllerId >= controllersInUse.size()) {
                    controllersInUse.resize(controllerId + 1);
                }
                controllersInUse[controllerId] = true;
            }
            players[i].controllerIndex = controllerId;
            return true;
        }
    }
    return false;
}

int LobbyManagerComponent::GetJoinedPlayerCount() const {
    int count = 0;
    for (const auto& player : players) {
        if (player.state != PlayerState::NotJoined) {
            count++;
        }
    }
    return count;
}

void LobbyManagerComponent::ChangePlayerSelect(int playerIndex, const std::string& characterString) {
    if (playerIndex < 0 || playerIndex >= 4) return;

    players[playerIndex].selectedCharacter = characterString;

    auto ui = GetPlayerUI(playerIndex);

    if (ui != nullptr) {
        ui->ChangeAnimationState(characterString);
    }
}

void LobbyManagerComponent::TogglePlayerReady(int playerIndex) {
    if (playerIndex < 0 || playerIndex >= 4) return;

    players[playerIndex].isReady = !players[playerIndex].isReady;
    SetPlayerReadyUI(playerIndex, players[playerIndex].isReady);
    if (AllPlayersReady()) {
        isEveryoneReady = true;
    }
}

bool LobbyManagerComponent::AllPlayersReady() const {
    if (GetJoinedPlayerCount() <= 0) return false;
    for (const auto& player : players) {
        if (player.state == PlayerState::Selecting && !player.isReady) {
            return false;
        }
    }
    return true;
}

const std::vector<std::string>& LobbyManagerComponent::GetSelectedCharacters() const {
    static std::vector<std::string> selectedChars;
    selectedChars.clear();

    for (const auto& player : players) {
        if (player.state != PlayerState::NotJoined) {
            selectedChars.push_back(player.selectedCharacter);
        }
        else {
            selectedChars.push_back("");
        }
    }

    return selectedChars;
}

void LobbyManagerComponent::SetPlayerState(int playerIndex, PlayerState newState)
{
    if (playerIndex >= 0 && playerIndex < static_cast<int>(players.size())) {
        players[playerIndex].state = newState;
    }
}

PlayerState LobbyManagerComponent::GetPlayerState(int playerIndex) const {
    if (playerIndex >= 0 && playerIndex < static_cast<int>(players.size())) {
        return players[playerIndex].state;
    }
    return PlayerState::NotJoined;
}

bool LobbyManagerComponent::RegisterPlayerUI(int playerIndex, std::shared_ptr<AnimationComponent> animComp) {

    if (playerIndex < 0 || playerIndex >= 4) {
        return false;
    }

    if (!animComp) {
        return false;
    }

    int uiIndex = players[playerIndex].uiIndex;
    if (uiIndex < 0 || uiIndex >= playerSelectionUIs.size()) {
        return false;
    }

    playerSelectionUIs[uiIndex] = animComp;

    animComp->ChangeAnimationState(players[playerIndex].selectedCharacter);

    return true;
}

std::shared_ptr<AnimationComponent> LobbyManagerComponent::GetPlayerUI(int playerIndex) const {
    if (playerIndex < 0 || playerIndex >= 4) return nullptr;
    int uiIndex = players[playerIndex].uiIndex;

    if (uiIndex >= 0 && uiIndex < playerSelectionUIs.size())
    {
        return playerSelectionUIs[uiIndex];
    }
    else
    {
        return nullptr;
    }


}

int LobbyManagerComponent::FindAvailableUISlot() const {
    for (int i = 0; i < playerSelectionUIs.size(); ++i) {
        if (!playerSelectionUIs[i]) {
            return i;
        }
    }
    return -1;
}

void LobbyManagerComponent::SetPlayerReadyUI(int playerIndex, bool isReady) {
    if (playerIndex < 0 || playerIndex >= 4) return;

    if (playerIndex < readyIndicators.size() && readyIndicators[playerIndex]) {
        readyIndicators[playerIndex]->SetIsActive(isReady);
    }
}


void LobbyManagerComponent::RegisterReadyIndicator(int playerIndex, GameObject* readyIndicator) {
    if (playerIndex < 0 || playerIndex >= 4) return;

    if (readyIndicators.size() <= playerIndex) {
        readyIndicators.resize(playerIndex + 1);
    }

    readyIndicators[playerIndex] = readyIndicator;
}