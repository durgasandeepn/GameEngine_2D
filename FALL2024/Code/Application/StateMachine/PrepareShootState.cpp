/****************************************************************
// File Name: PrepareShootState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An intermediate enemy state that moves us into the shooting state
****************************************************************/

#include "precompiled.h"
#include "PrepareShootState.h"
#include "ShootState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 
void PrepareShootState::Enter()
{
    GetEntity().currentStateName = "PrepareShoot";

    GetEntity().ChangeAnimationState("PrepareShoot");

    stateTimer = 0.0f;
}
void PrepareShootState::Update(float deltaTime)
{
    stateTimer += deltaTime;

    // If 5 seconds have elapsed, change to ChaseState
    if (stateTimer >= 1.0f) {
        int flip = rand() % 2;
		if (flip == 0) {
            if (GetEntity().DoesStateExist("WaveShoot")) {
                GetEntity().ChangeState("WaveShoot");
            }
		}
		else {
			GetEntity().ChangeState("Shoot");
		}
        stateTimer = 0.0f;  // Reset timer so state doesn't change every frame
    }
}
void PrepareShootState::Exit()
{

}

void PrepareShootState::Deserialize(const rapidjson::Value& json)
{
}
