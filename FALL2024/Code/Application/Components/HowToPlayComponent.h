/****************************************************************
// File Name: HowToPlayComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: Component to handle the how to play menu screen
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
class HowToPlayComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);


	void Return();

private:
	uint32_t eventID;
};
