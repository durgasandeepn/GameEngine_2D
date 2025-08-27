/****************************************************************
// File Name: MainMenuComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component to handle the main menu screen, with the ability to 
// start the game, open settings, view credits, and quit the game
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
class MainMenuComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

	void Play();
	void Settings();
	void Credits();
	void Quit();

private:
	uint32_t eventID;
};

