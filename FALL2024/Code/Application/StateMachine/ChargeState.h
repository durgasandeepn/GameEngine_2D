/****************************************************************
// File Name: ChargeState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (ChargeState core), Jacob Wilburn (Behavior refactor)
// Description: An enemy state that has the enemy charge at a player
****************************************************************/

#pragma once
#include "State.h"
#include "Math/Vector3.h"
class ChargeState : public State
{
public:
    ChargeState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    float chargeSpeed = 1.0f;
    float chargeThreshold = 10.0f;
    bool bulletOnEnter = false;

    Vector3 targetPosition;

    float chargeTimer = 1.0f;
    float currentChargeTimer = 1.0f;
};

