/****************************************************************
// File Name: HowToPlayComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: Component to handle the how to play menu screen
****************************************************************/

#include "precompiled.h"
#include "HowToPlayComponent.h"
#include "Event/Events/UIButtonPressedEvent.h"
#include "Engine.h"

void HowToPlayComponent::Initialize()
{
    eventID = EventManager::Instance().AddListener<UIButtonPressedEvent>(
        [this](const UIButtonPressedEvent& event) {
            if (event.buttonTag == "") return;
            if (event.buttonTag == "Back") {
                Return();
            }
        }
    );
}

void HowToPlayComponent::Update(float deltaTime)
{
    if (Input::Instance().IsKeyPressed(KeyCode::Escape) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 0) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 1) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 2) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 3))
    {
        SceneManager::Instance().PopScene();
    }
}

void HowToPlayComponent::Shutdown()
{
    EventManager::Instance().RemoveListener<UIButtonPressedEvent>(eventID);
}

void HowToPlayComponent::Serialize()
{
}

void HowToPlayComponent::Deserialize(const rapidjson::Value& json)
{
}

void HowToPlayComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}



void HowToPlayComponent::Return()
{
    SceneManager::Instance().PopScene();
}