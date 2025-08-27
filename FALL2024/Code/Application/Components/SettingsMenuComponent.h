/****************************************************************
// File Name: SettingsMenuComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component to handle the settings menu screen, with the ability 
// to access various settings like resolution, windowed/fullscreen, and audio volumes
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
class SettingsMenuComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

private:
	bool hasSetSliderValues = false;
	uint32_t buttonEventID;
	uint32_t sliderEventID;

	// Set the intended values for the children sliders
	void SetSliderValues();
};

