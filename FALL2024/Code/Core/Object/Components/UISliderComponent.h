/****************************************************************
// File Name: UISliderComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component relating to a slider on the UI
// Extends from UIElementComponent
****************************************************************/

#pragma once

#include "Object/Components/UIElementComponent.h"

class UISliderComponent : public UIElementComponent {
public:
	void Initialize() override;
	void HandleInput(float deltaTime) override;

	// Calls a "UISliderValueChanged" event
	void SetValue(float newValue);
	void SetIsHovered(bool newIsHovered) override;
private:
	// The value of the slider, send an event out with this value when it is changed
	float value = 1.0f;
};