/****************************************************************
// File Name: WanderState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn, Jacob Wilburn
// Description: An enemy state that handles wandering / moving randomly
****************************************************************/
#pragma once
#include <iostream>
#include "State.h"
#include "Math/Vector3.h"

class WanderState : public State {
public:
    WanderState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    std::mt19937 randomEngine;
    float wanderTimerMin;
    float wanderTimerMax;
    float currentWanderTimer = 0.0f;
    Vector3 wanderDirection;
    float wanderSpeed = 2.0f;
};