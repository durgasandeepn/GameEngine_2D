/****************************************************************
// File Name: InputAction
// © 2025 DigiPen (USA) Corporation
// Authors:  Ju-ve Chankasemporn
// Description: Mapping input from GLFW to Gamepad or Mouse and Keyboard
// controls. Also can work for multiple controller
****************************************************************/

#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include "Input.h"

enum class InputType {
    Keyboard,
    MouseButton,
    GamepadButton
};

struct InputBinding {
    InputType type;
    //for keycode, mouse button, or gamepad button (int type)
    int inputID;
};

class InputAction
{
public: 
    InputAction();
    void BindInput(InputType type, int inputID);
    bool IsPressed(int controllerId);
    bool IsReleased(int controllerId);
    bool IsHeld(int controllerId);
    float GetAxisValue(int controllerId);
private:
    //this allows multiple inputIds for the same input action
    std::vector<InputBinding> bindings;
    bool CheckIsPressedState(const InputBinding& binding, int controllerId);
    bool CheckIsReleasedState(const InputBinding& binding, int controllerId);
    bool CheckIsHeldState(const InputBinding& binding, int controllerId);
};

