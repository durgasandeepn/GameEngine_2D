/****************************************************************
// File Name: StrafeShootState
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries, Jacob Wilburn
// Description: An enemy state that handles shooting while moving
****************************************************************/

#pragma once
#include "precompiled.h"
#include "State.h"
#include "Math/Vector3.h"
class StrafeShootState : public State
{
public:
    StrafeShootState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:

    bool targetted = true; // Whether or not we shoot at target player
    float shootTimer = 0.0f;
    int shotsFired = 0;
    float shootInterval = 1.0f;
    int maxShots = 5;

    float strafeAngle = 0.0f;
    float strafeRadius = 5.0f;
    float strafeSpeed = 1.5f;

    float shootSpeed = 5.0f;
    float shootMultiplier = 1.0f;

    Vector3 moveDirection;
    float moveSpeed = 2.0f;
    float directionTimer;
    bool moveToPlayer;
    std::mt19937 randomEngine;

};

