/****************************************************************
// File Name: StrafeShootState
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries (StrafeShoot core), Jacob Wilburn (Behavior refactor)
// Description: An enemy state that handles shooting while moving
****************************************************************/

#include "precompiled.h"
#include "StrafeShootState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h"
#include "Managers/GlobalSoundManager.h"

void StrafeShootState::Enter()
{
    GetEntity().currentStateName = "StrafeShoot";

    GetEntity().ChangeAnimationState("Shoot");

    GlobalSoundManager::Instance().Play("mob10atk.mp3");

    shootTimer = 0.0f;
    shotsFired = 0;
    strafeAngle = 0.0f; // Start from a neutral position
    directionTimer = 1.0f;

    std::random_device rd;
    randomEngine.seed(rd());
    
    GetEntity().CheckAndAssignNewTarget();

    if (targetted) {
        strafeRadius = 25.0f; // Adjust for desired strafing distance
        strafeSpeed = 3.0f;  // Adjust speed of strafing
    }
    
}

void StrafeShootState::Update(float deltaTime)
{
    shootTimer += deltaTime;

	std::uniform_int_distribution<> distr2(0, 100);
	int randomNum = distr2(randomEngine);
    if (randomNum <= 20) {
		moveToPlayer = true;
	}
    else {
        moveToPlayer = false;
    }

    if (directionTimer > 1.0f) {
        if (moveToPlayer) {
			moveDirection = (GetEntity().GetTargetPlayer()->GetLocalPosition() - GetEntity().GetOwner()->GetLocalPosition()).Normalized();
        }
        else {
            std::uniform_real_distribution<> distr(-5.0f, 5.0f);
            float randomX = distr(randomEngine);
            float randomY = distr(randomEngine);
            moveDirection = Vector3(randomX, randomY, 0.0f).Normalized();
        }
		directionTimer = 0.0f;
    }
    else {
		directionTimer += deltaTime;
    }
    
    Vector3 desiredVelocity = moveDirection * moveSpeed;
    GetEntity().MoveOwner(desiredVelocity);
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

void StrafeShootState::Exit()
{
}

void StrafeShootState::Deserialize(const rapidjson::Value& json)
{
    try
    {
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for StrafeShootState: Expected an object.");
        }

        if (json.HasMember("targetted") && json["targetted"].IsBool()) {
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
        std::cerr << "Error deserializing StrafeShootState: " << e.what() << std::endl;
        throw;
    }
}
