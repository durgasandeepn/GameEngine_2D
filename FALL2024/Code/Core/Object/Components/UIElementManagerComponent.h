/****************************************************************
// File Name: ElementManagerComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Handles input in relation to a series of elements
// registered as children of the owning object.
// Used in menus to handle input / button management (button indices).
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/InputComponent.h"

class UIElementComponent;

class UIElementManagerComponent : public Component {
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

	void RegisterElement(UIElementComponent& elementToRegister) { elements .push_back(&elementToRegister); }

	void SetLayout(float deltatTime);

	void MouseIsHovering(UIElementComponent& elementHovered);
private:
	float hoverDelay = 0.0f;
	const float hoverCooldown = 0.2f;
	bool initialLayoutSet = false;
	int elementIndex = 0; // The button we've currently got highlighted
	std::vector<UIElementComponent*> elements; // All available UI elements

	// Layout settings
	float startX = 0.0f;
	float startY = 0.0f;
	float elementMargin = 1.0f;

	std::shared_ptr<InputComponent> inputComponent;
};