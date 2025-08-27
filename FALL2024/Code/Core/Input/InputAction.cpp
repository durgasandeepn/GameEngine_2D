/****************************************************************
// File Name: InputAction
// © 2025 DigiPen (USA) Corporation
// Authors:  Ju-ve Chankasemporn
// Description: Mapping input from GLFW to Gamepad or Mouse and Keyboard
// controls. Also can work for multiple controller
****************************************************************/

#include "precompiled.h"
#include "InputAction.h"

InputAction::InputAction()
{

}

void InputAction::BindInput(InputType type, int inputID)
{
	bindings.push_back({ type, inputID });
}

bool InputAction::IsPressed(int controllerId)
{
	for (const auto& binding : bindings) {
		if (CheckIsPressedState(binding, controllerId)) {
			return true;
		}
	}
	return false;
}

bool InputAction::IsReleased(int controllerId)
{
	for (const auto& binding : bindings) {
		if (CheckIsReleasedState(binding, controllerId)) {
			return true;
		}
	}
	return false;
}

bool InputAction::IsHeld(int controllerId)
{
	for (const auto& binding : bindings) {
		if (CheckIsHeldState(binding, controllerId)) {
			return true;
		}
	}
	return false;
}

float InputAction::GetAxisValue(int controllerId)
{
	for (const auto& binding : bindings) {
		return Input::Instance().GetGamepadAxisValue(static_cast<GamepadAxes>(binding.inputID), controllerId);
	}
	return 0.0f;
}

bool InputAction::CheckIsPressedState(const InputBinding& binding, int controllerId)
{
	switch (binding.type) {
	case InputType::Keyboard:
		return Input::Instance().IsKeyPressed(static_cast<KeyCode>(binding.inputID));
	case InputType::MouseButton:
		return Input::Instance().IsMouseButtonPressed(static_cast<MouseButton>(binding.inputID));
	case InputType::GamepadButton:
		return Input::Instance().IsGamepadButtonPressed(static_cast<GamepadButton>(binding.inputID), controllerId);
	default:
		return false;
	}
}

bool InputAction::CheckIsReleasedState(const InputBinding& binding, int controllerId)
{
	switch (binding.type) {
	case InputType::Keyboard:
		return Input::Instance().IsKeyReleased(static_cast<KeyCode>(binding.inputID));
	case InputType::MouseButton:
		return Input::Instance().IsMouseButtonReleased(static_cast<MouseButton>(binding.inputID));
	case InputType::GamepadButton:
		return Input::Instance().IsGamepadButtonReleased(static_cast<GamepadButton>(binding.inputID), controllerId);
	default:
		return false;
	}
}

bool InputAction::CheckIsHeldState(const InputBinding& binding, int controllerId)
{
	switch (binding.type) {
	case InputType::Keyboard:
		return Input::Instance().IsKeyHeld(static_cast<KeyCode>(binding.inputID));
	case InputType::MouseButton:
		return Input::Instance().IsMouseButtonHeld(static_cast<MouseButton>(binding.inputID));
	case InputType::GamepadButton:
		return Input::Instance().IsGamepadButtonHeld(static_cast<GamepadButton>(binding.inputID), controllerId);
	default:
		return false;
	}
}
