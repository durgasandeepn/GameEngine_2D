/****************************************************************
// File Name: Input
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors,
// Ju-ve Chankasemporn - worked with controller and InputActions
// Description: Handles input for engine.
// Uses GLFW's callbacks in order to get inputs on demand
****************************************************************/

#include "precompiled.h"
#include "Input.h"

Input::~Input()
{
	glfwSetInputMode(pWindow->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::Initialize(GameWindow* window)
{
	this->pWindow = window;
	glfwSetJoystickCallback(JoystickCallback);
	InitGamepads();
}

void Input::InitGamepads()
{
	for (int gamepadId = GLFW_JOYSTICK_1; gamepadId < MAX_GAMEPADS; gamepadId++)
	{
		for (int button = 0; button < (int)GamepadButton::Last_Button + 1; button++) {
			if (gamepadButtons[gamepadId].find(button) == gamepadButtons[gamepadId].end()) {
				gamepadButtons[gamepadId][button] = ButtonState();
			}
		}

		for (int axis = 0; axis < GLFW_GAMEPAD_AXIS_LAST + 1; axis++) {
			if (gamepadAxes[gamepadId].find(axis) == gamepadAxes[gamepadId].end()) {
				gamepadAxes[gamepadId][axis] = 0.0f;
			}
		}
	}
}

void Input::Update()
{
	UpdateKeyStates();
	UpdateMouseStates();
	UpdateGamepadStates();
}

void Input::UpdateKeyStates()
{
	for (auto& [key, state] : keyStates) {
		//reset the states for the new frame
		state.pressed = false;
		state.released = false;

		//get the current key state
		int glfwState = glfwGetKey(pWindow->GetNativeWindow(), key);

		if (glfwState == GLFW_PRESS) {
			if (!state.held) {
				state.pressed = true;
			}
			state.held = true;
		}
		else if (glfwState == GLFW_RELEASE) {
			if (state.held) {
				state.released = true;
			}
			state.held = false;
		}
	}
}

void Input::UpdateMouseStates()
{
	for (auto& [key, state] : mouseButtonStates) {
		//reset the states for the new frame
		state.pressed = false;
		state.released = false;

		//get the current key state
		int glfwState = glfwGetMouseButton(pWindow->GetNativeWindow(), key);

		if (glfwState == GLFW_PRESS) {
			if (!state.held) {
				state.pressed = true;
			}
			state.held = true;
		}
		else if (glfwState == GLFW_RELEASE) {
			if (state.held) {
				state.released = true;
			}
			state.held = false;
		}
	}

	prevMouseX = currentMouseX;
	prevMouseY = currentMouseY;

	GetMousePosition(currentMouseX, currentMouseY);
}

void Input::UpdateGamepadStates()
{
	for (int gamepadId = GLFW_JOYSTICK_1; gamepadId < MAX_GAMEPADS; gamepadId++) {
		if (glfwJoystickPresent(gamepadId)) {
			//handle buttons
			int buttonCount;
			const unsigned char* buttons = glfwGetJoystickButtons(gamepadId, &buttonCount);

			//get std::unorderedmap gamepad's button states from the array
			auto& buttonsState = gamepadButtons[gamepadId];

			for (auto& [button, state] : buttonsState) {
				//reset the states for the new frame
				state.pressed = false;
				state.released = false;

				//check if the button index is within the range of available buttons
				if (button < buttonCount) {
					if (buttons[button] == GLFW_PRESS) {
						//use this for debugging buttons
						std::cout << "button: " << button << std::endl;
						if (!state.held) {
							state.pressed = true;
						}
						state.held = true;
					}
					else if (buttons[button] == GLFW_RELEASE) {
						if (state.held) {
							state.released = true;
						}
						state.held = false;
					}
				}
			}

			//handle axes
			int axisCount;
			const float* axes = glfwGetJoystickAxes(gamepadId, &axisCount);

			auto& axesState = gamepadAxes[gamepadId];
			for (int axis = 0; axis < axisCount; axis++) {
				axesState[axis] = axes[axis];
			}
		}
	}
}

bool Input::IsKeyPressed(KeyCode key)
{
	int glfwKey = static_cast<int>(key);
	return keyStates[glfwKey].pressed;
}

bool Input::IsKeyReleased(KeyCode key)
{
	int glfwKey = static_cast<int>(key);
	return keyStates[glfwKey].released;
}

bool Input::IsKeyHeld(KeyCode key)
{
	int glfwKey = static_cast<int>(key);
	return keyStates[glfwKey].held;
}

bool Input::IsMouseButtonPressed(MouseButton button)
{
	int glfwMouseButton = static_cast<int>(button);
	return mouseButtonStates[glfwMouseButton].pressed;
}

bool Input::IsMouseButtonReleased(MouseButton button)
{
	int glfwMouseButton = static_cast<int>(button);
	return !mouseButtonStates[glfwMouseButton].released;
}

bool Input::IsMouseButtonHeld(MouseButton button)
{
	int glfwMouseButton = static_cast<int>(button);
	return mouseButtonStates[glfwMouseButton].held;
}

void Input::GetMousePosition(double& x, double& y)
{
	// Stores the position in x and y
	double mouseX;
	double mouseY;
	glfwGetCursorPos(pWindow->GetNativeWindow(), &mouseX, &mouseY);

	x = (2 * mouseX / pWindow->GetWidth()) - 1;
	y = (2 * mouseY / pWindow->GetHeight()) - 1;
}

void Input::SetCursorMode(CursorMode mode)
{
	glfwSetInputMode(pWindow->GetNativeWindow(), GLFW_CURSOR, static_cast<int>(mode));
}

bool Input::IsGamepadButtonPressed(GamepadButton button, int playerId)
{
	int glfwGamepadButton = static_cast<int>(button);
	return GetGamepadButtonState(glfwGamepadButton, playerId, ButtonStateChecker::Pressed);
}

bool Input::IsGamepadButtonReleased(GamepadButton button, int playerId)
{
	int glfwGamepadButton = static_cast<int>(button);
	return GetGamepadButtonState(glfwGamepadButton, playerId, ButtonStateChecker::Released);
}

bool Input::IsGamepadButtonHeld(GamepadButton button, int playerId)
{
	int glfwGamepadButton = static_cast<int>(button);
	return GetGamepadButtonState(glfwGamepadButton, playerId, ButtonStateChecker::Held);
}

float Input::GetGamepadAxisValue(GamepadAxes axisButton, int playerId)
{
	int glfwGamepadAxis = static_cast<int>(axisButton);

	int gamepadId = GLFW_JOYSTICK_1 + playerId;

	if (glfwJoystickPresent(gamepadId))
	{
		//get the gamepad's axes state
		auto& axesState = gamepadAxes[gamepadId];

		auto it = axesState.find(glfwGamepadAxis);
		if (it != axesState.end())
		{
			return it->second; 
		}
	}

	return 0.0f;
}

bool Input::GetGamepadButtonState(int button, int playerId, ButtonStateChecker state)
{
	int gamepadId = GLFW_JOYSTICK_1 + playerId;

	if (glfwJoystickPresent(gamepadId))
	{
		//get std::unorderedmap gamepad's button states from the array
		auto& buttonsState = gamepadButtons[gamepadId];

		//check if the button exists
		auto it = buttonsState.find(button);
		if (it != buttonsState.end()) {
			const ButtonState& keyState = it->second;

			switch (state)
			{
			case ButtonStateChecker::Released:
				return keyState.released;
			case ButtonStateChecker::Held:
				return keyState.held;
			case ButtonStateChecker::Pressed:
				return keyState.pressed;
			default:
				return false;
			}
		}
	}

	//no controller or button found
	return false;
}

void Input::JoystickCallback(int jid, int event) {
	
	Input& input = Input::Instance();

	if (event == GLFW_CONNECTED) {
		std::cout << "Joystick " << jid << " connected\n";
	}
	else if (event == GLFW_DISCONNECTED) {
		std::cout << "Joystick " << jid << " disconnected\n";
	}
}