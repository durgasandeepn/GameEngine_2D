/****************************************************************
// File Name: BossIdleState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An enemy state specific to boss that 
// handles moving us to other boss states, (also idles)
****************************************************************/

#pragma once
#include <iostream>
#include "State.h"

class BossIdleState : public State {
public:
    BossIdleState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    float stateTimer = 0.0f;
    float stateChangeThreshold = 1.0f;

    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist{ 0, 99 }; 
};