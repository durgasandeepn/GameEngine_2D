/****************************************************************
// File Name: AudioSourceComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Sound as a part of the component
****************************************************************/

#include "precompiled.h"
#include "AudioSourceComponent.h"

AudioSourceComponent::AudioSourceComponent() : volume(1.0f), loop(0)
{

}

void AudioSourceComponent::Initialize() 
{
    pitch = 1.0f;
}

void AudioSourceComponent::Update(float deltaTime)
{

}

void AudioSourceComponent::Shutdown()
{

}

void AudioSourceComponent::Serialize()
{

}

void AudioSourceComponent::Deserialize(const rapidjson::Value& json)
{
    try {
        // Validate the JSON structure
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for AudioSourceComponent: Expected an object.");
        }

        // Volume
        if (json.HasMember("volume") && json["volume"].IsFloat()) {
            volume = json["volume"].GetFloat();
        }
        else {
            throw std::invalid_argument("AudioSourceComponent::Deserialize - Missing or invalid 'volume'");
        }

        // Looping
        if (json.HasMember("loop") && json["loop"].IsBool()) {
            loop = json["loop"].GetBool();
        }
        else {
            throw std::invalid_argument("AudioSourceComponent::Deserialize - Missing or invalid 'loop'");
        }

        // Audio Clip
        if (json.HasMember("audioClip") && json["audioClip"].IsString()) {
            SetAudioClip(json["audioClip"].GetString());
        }
        else {
            throw std::invalid_argument("AudioSourceComponent::Deserialize - Missing or invalid 'audioClip'");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing AudioSourceComponent: " << e.what() << std::endl;
        throw; // Re-throw the exception after logging
    }
}

void AudioSourceComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{

}

void AudioSourceComponent::SetAudioSystem(AudioManager* audioManager)
{
    this->audioManager = audioManager;
    // If we have an audioClip that hasn't gotten a sound generated for it
    // (since it didn't have an audio manager), generate it now
    if (audioClip && !audioClip->IsGenerated()) {
        audioClip->Generate(*audioManager);
    }
}

void AudioSourceComponent::SetAudioClip(AudioClip* newAudioClip)
{
    if (newAudioClip && !newAudioClip->IsGenerated()) {
        newAudioClip->Generate(*audioManager);
    }

    audioClip = newAudioClip;
}

void AudioSourceComponent::SetAudioClip(std::string newAudioName)
{
    // Missing audio manager, set a non-generated audio clip
    if (audioManager == nullptr) {
        audioClip = new AudioClip(newAudioName);
    }
    else {
        audioClip = new AudioClip(newAudioName, *audioManager);
    }
}

void AudioSourceComponent::Play()
{
    if (audioClip == nullptr) {
        std::cout << "No Audio clip" << std::endl;
        return;
    }

    if (audioClip->GetSound() == nullptr) {
        std::cout << "No Sound" << std::endl;
        return;
    } 

    if (audioManager != nullptr)
    {
        audioManager->PlaySound(audioClip->GetSound(), channel, loop);
    }

    channel->setVolume(volume);
}

void AudioSourceComponent::Stop()
{
    if (channel != nullptr) {
        channel->stop();
    }
}

void AudioSourceComponent::SetVolume(float newVolume)
{
    volume = newVolume;

    if (channel != nullptr) {
        channel->setVolume(volume);
    }
}

void AudioSourceComponent::SetPitch(float newPitch)
{
    pitch = newPitch;

    if (channel != nullptr) {
        channel->setPitch(pitch);
    }
}

void AudioSourceComponent::SetLoop(bool shouldLoop)
{
    loop = shouldLoop;

    if (audioClip->GetSound() == nullptr) {
        return;
    }

    if (channel != nullptr) {

        if (audioManager != nullptr)
        {
            audioManager->SetLoop(loop, audioClip->GetSound());
        }
    }
}