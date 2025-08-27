/****************************************************************
// File Name: PlayerLobbyComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Component to handle the lobby menu, player joining, and character selection
****************************************************************/

#include "precompiled.h"
#include "PlayerLobbyComponent.h"
#include "Object/GameObject.h"
#include "Managers/TransitionManager.h"
#include "Scenes/MainMenu.h"
#include "Managers/GlobalSoundManager.h"

void PlayerLobbyComponent::Initialize()
{
    //playerIndex = LobbyManager::Instance().AddPlayer();


}


void PlayerLobbyComponent::Update(float deltaTime)
{
    if (playerIndex == -1 ) return;

    if (inputComponent == nullptr) 
    {
        inputComponent = owner->FindComponent<InputComponent>();

        //if (playerIndex >= 1)
        //{
        //    inputComponent->SetControllerId(playerIndex - 1);
        //}
        return;
    }

    if (!lobbyManager) return;


    if (lobbyManager->GetPlayerState(playerIndex) == PlayerState::Selecting) {

        if (inputComponent->IsActionPressed("Left")) {
            const auto& current = lobbyManager->GetSelectedCharacters()[playerIndex];
            if (current == "Blue") lobbyManager->ChangePlayerSelect(playerIndex, "Green");
            else if (current == "Pink") lobbyManager->ChangePlayerSelect(playerIndex, "Blue");
            else if (current == "Red") lobbyManager->ChangePlayerSelect(playerIndex, "Pink");
            else if (current == "Green") lobbyManager->ChangePlayerSelect(playerIndex, "Red");
            
            GlobalSoundManager::Instance().Play("bookFlip1.mp3");
        
        }

        if (inputComponent->IsActionPressed("Right")) {
            const auto& current = lobbyManager->GetSelectedCharacters()[playerIndex];
            if (current == "Blue") lobbyManager->ChangePlayerSelect(playerIndex, "Pink");
            else if (current == "Pink") lobbyManager->ChangePlayerSelect(playerIndex, "Red");
            else if (current == "Red") lobbyManager->ChangePlayerSelect(playerIndex, "Green");
            else if (current == "Green") lobbyManager->ChangePlayerSelect(playerIndex, "Blue");


            GlobalSoundManager::Instance().Play("bookFlip1.mp3");
        }

        if (inputComponent->IsActionPressed("Confirm")) {
            lobbyManager->SetPlayerState(playerIndex, PlayerState::Ready);
            lobbyManager->TogglePlayerReady(playerIndex);
            GlobalSoundManager::Instance().Play("ready.mp3");
            
        }
		if (inputComponent->IsActionPressed("Cancel")) {
			TransitionManager::Instance().QueueSceneChange<MainMenu>("MainMenu");
            GlobalSoundManager::Instance().Play("bookClose.mp3");
		}
    }
    if (inputComponent->IsActionPressed("Cancel") && lobbyManager->GetPlayerState(playerIndex) != PlayerState::Selecting) {
        lobbyManager->SetPlayerState(playerIndex, PlayerState::Selecting);
        lobbyManager->TogglePlayerReady(playerIndex);
        if (lobbyManager->GetIsEveryoneReady()) {
            lobbyManager->SetIsEveryoneReady(false);
        }
        GlobalSoundManager::Instance().Play("bookClose.mp3");

    }
}

void PlayerLobbyComponent::Shutdown()
{
}

void PlayerLobbyComponent::Serialize()
{
}

void PlayerLobbyComponent::Deserialize(const rapidjson::Value& json)
{

}

void PlayerLobbyComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void PlayerLobbyComponent::SetControllerId(int id)
{
    controllerId = id;

    if (inputComponent == nullptr)
    {
        inputComponent = owner->FindComponent<InputComponent>();
    }

    if (inputComponent != nullptr)
    {
        inputComponent->SetControllerId(controllerId);
    }
}