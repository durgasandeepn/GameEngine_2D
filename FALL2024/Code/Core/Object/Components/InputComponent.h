/****************************************************************
// File Name: InputComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn - base code, Alex Humphries - fixes, refactors, deserializing
// Description: Component dedicated to handling Input
****************************************************************/

#pragma once
#include "Component.h"
#include "Input/InputAction.h"
class InputComponent : public Component
{
public:
	InputComponent();
	~InputComponent() = default;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json) override;
	void Configure(const std::unordered_map<std::string, std::any>& properties) override;

	void SetControllerId(int newControllerId);
	void BindActionToInput(std::string actionName, InputType type, int inputId);
	bool IsActionPressed(std::string actionName);
	bool IsActionPressed(std::string actionName, int inputId);
	bool IsActionReleased(std::string actionName);
	bool IsActionHeld(std::string actionName);
	float GetAxisValue(std::string actionName);

private:
	int controllerId;
	std::unordered_map<std::string, InputAction> actions;
};

