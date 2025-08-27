/****************************************************************
// File Name: PrepareChargeState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An intermediate enemy state that moves us into the charge state
****************************************************************/

#include "precompiled.h"
#include "PrepareChargeState.h"
#include "ChargeState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 
void PrepareChargeState::Enter()
{
    GetEntity().currentStateName = "PrepareCharge";

    GetEntity().ChangeAnimationState("PrepareCharge");

    stateTimer = 0.0f;
}
void PrepareChargeState::Update(float deltaTime)
{
    stateTimer += deltaTime;

    if (stateTimer >= 1.0f) {
        GetEntity().ChangeState("Charge");
        stateTimer = 0.0f;  
    }
}
void PrepareChargeState::Exit()
{

}

void PrepareChargeState::Deserialize(const rapidjson::Value& json)
{
}
