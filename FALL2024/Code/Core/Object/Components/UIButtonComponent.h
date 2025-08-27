/****************************************************************
// File Name: UIButtonComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component relating to a button on the UI
// Extends from UIElementComponent
****************************************************************/

#pragma once
#include "Object/Components/UIElementComponent.h"

class UIButtonComponent : public UIElementComponent {
public:

	void Update(float deltaTime) override;
	void HandleInput(float deltaTime) override;

	void SetIsHovered(bool newIsHovered) override;

	// Calls a "UIButtonPressed" event
	void Activate();

};