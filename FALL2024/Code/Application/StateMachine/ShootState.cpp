/****************************************************************
// File Name: ShootState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (ShootState core), Alex Humphries (Code refactor)
// Description: An enemy state that handles shooting projectiles
****************************************************************/

#include "precompiled.h"
#include "ShootState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 
#include "Managers/GlobalSoundManager.h"

void ShootState::Enter()
{
    GetEntity().currentStateName = "Shoot";

    GetEntity().ChangeAnimationState("Shoot");

    GlobalSoundManager::Instance().Play("mob10atk.mp3");

    shootTimer = 0.0f;
    shotsFired = 0;
}
void ShootState::Update(float deltaTime)
{
    shootTimer += deltaTime;

    if (shootTimer >= shootInterval) 
    {
        if (targetted) {
            ShootAtTarget(GetEntity().GetTargetPlayer()->GetLocalPosition(), shootSpeed, shootMultiplier);
        }
        else {
            Shoot();
        }
        
        GlobalSoundManager::Instance().Play("15_Impact_flesh_02.mp3");

        shootTimer = 0.0f;
        shotsFired++;

        if (shotsFired >= maxShots) {
            if (GetEntity().DoesStateExist("Seek")) {
                GetEntity().ChangeState("Seek");
            }
            else if (GetEntity().DoesStateExist("Wander")) {
                GetEntity().ChangeState("Wander");
            }
        }
    }

}
void ShootState::Exit()
{

}

void ShootState::Deserialize(const rapidjson::Value& json)
{
    try
    {
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for WanderState: Expected an object.");
        }

        if (json.HasMember("targetted") && json["targetted"].IsBool ()) {
            targetted = json["targetted"].GetBool();
        }
        if (json.HasMember("maxShots") && json["maxShots"].IsNumber()) {
            maxShots = json["maxShots"].GetInt();
        }
        if (json.HasMember("shootSpeed") && json["shootSpeed"].IsNumber()) {
            shootSpeed = json["shootSpeed"].GetFloat();
        }
        if (json.HasMember("shootMultiplier") && json["shootMultiplier"].IsNumber()) {
            shootMultiplier = json["shootMultiplier"].GetFloat();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing WanderState: " << e.what() << std::endl;
        throw;
    }
}
