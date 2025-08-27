/****************************************************************
// File Name: SettingsMenuComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component to handle the settings menu screen, with the ability
// to access various settings like resolution, windowed/fullscreen, and audio volumes
****************************************************************/

#include "precompiled.h"
#include "Engine.h"
#include "SettingsMenuComponent.h"
#include "Event/Events/UIButtonPressedEvent.h"
#include "Event/Events/UISliderValueChangedEvent.h"
#include "SceneManagement/SceneManager.h"
#include "Managers/GlobalSoundManager.h"

void SettingsMenuComponent::Initialize()
{
    buttonEventID = EventManager::Instance().AddListener<UIButtonPressedEvent>(
        [this](const UIButtonPressedEvent& event) {
            if (event.buttonTag == "") return;
            if (event.buttonTag == "Fullscreen") {
                Engine::Instance().SetFullscreen(true);
            }
            if (event.buttonTag == "Windowed") {
                Engine::Instance().SetFullscreen(false);
            }
            if (event.buttonTag == "1920x1080") {
                Engine::Instance().SetResolution(Resolution::R_1920x1080);
            }
            if (event.buttonTag == "1600x900") {
                Engine::Instance().SetResolution(Resolution::R_1600x900);
            }
            if (event.buttonTag == "1280x720") {
                Engine::Instance().SetResolution(Resolution::R_1280x720);
            }
            if (event.buttonTag == "Back") {
                SceneManager::Instance().PopScene();
            }
        }
    );

    sliderEventID = EventManager::Instance().AddListener<UISliderValueChangedEvent>(
        [this](const UISliderValueChangedEvent& event) {
            if (event.sliderTag == "") return;
            if (event.sliderTag == "Music") {
                if (event.value >= 0 && event.value <= 1.0f) {
                    GlobalSoundManager::Instance().SetBGMVolume(event.value);
                }
            }
            if (event.sliderTag == "Ambience") {
                if (event.value >= 0 && event.value <= 1.0f) {
                    GlobalSoundManager::Instance().SetEnvVolume(event.value);
                }
            }
            if (event.sliderTag == "SFX") {
                if (event.value >= 0 && event.value <= 1.0f) {
                    GlobalSoundManager::Instance().SetSFXVolume(event.value);
                }
            }
        }
    );
}

void SettingsMenuComponent::Update(float deltaTime)
{
    if (!hasSetSliderValues) {
        SetSliderValues();
        hasSetSliderValues = true;
    }
    if (Input::Instance().IsKeyPressed(KeyCode::Escape) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 0) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 1) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 2) ||
        Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 3))
    {
        SceneManager::Instance().PopScene();
    }
}

void SettingsMenuComponent::Shutdown()
{
    EventManager::Instance().RemoveListener<UIButtonPressedEvent>(buttonEventID);
    EventManager::Instance().RemoveListener<UISliderValueChangedEvent>(sliderEventID);
}

void SettingsMenuComponent::Serialize()
{
}

void SettingsMenuComponent::Deserialize(const rapidjson::Value& json)
{
}

void SettingsMenuComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void SettingsMenuComponent::SetSliderValues()
{
    // Set music value
    auto* musicNode = owner->FindChildNodeFast("MusicSlider");
    if (musicNode) {
        GameObject* musicObject = dynamic_cast<GameObject*>(musicNode);
        if (musicObject) {
            std::shared_ptr<UISliderComponent> musicSlider = musicObject->FindComponent<UISliderComponent>();
            if (musicSlider) {
                musicSlider->SetValue(GlobalSoundManager::Instance().GetBGMVolume());
            }
        }
    }

    // Set Environment value
    auto* envNode = owner->FindChildNodeFast("AmbienceSlider");
    if (envNode) {
        GameObject* envObject = dynamic_cast<GameObject*>(envNode);
        if (envObject) {
            std::shared_ptr<UISliderComponent> envSlider = envObject->FindComponent<UISliderComponent>();
            if (envSlider) {
                envSlider->SetValue(GlobalSoundManager::Instance().GetEnvVolume());
            }
        }
    }

    // Set SFX value
    auto* sfxNode = owner->FindChildNodeFast("SFXSlider");
    if (sfxNode) {
        GameObject* sfxObject = dynamic_cast<GameObject*>(sfxNode);
        if (sfxObject) {
            std::shared_ptr<UISliderComponent> sfxSlider = sfxObject->FindComponent<UISliderComponent>();
            if (sfxSlider) {
                sfxSlider->SetValue(GlobalSoundManager::Instance().GetSFXVolume());
            }
        }
    }
}
