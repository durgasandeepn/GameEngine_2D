/****************************************************************
// File Name: UIElementComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Base parent component for UI Elements, specific
// elements (like buttons and sliders) extend from this parent class.
****************************************************************/

#include "precompiled.h"
#include "UIElementComponent.h"
#include "CameraComponent.h"

void UIElementComponent::Initialize()
{
	animationComponent = owner->FindComponentInChild<AnimationComponent>();
	if (animationComponent == nullptr)
	{
		std::cerr << "Failed to find AnimationComponent " << std::endl;
	}

	uiComponent = owner->FindComponentInChild<UIComponent>();
	if (uiComponent == nullptr)
	{
		std::cerr << "Failed to find uiComponent " << std::endl;
	}
	SetIsHovered(false);

	timeSinceLastInput = inputDelay;
}

void UIElementComponent::Update(float deltaTime)
{
	if (!hasRegisteredWithParent) {
		owner->SetIsActive(false);
		if (owner->GetParent()) {
			GameObject* parentObject = dynamic_cast<GameObject*>(owner->GetParent());
			if (parentObject) {
				managerComponent = parentObject->FindComponent<UIElementManagerComponent>();
				if (managerComponent) {
					managerComponent->RegisterElement(*this);
				}
			}
		}
		hasRegisteredWithParent = true;
	}

	double mouseX, mouseY;
	Input::Instance().GetMousePosition(mouseX, mouseY);

	// Retrieve the UI camera’s projection matrix.
	Matrix4 projMatrix = uiComponent->GetRenderable()->GetCamera()->GetProjectionMatrix();

	// Compute the world-space boundaries from the projection matrix.
	// These formulas convert the normalized projection values to world coordinates.
	float left = -(projMatrix.GetElement(3, 0) + 1) / projMatrix.GetElement(0, 0);
	float right = (1 - projMatrix.GetElement(3, 0)) / projMatrix.GetElement(0, 0);
	float bottom = -(projMatrix.GetElement(3, 1) + 1) / projMatrix.GetElement(1, 1);
	float top = (1 - projMatrix.GetElement(3, 1)) / projMatrix.GetElement(1, 1);

	float worldX = left + (mouseX + 1) * (right - left) / 2;
	float worldY = bottom + (mouseY + 1) * (top - bottom) / 2;

	if ((worldX >= (owner->GetLocalPosition().x - halfWidth)) &&
		(worldX <= (owner->GetLocalPosition().x + halfWidth)) &&
		(-worldY >= (owner->GetLocalPosition().y+0.25f - halfHeight)) &&
		(-worldY <= (owner->GetLocalPosition().y+0.4f + halfHeight))
		){
		managerComponent->MouseIsHovering(*this);
	}
}

void UIElementComponent::Shutdown()
{
}

void UIElementComponent::Serialize()
{
}

void UIElementComponent::Deserialize(const rapidjson::Value& json)
{
	try {
		// Validate the JSON structure
		if (!json.IsObject()) {
			throw std::invalid_argument("Invalid JSON for UIButtonComponent: Expected an object.");
		}

		if (json.HasMember("uiTag") && json["uiTag"].IsString()) {
			uiTag = json["uiTag"].GetString();
		}
		else {
			throw std::invalid_argument("UIButtonComponent::Deserialize - Missing or invalid 'uiTag'");
		}

		if (json.HasMember("halfWidth") && json["halfWidth"].IsNumber()) {
			halfWidth = json["halfWidth"].GetFloat();
		}

		if (json.HasMember("halfHeight") && json["halfHeight"].IsNumber()) {
			halfHeight = json["halfHeight"].GetFloat();
		}

		if (json.HasMember("inputDelay") && json["inputDelay"].IsNumber()) {
			inputDelay = json["inputDelay"].GetFloat();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing UIButtonComponent: " << e.what() << std::endl;
		throw; // Re-throw the exception after logging
	}
}

void UIElementComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}
