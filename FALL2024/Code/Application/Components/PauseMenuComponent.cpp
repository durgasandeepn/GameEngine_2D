/****************************************************************
// File Name: PauseMenuComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Component to handle the pause menu screen, with the ability
// to move to how to play, settings, or quit
****************************************************************/

#include "precompiled.h"
#include "PauseMenuComponent.h"
#include "Event/Events/UIButtonPressedEvent.h"
#include "Object/GameObject.h"
#include "Managers/GameManager.h"
#include "Scenes/QuitConfirmationScene.h"
#include "Scenes/SettingsScene.h"
#include "Scenes/HowToPlayScene.h"
void PauseMenuComponent::Initialize()
{

    EventManager::Instance().AddListener<UIButtonPressedEvent>(
        [this](const UIButtonPressedEvent& event) {
            if (event.buttonTag == "") return;
            if (event.buttonTag == "Resume") {
                if (GameManager::Instance().IsPauseMenuActive())
                    GameManager::Instance().ClosePauseMenu();
            }
            if (event.buttonTag == "Settings") {
                Settings();
            }
            if (event.buttonTag == "HowToPlay") {
                SceneManager::Instance().PushScene<HowToPlayScene>("HowToPlayScene");
            }
            if (event.buttonTag == "Quit") {
                SceneManager::Instance().PushScene<QuitConfirmationScene>("QuitConfirmationScene");
            }
        }
    );
}

void PauseMenuComponent::Update(float deltaTime)
{
    if (Input::Instance().IsKeyPressed(KeyCode::Escape) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 0) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 1) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 2) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 3) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 0) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 1) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 2) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 3))
    {
        if (GameManager::Instance().IsPauseMenuActive())
            GameManager::Instance().ClosePauseMenu();
    }
}

void PauseMenuComponent::Shutdown()
{
    EventManager::Instance().RemoveListenersForType<UIButtonPressedEvent>();
}

void PauseMenuComponent::Serialize()
{
}

void PauseMenuComponent::Deserialize(const rapidjson::Value& json)
{
}

void PauseMenuComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void PauseMenuComponent::Settings()
{
    SceneManager::Instance().PushScene<SettingsScene>("Settings");
}

