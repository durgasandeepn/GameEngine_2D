/****************************************************************
// File Name: WaveShootState
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: An enemy state that handles shooting in a spiral /
// wave pattern
****************************************************************/

#pragma once
#include "precompiled.h"
#include "State.h"
#include "Math/Vector3.h"
class WaveShootState : public State
{
public:
    WaveShootState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    float shootTimer = 0.0f;
    int wavesFired = 0;
    float shootInterval = 1.0f / 2.0f;
    int maxWaves = 4;
    int waveShootIndex = 0;

    float shootSpeed = 5.0f;
};