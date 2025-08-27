/****************************************************************
// File Name: PauseMenuComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries, Ju-ve Chankasemporn
// Description: Component to handle the pause menu screen, with the ability 
// to move to how to play, settings, or quit
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
class PauseMenuComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);
private:
	GameObject* buttonManager;

	void Settings();
};

