/****************************************************************
// File Name: CreditsMenuComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component to handle the credits menu screen, with the ability to speed it up
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
class CreditsMenuComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

private:
	float scrollSpeed = 1.0f;

	bool hasInitialized = false;
	GameObject* creditsTitle;
	GameObject* knightlyBuild;
	GameObject* creditsText;
	GameObject* digipenLogo;
	GameObject* thanksForPlaying;
};

