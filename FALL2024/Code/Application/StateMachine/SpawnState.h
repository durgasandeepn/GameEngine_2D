/****************************************************************
// File Name: SpawnState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An enemy state that handles spawning other enemies
****************************************************************/

#pragma once
#include "State.h"
class SpawnState : public State
{
public:
    SpawnState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    void SpawnMinion();

    float stateTimer = 0.0f;
};

