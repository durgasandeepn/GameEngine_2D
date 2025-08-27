/****************************************************************
// File Name: SpawnState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An enemy state that handles spawning other enemies
****************************************************************/

#include "precompiled.h"
#include "SpawnState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 
#include "Dungeon/EnemyCreator.h"
#include "Managers/GameManager.h"

void SpawnState::Enter()
{
    GetEntity().currentStateName = "Spawn";
    GetEntity().ChangeAnimationState("Spawn");
}
void SpawnState::Update(float deltaTime)
{
    SpawnMinion();

    if (GetEntity().DoesStateExist("BossIdle")) {
        GetEntity().ChangeState("BossIdle");
    }
    else if (GetEntity().DoesStateExist("BossIdle")) {
        GetEntity().ChangeState("BossIdle");
    }

}
void SpawnState::Exit()
{

}

void SpawnState::Deserialize(const rapidjson::Value& json)
{
}

void SpawnState::SpawnMinion()
{
    Vector3 enemyPos = GetEntity().GetOwner()->GetLocalPosition();

    EnemyCreator enemyCreator;

    auto ghost1 = enemyCreator.CreateGhostShooter(GameManager::Instance().players, Vector3(2.0f, 2.0f, 0.0f), Vector3(-11.5f, 5.0f, 0.0f));

    ghost1->SetLocalScale(Vector3(2.0f, 2.0f, 0.0f));
    ghost1->SetLocalPosition(Vector3(enemyPos.x, enemyPos.y - 3.0f, 0.0f));
}
