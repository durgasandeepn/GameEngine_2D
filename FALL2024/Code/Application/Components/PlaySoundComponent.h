/****************************************************************
// File Name: PlaySoundComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankaseemporn
// Description: Component to handle the audio playing 
****************************************************************/

#pragma once

#include "Object/Components/Component.h"
#include "Object/Components/AudioSourceComponent.h"
#include "Object/Components/InputComponent.h"
#include <unordered_map>

class PlaySoundComponent : public Component {
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);
	void Play(std::string soundName);
private:
	std::shared_ptr<AudioSourceComponent> audioSourceComponent;
	std::shared_ptr<InputComponent> inputComponent;
	std::unordered_map<std::string, AudioClip*> soundMap;
};