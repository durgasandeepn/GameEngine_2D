/****************************************************************
// File Name: ShootState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (ShootState core), Alex Humphries (Code refactor)
// Description: An enemy state that handles shooting projectiles
****************************************************************/

#pragma once
#include "precompiled.h"
#include "State.h"
#include "Math/Vector3.h"
class ShootState : public State
{
public:
    ShootState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:

    bool targetted = true; // Whether or not we shoot at target player
    float shootTimer = 0.0f;
    int shotsFired = 0;
    float shootInterval = 1.0f / 2.0f; 
    int maxShots = 4;

    float shootSpeed = 5.0f;
    float shootMultiplier = 1.0f;
};

