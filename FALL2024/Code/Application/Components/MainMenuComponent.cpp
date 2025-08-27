/****************************************************************
// File Name: MainMenuComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component to handle the main menu screen, with the ability to
// start the game, open settings, view credits, and quit the game
****************************************************************/


#include "precompiled.h"
#include "MainMenuComponent.h"
#include "Engine.h"
#include "Scenes/Lobby.h"
#include "Event/Events/UIButtonPressedEvent.h"
#include "Managers/TransitionManager.h"
#include "Scenes/QuitConfirmationScene.h"
#include "Scenes/SettingsScene.h"
#include "Scenes/CreditsScene.h"


void MainMenuComponent::Initialize()
{
    eventID = EventManager::Instance().AddListener<UIButtonPressedEvent>(
        [this](const UIButtonPressedEvent& event) {
            if (event.buttonTag == "") return;
            if (event.buttonTag == "Play") {
                Play();
            }
            if (event.buttonTag == "Settings") {
                Settings();
            }
            if (event.buttonTag == "Credits") {
                Credits();
            }
            if (event.buttonTag == "Quit") {
                Quit();
            }
        }
    );
}

void MainMenuComponent::Update(float deltaTime)
{
}

void MainMenuComponent::Shutdown()
{
    //EventManager::Instance().RemoveListener<UIButtonPressedEvent>(eventID);
    EventManager::Instance().RemoveListenersForType<UIButtonPressedEvent>();
}

void MainMenuComponent::Serialize()
{
}

void MainMenuComponent::Deserialize(const rapidjson::Value& json)
{
}

void MainMenuComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void MainMenuComponent::Play()
{
    TransitionManager::Instance().QueueSceneChange<Lobby>("Lobby");
}

void MainMenuComponent::Settings()
{
    SceneManager::Instance().PushScene<SettingsScene>("Settings");
}

void MainMenuComponent::Credits()
{
    SceneManager::Instance().PushScene<CreditsScene>("Credits");
}

void MainMenuComponent::Quit()
{
    SceneManager::Instance().PushScene<QuitConfirmationScene>("QuitConfirmationScene");
}
