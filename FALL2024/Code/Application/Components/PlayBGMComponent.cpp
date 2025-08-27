/****************************************************************
// File Name: PlayBGMComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Component to handle playing background audio
****************************************************************/

#include "precompiled.h"
#include "PlayBGMComponent.h"
#include "Object/GameObject.h"

void PlayBGMComponent::Initialize()
{
    hasPlayed = false;
    audioSourceComponent = owner->FindComponent<AudioSourceComponent>();
}

void PlayBGMComponent::Update(float deltaTime)
{
    if (!hasPlayed) {
        audioSourceComponent->Play();
        hasPlayed = true;
    }
}

void PlayBGMComponent::Shutdown()
{
}

void PlayBGMComponent::Serialize()
{
}

void PlayBGMComponent::Deserialize(const rapidjson::Value& json)
{

}

void PlayBGMComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}
