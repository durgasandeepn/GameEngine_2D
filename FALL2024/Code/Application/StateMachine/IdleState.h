/****************************************************************
// File Name: IdleState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An enemy state that handles moving us to other enemy states,
// (also idles)
****************************************************************/

#pragma once
#include <iostream>
#include "State.h"

class IdleState : public State {
public:
    IdleState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    float stateTimer = 0.0f;
    float stateChangeThreshold = 1.0f;
};