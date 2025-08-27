/****************************************************************
// File Name: InputComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn - base code, Alex Humphries - fixes, refactors, deserializing
// Description: Component dedicated to handling Input
****************************************************************/

#include "precompiled.h"
#include "InputComponent.h"

InputComponent::InputComponent() : controllerId(0)
{
}

void InputComponent::Initialize()
{
}

void InputComponent::Update(float deltaTime)
{
}

void InputComponent::Shutdown()
{
}

void InputComponent::Serialize()
{
}

void InputComponent::Deserialize(const rapidjson::Value& json)
{
	try {
		// Validate the JSON structure
		if (!json.IsObject()) {
			throw std::invalid_argument("Invalid JSON for InputComponent: Expected an object.");
		}

		// actions array
		if (json.HasMember("actions") && json["actions"].IsArray()) {
			const auto& actions = json["actions"].GetArray();
			for (const auto& action : actions) {
				std::string actionName = "";
				int inputType = -1;
				int inputId = -1;
				if (action.HasMember("actionName") && action["actionName"].IsString()) {
					actionName = action["actionName"].GetString();
				}
				else {
					throw std::invalid_argument("InputComponent::Deserialize - Missing or invalid 'actions.actionName");
				}
				if (action.HasMember("inputType") && action["inputType"].IsNumber()) {
					inputType = action["inputType"].GetInt();
				}
				else {
					throw std::invalid_argument("InputComponent::Deserialize - Missing or invalid 'actions.inputType");
				}
				if (action.HasMember("inputId") && action["inputId"].IsNumber()){
					inputId = action["inputId"].GetInt();
				}
				else {
					throw std::invalid_argument("InputComponent::Deserialize - Missing or invalid 'actions.inputId");
				}

				if (actionName != "" && inputType != -1 && inputId != -1) {
					BindActionToInput(actionName, static_cast<InputType>(inputType), inputId);
				}
			}
		}
		else {
			throw std::invalid_argument("InputComponent::Deserialize - Missing or invalid 'actions'");
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing InputComponent: " << e.what() << std::endl;
		throw; // Re-throw the exception after logging
	}
}

void InputComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void InputComponent::SetControllerId(int newControllerId)
{
	controllerId = newControllerId;
}

void InputComponent::BindActionToInput(std::string actionName, InputType type, int inputId)
{
	actions[actionName].BindInput(type, inputId);
}

bool InputComponent::IsActionPressed(std::string actionName)
{
	auto it = actions.find(actionName);
	if (it != actions.end()) {
		return it->second.IsPressed(controllerId);
	}
	return false;
}

bool InputComponent::IsActionPressed(std::string actionName, int inputId)
{
	auto it = actions.find(actionName);
	if (it != actions.end()) {
		return it->second.IsPressed(inputId);
	}
	return false;
}

bool InputComponent::IsActionReleased(std::string actionName)
{
	auto it = actions.find(actionName);
	if (it != actions.end()) {
		return it->second.IsReleased(controllerId);
	}
	return false;
}

bool InputComponent::IsActionHeld(std::string actionName)
{
	auto it = actions.find(actionName);
	if (it != actions.end()) {
		return it->second.IsHeld(controllerId);
	}
	return false;
}

float InputComponent::GetAxisValue(std::string actionName)
{
	auto it = actions.find(actionName);
	if (it != actions.end()) {
		return it->second.GetAxisValue(controllerId);
	}
	return 0.0f;
}
