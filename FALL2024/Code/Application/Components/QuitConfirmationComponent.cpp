/****************************************************************
// File Name: QuitConfirmationComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankaseemporn
// Description: Component to handle the quit confirmation screen
****************************************************************/

#include "precompiled.h"
#include "QuitConfirmationComponent.h"
#include "Event/Events/UIButtonPressedEvent.h"
#include "Engine.h"

void QuitConfirmationComponent::Initialize()
{
    eventID = EventManager::Instance().AddListener<UIButtonPressedEvent>(
        [this](const UIButtonPressedEvent& event) {
            if (event.buttonTag == "") return;
            if (event.buttonTag == "No") {
                No();
            }
            if (event.buttonTag == "Yes") {
                Yes();
            }
        }
    );
}

void QuitConfirmationComponent::Update(float deltaTime)
{
}

void QuitConfirmationComponent::Shutdown()
{
    EventManager::Instance().RemoveListener<UIButtonPressedEvent>(eventID);
}

void QuitConfirmationComponent::Serialize()
{
}

void QuitConfirmationComponent::Deserialize(const rapidjson::Value& json)
{
}

void QuitConfirmationComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}



void QuitConfirmationComponent::No()
{
    SceneManager::Instance().PopScene();
}

void QuitConfirmationComponent::Yes()
{
    Engine::Instance().Quit();
}
