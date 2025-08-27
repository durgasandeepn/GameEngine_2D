/****************************************************************
// File Name: PrepareSpawnState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An intermediate enemy state that moves us into the spawning state
****************************************************************/

#pragma once

#include "State.h"
class PrepareSpawnState : public State
{
public:
    PrepareSpawnState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    float stateTimer = 0.0f;
};