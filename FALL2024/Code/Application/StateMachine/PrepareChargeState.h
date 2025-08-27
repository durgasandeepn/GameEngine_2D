/****************************************************************
// File Name: PrepareChargeState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An intermediate enemy state that moves us into the charge state
****************************************************************/
#pragma once
#include <iostream>
#include "State.h"

class PrepareChargeState : public State {
public:
    PrepareChargeState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    float stateTimer = 0.0f;
};