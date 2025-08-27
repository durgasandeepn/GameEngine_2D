/****************************************************************
// File Name: PrepareSpawnState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An intermediate enemy state that moves us into the spawning state
****************************************************************/

#include "precompiled.h"
#include "PrepareSpawnState.h"
#include "SpawnState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 
void PrepareSpawnState::Enter()
{
    GetEntity().currentStateName = "PrepareSpawn";
    GetEntity().ChangeAnimationState("PrepareSpawn");

    stateTimer = 0.0f;
}
void PrepareSpawnState::Update(float deltaTime)
{
    stateTimer += deltaTime;

    if (stateTimer >= 1.0f) {
        GetEntity().ChangeState("Spawn");
        stateTimer = 0.0f;  
    }
}
void PrepareSpawnState::Exit()
{

}

void PrepareSpawnState::Deserialize(const rapidjson::Value& json)
{
}
