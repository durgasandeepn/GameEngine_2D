/****************************************************************
// File Name: InputCodes
// © 2025 DigiPen (USA) Corporation
// Authors: Team - everyone added keycodes where necessary
// Description: Maps GLWF input codes to different Enum values
****************************************************************/

#pragma once

#include <glfw3.h>

/**
* @brief Enum mapping the different GLFW key codes. These are 1:1 with GLWF key codes: https://www.glfw.org/docs/3.3/group__keys.html
*/
enum class KeyCode
{
    Unknown = -1,
    Space = GLFW_KEY_SPACE,
    Escape = GLFW_KEY_ESCAPE,
    Enter = GLFW_KEY_ENTER,
    Tab = GLFW_KEY_TAB,
    Backspace = GLFW_KEY_BACKSPACE,
    LCtrl = GLFW_KEY_LEFT_CONTROL,
    Left = GLFW_KEY_LEFT,
    Right = GLFW_KEY_RIGHT,
    Up = GLFW_KEY_UP,
    Down = GLFW_KEY_DOWN,
    W = GLFW_KEY_W,
    A = GLFW_KEY_A,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D,
    Q = GLFW_KEY_Q,
    E = GLFW_KEY_E,
    Last = GLFW_KEY_LAST,
    F11 = GLFW_KEY_F11,
    Tilda = GLFW_KEY_GRAVE_ACCENT
};

/**
* @brief Enum mapping the different GLFW mouse buttons. These are 1:1 with GLWF mouse buttons: https://www.glfw.org/docs/latest/group__buttons.html
*/
enum class MouseButton
{
    Left = GLFW_MOUSE_BUTTON_LEFT,
    Right = GLFW_MOUSE_BUTTON_RIGHT,
    Middle = GLFW_MOUSE_BUTTON_MIDDLE,
    Button4 = GLFW_MOUSE_BUTTON_4,
    Button5 = GLFW_MOUSE_BUTTON_5,
};

/**
* @brief Enum mapping the different GLFW gamepad buttons. These are 1:1 with GLWF mouse buttons: https://www.glfw.org/docs/latest/group__gamepad__buttons.html
* glfw number is not working properly
*/
enum class GamepadButton
{
    Button_A = 0,
    Button_B = 1,
    Button_X = 2,
    Button_Y = 3,
    Left_Bumper = 4,
    Right_Bumper = 5,
    Button_Back = 6,
    Button_Start = 7,
    Left_Thumb = 8,
    Right_Thumb = 9,
    Dpad_Up = 10,
    Dpad_Right = 11,
    Dpad_Down = 12,
    Dpad_Left = 13,
    Last_Button = Dpad_Left
};

enum class GamepadAxes
{
    Axis_Left_X = GLFW_GAMEPAD_AXIS_LEFT_X,
    Axis_Left_Y = GLFW_GAMEPAD_AXIS_LEFT_Y,
    Axis_Right_X = GLFW_GAMEPAD_AXIS_RIGHT_X,
    Axis_Right_Y = GLFW_GAMEPAD_AXIS_RIGHT_Y,
    Left_Trigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
    Right_Trigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
};