/****************************************************************
// File Name: LobbyUICreator
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Creates the layout for the lobby screen and various UI components
****************************************************************/

#include "precompiled.h"
#include "LobbyUICreator.h"
#include "Managers/GameResourceManager.h"
#include "Object/GameObjectFactory.h"

LobbyUICreator::LobbyUICreator()
{
}

GameObject* LobbyUICreator::CreateCharacterBackgroundUI(Vector3 pos, Vector3 scale) {
    auto bgUI = GameObject::Instantiate("UI/lobby_character_backgroundUI.json");
    if (!bgUI) {
        std::cerr << "Failed to create character background UI" << std::endl;
        return nullptr;
    };
    bgUI->SetLocalPosition(pos);
    bgUI->SetLocalScale(scale);
    bgUI->Update(1.0f);

    Vector3 promptPos = pos + Vector3(0.0f, -4.5f, 0.0f);
    //CreateJoinPrompt(promptPos, Vector3(4.0f, 1.0f, 1.0f));

    return bgUI;
}

GameObject* LobbyUICreator::CreateStartUI(Vector3 pos, Vector3 scale)
{
    auto startUI = GameObject::Instantiate("UI/press_to_start.json");
    if (startUI) {
        startUI->SetLocalPosition(pos);
        startUI->SetLocalScale(scale);
        startUI->SetIsActive(false);
        startUI->Update(1.0f);
    }
    return startUI;
}

GameObject* LobbyUICreator::CreateSelectYourCharacterUI(Vector3 pos, Vector3 scale)
{
    auto SelectYourCharacterUI = GameObject::Instantiate("UI/select_your_character.json");
    if (SelectYourCharacterUI) {
        SelectYourCharacterUI->SetLocalPosition(pos);
        SelectYourCharacterUI->SetLocalScale(scale);
        SelectYourCharacterUI->SetIsActive(true);
        SelectYourCharacterUI->Update(1.0f);
    }
    return SelectYourCharacterUI;
}

GameObject* LobbyUICreator::CreateCharacterUI(Vector3 pos, Vector3 scale, int playerIndex) {
    auto charUI = GameObject::Instantiate("UI/character_selection.json");
    if (!charUI) {
        std::cerr << "Failed to create character UI" << std::endl;
        return nullptr;
    };
    charUI->SetLocalPosition(pos);
    charUI->SetLocalScale(scale);
    charUI->Update(1.0f);
    return charUI;
}

GameObject* LobbyUICreator::CreateReadyIndicator(Vector3 pos, Vector3 scale) {
    auto readyUI = GameObject::Instantiate("UI/ready_indicator.json");
    if (readyUI) {
        readyUI->SetLocalPosition(pos);
        readyUI->SetLocalScale(scale);
        readyUI->Update(1.0f);
        readyUI->SetIsActive(false); 
    }
    return readyUI;
}

GameObject* LobbyUICreator::CreateJoinPrompt(Vector3 pos, Vector3 scale) {
    auto promptUI = GameObject::Instantiate("UI/join_prompt.json");
    if (promptUI) {
        promptUI->SetLocalPosition(pos);
        promptUI->SetLocalScale(scale);
        promptUI->Update(1.0f);
    }
    return promptUI;
}


