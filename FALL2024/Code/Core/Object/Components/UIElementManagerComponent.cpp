/****************************************************************
// File Name: ElementManagerComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Handles input in relation to a series of elements
// registered as children of the owning object.
// Used in menus to handle input / button management (button indices).
****************************************************************/

#include "precompiled.h"
#include "UIElementManagerComponent.h"
#include "UIButtonComponent.h"
#include "Object/GameObject.h"
#include "Managers/GlobalSoundManager.h"

void UIElementManagerComponent::Initialize()
{
}

void UIElementManagerComponent::Update(float deltaTime)
{
	if (elements.size() <= 0) return;
	if (!initialLayoutSet) {
		SetLayout(deltaTime);
		initialLayoutSet = true;
	}

	hoverDelay -= deltaTime;

	if (Input::Instance().IsKeyPressed(KeyCode::Up) ||
		Input::Instance().IsKeyPressed(KeyCode::W) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Dpad_Up, 0) ||
		(Input::Instance().GetGamepadAxisValue(GamepadAxes::Axis_Left_Y, 0) < -0.5f && hoverDelay <= 0.0f)) {
		elements[elementIndex]->SetIsHovered(false);
		elementIndex--;
		if (elementIndex < 0) elementIndex = elements.size() - 1;
		hoverDelay = hoverCooldown;

		// TODO this is not great practice, a core system referencing an application system
		// Fix when not rushing or if this breaks something
		GlobalSoundManager::Instance().Play("select_007.mp3");
	}
	if (Input::Instance().IsKeyPressed(KeyCode::Down) ||
		Input::Instance().IsKeyPressed(KeyCode::S) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Dpad_Down, 0) ||
		(Input::Instance().GetGamepadAxisValue(GamepadAxes::Axis_Left_Y, 0) > 0.5f && hoverDelay <= 0.0f)) {
		elements[elementIndex]->SetIsHovered(false);
		elementIndex++;
		if (elementIndex > elements.size() - 1) elementIndex = 0;
		hoverDelay = hoverCooldown;

		// Same here
		GlobalSoundManager::Instance().Play("select_007.mp3");
	}

	elements[elementIndex]->SetIsHovered(true);

	elements[elementIndex]->HandleInput(deltaTime);
}

void UIElementManagerComponent::Shutdown()
{
}

void UIElementManagerComponent::Serialize()
{
}

void UIElementManagerComponent::Deserialize(const rapidjson::Value& json)
{
	try {
		// Validate the JSON structure
		if (!json.IsObject()) {
			throw std::invalid_argument("Invalid JSON for UIElementManagerComponent: Expected an object.");
		}

		if (json.HasMember("startX") && json["startX"].IsNumber()) {
			startX = json["startX"].GetFloat();
		}

		if (json.HasMember("startY") && json["startY"].IsNumber()) {
			startY = json["startY"].GetFloat();
		}

		if (json.HasMember("elementMargin") && json["elementMargin"].IsNumber()) {
			elementMargin = json["elementMargin"].GetFloat();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing UIElementManagerComponent: " << e.what() << std::endl;
		throw; // Re-throw the exception after logging
	}
}

void UIElementManagerComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void UIElementManagerComponent::SetLayout(float deltaTime)
{

	for (size_t i = 0; i < elements.size(); ++i)
	{
		float posY = startY - i * (elements[i]->GetOwner()->GetLocalScale().y + elementMargin);
		elements[i]->GetOwner()->SetLocalPosition(Vector3(startX, posY, 0.0f));
		// Ensure they're in the right pos
		elements[i]->GetOwner()->Update(deltaTime);
		elements[i]->GetOwner()->SetIsActive(true);
	}

	// Ensure first button is hovered initially
	elementIndex = 0;
	elements[elementIndex]->SetIsHovered(true);
}

void UIElementManagerComponent::MouseIsHovering(UIElementComponent& elementHovered)
{
	for (size_t i = 0; i < elements.size(); ++i)
	{
		if (elements[i] == &elementHovered) {
			elementIndex = i;
		}
		else {
			elements[i]->SetIsHovered(false);
		}
	}
}