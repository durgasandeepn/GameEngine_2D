/****************************************************************
// File Name: Input
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors,
// Ju-ve Chankasemporn - worked with controller and InputActions
// Description: Handles input for engine.
// Uses GLFW's callbacks in order to get inputs on demand
****************************************************************/

#pragma once
#include "GameWindow.h"
#include <unordered_map>
#include "InputCodes.h"
#include <array>
// TODO - Possible optimization is making this dynamic
// based on how many controllers connected
#define MAX_GAMEPADS 4
/**
* @brief Enum describing the different cursor "mode{s}". These are 1:1 with GLWF cursor modes. Ref: https://www.glfw.org/docs/3.3/group__input.html
*/
enum class CursorMode
{
	Normal = GLFW_CURSOR_NORMAL, // Cursor is visible as normal
	Hidden = GLFW_CURSOR_HIDDEN, // hides the cursor in the content area (window) but doesn't lock it
	Disabled = GLFW_CURSOR_DISABLED // hides and grabs (locks) the cursor
};

//use for checking the current state of the buttons only
enum class ButtonStateChecker {
	Pressed,
	Released,
	Held
};

struct ButtonState {
	bool pressed = false;   //true - only on the frame the key is first pressed
	bool released = false;  //true - only on the frame the key is released
	bool held = false;      //true - while the key is being held
};

class Input
{
public:
	static Input& Instance() {
		static Input instance;
		return instance;
	}
	
	void Initialize(GameWindow* window);
	// Called by game loop
	void Update();

	/* Keyboard */
	bool IsKeyPressed(KeyCode key);
	bool IsKeyReleased(KeyCode key);
	bool IsKeyHeld(KeyCode key);

	/* Mouse */
	bool IsMouseButtonPressed(MouseButton button);
	bool IsMouseButtonReleased(MouseButton button);
	bool IsMouseButtonHeld(MouseButton button);

	void GetMousePosition(double& x, double& y);
	double GetCurrMouseX() const { return currentMouseX; }
	double GetCurrMouseY() const { return currentMouseY; }
	double GetPrevMouseX() const { return prevMouseX; }
	double GetPrevMouseY() const { return prevMouseY; }
	void SetCursorMode(CursorMode mode);

	/* Gamepad */
	bool IsGamepadButtonPressed(GamepadButton button, int controllerId = 0);
	bool IsGamepadButtonReleased(GamepadButton button, int controllerId = 0);
	bool IsGamepadButtonHeld(GamepadButton button, int controllerId = 0);
	float GetGamepadAxisValue(GamepadAxes axisButton, int controllerId = 0);
private:
	Input() = default;
	~Input();

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	void UpdateKeyStates();
	void UpdateMouseStates();
	void InitGamepads();
	void UpdateGamepadStates();
	bool GetGamepadButtonState(int button, int controllerId, ButtonStateChecker state);

	GameWindow* pWindow{ nullptr };

	std::unordered_map<int, ButtonState> keyStates; // Handles keyboard key states
	std::unordered_map<int, ButtonState> mouseButtonStates; // Handles mouse button states (left click, etc.)
	std::array<std::unordered_map<int, ButtonState>, MAX_GAMEPADS> gamepadButtons;
	std::array<std::unordered_map<int, float>, MAX_GAMEPADS> gamepadAxes;

	double currentMouseX{0.0f};
	double currentMouseY{0.0f};
	double prevMouseX{0.0f};
	double prevMouseY{0.0f};

	static void JoystickCallback(int jid, int event);
};