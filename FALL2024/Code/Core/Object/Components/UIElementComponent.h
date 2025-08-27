/****************************************************************
// File Name: UIElementComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Base parent component for UI Elements, specific
// elements (like buttons and sliders) extend from this parent class.
****************************************************************/
#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/UIElementManagerComponent.h"
#include "Object/Components/AnimationComponent.h"
#include "Object/Components/UIComponent.h"

class UIElementComponent : public Component {
public:
	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

	// Lets an element manage it's own input handling
	virtual void HandleInput(float deltaTime) = 0;

	virtual void SetIsHovered(bool newIsHovered) = 0;
	void SetUITag(std::string newTag) { uiTag = newTag; }
protected:
	bool hasRegisteredWithParent = false;
	// Used by the manager to give a visual queue that this element is being hovered
	bool isHovered = false;
	// The tag we send out when we activate the element.
	// Other components can check for this and do something accordingly
	std::string uiTag;

	float halfWidth = 2.6f;
	float halfHeight = 1.2f;

	float inputDelay = 0.3f; // delay between inputs in seconds
	float timeSinceLastInput = 0.0f;

	std::shared_ptr<UIComponent> uiComponent;
	std::shared_ptr<AnimationComponent> animationComponent;
	std::shared_ptr<UIElementManagerComponent> managerComponent;
};