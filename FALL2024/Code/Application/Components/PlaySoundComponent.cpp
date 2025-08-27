/****************************************************************
// File Name: PlaySoundComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankaseemporn
// Description: Component to handle the audio playing
****************************************************************/


#include "precompiled.h"
#include "PlaySoundComponent.h"
#include "Object/GameObject.h"
#include "Sound/AudioManager.h"

void PlaySoundComponent::Initialize()
{
	audioSourceComponent = owner->FindComponent<AudioSourceComponent>();
    //inputComponent = owner->FindComponent<InputComponent>();
}

//TODO: remove the implementation after the showcase
void PlaySoundComponent::Update(float deltaTime)
{
    //if (inputComponent->IsActionPressed("Space"))
    //{
    //    audioSourceComponent->SetAudioClip(soundMap["Jump"]);
    //    audioSourceComponent->Play();
    //}

    //if (inputComponent->IsActionPressed("Shift"))
    //{
    //    audioSourceComponent->SetAudioClip(soundMap["Right"]);
    //    audioSourceComponent->Play();
    //}
}

void PlaySoundComponent::Shutdown()
{
}

void PlaySoundComponent::Serialize()
{
}

void PlaySoundComponent::Deserialize(const rapidjson::Value& json)
{
    try 
    {
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for PlaySoundComponent: Expected an object.");
        }

        if (!json.HasMember("soundAttributes")) {
            throw std::invalid_argument("Invalid JSON: 'soundAttributes' must be an array.");
        }

        if (!json["soundAttributes"].IsArray()) {
            throw std::invalid_argument("Invalid JSON: 'soundAttributes' must be an array.");
        }

        const auto& soundAttributes = json["soundAttributes"].GetArray();
        if (soundAttributes.Empty()) {
            throw std::invalid_argument("Invalid JSON: no string");
        }

        for (const auto& soundObj : soundAttributes) {
            if (!soundObj["name"].IsString()) {
                throw std::invalid_argument("Invalid JSON: not string");
            }

            if (!soundObj["file"].IsString()) {
                throw std::invalid_argument("Invalid JSON: not string");
            }

            if (!soundObj.HasMember("name") || !soundObj["name"].IsString()) {
                throw std::invalid_argument("Invalid JSON: Missing or invalid 'name' field.");
            }
            if (!soundObj.HasMember("file") || !soundObj["file"].IsString()) {
                throw std::invalid_argument("Invalid JSON: Missing or invalid 'file' field.");
            }

            std::string soundName = soundObj["name"].GetString();
            std::string filePath = soundObj["file"].GetString();
            std::cout << "filePath: "<< filePath <<std::endl;
            AudioClip* clip = new AudioClip(filePath);
            soundMap[soundName] = clip;
        }

        for (const auto& pair : soundMap) {
            std::cout << pair.first << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing PlaySoundComponent: " << e.what() << std::endl;
        throw; 
    }
}

void PlaySoundComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void PlaySoundComponent::Play(std::string soundName)
{
    audioSourceComponent->SetAudioClip(soundMap[soundName]);
    audioSourceComponent->Play();
}
