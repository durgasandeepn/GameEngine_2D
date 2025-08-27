/****************************************************************
// File Name: PlayBGMComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Component to handle playing background audio
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/AudioSourceComponent.h"

class PlayBGMComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

private:
	bool hasPlayed;
	std::shared_ptr<AudioSourceComponent> audioSourceComponent;
};

