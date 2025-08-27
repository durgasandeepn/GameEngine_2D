/****************************************************************
// File Name: ChargeState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (ChargeState core), Jacob Wilburn (Behavior refactor)
// Description: An enemy state that has the enemy charge at a player
****************************************************************/

#include "precompiled.h"
#include "ChargeState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 

void ChargeState::Enter()
{
    GetEntity().currentStateName = "Charge";
    GetEntity().ChangeAnimationState("Charge");

    // TODO put this into a different state called like "ChargeShoot"
    if (bulletOnEnter) {
        Shoot();
    }
    currentChargeTimer = chargeTimer;
	GetEntity().CheckAndAssignNewTarget();
	targetPosition = GetEntity().GetTargetPlayer()->GetLocalPosition();
}
void ChargeState::Update(float deltaTime)
{
    /*if (GetEntity().GetTargetPlayer() == nullptr)
    {
        return;
    }*/

    Vector3 currentPos = GetEntity().GetOwner()->GetLocalPosition();
    Vector3 direction = (targetPosition - currentPos).Normalized();

    Vector3 desiredVelocity = direction * chargeSpeed;
    GetEntity().MoveOwner(desiredVelocity);

    currentPos = GetEntity().GetOwner()->GetLocalPosition();
    Vector3 diff = targetPosition - currentPos;
    if (diff.Magnitude() <= 0.1f || currentChargeTimer <= 0.0f)
    {
        if (GetEntity().DoesStateExist("BossIdle")) {
            GetEntity().ChangeState("BossIdle");
        }
        else if (GetEntity().DoesStateExist("Idle")) {
            GetEntity().ChangeState("Idle");
        }
    }

    currentChargeTimer -= deltaTime;
}
void ChargeState::Exit()
{
    if (bulletOnEnter) {
        Shoot();
    }
}

void ChargeState::Deserialize(const rapidjson::Value& json)
{
    try
    {
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for ChargeState: Expected an object.");
        }

        if (json.HasMember("chargeSpeed") && json["chargeSpeed"].IsFloat()) {
            chargeSpeed = json["chargeSpeed"].GetFloat();
        }

        if (json.HasMember("bulletOnEnter") && json["bulletOnEnter"].IsBool()) {
            bulletOnEnter = json["bulletOnEnter"].GetBool();
        }

        if (json.HasMember("chargeThreshold") && json["chargeThreshold"].IsNumber()) {
            chargeThreshold = json["chargeThreshold"].GetFloat();
        }

        if (json.HasMember("chargeTimer") && json["chargeTimer"].IsNumber()) {
            chargeTimer = json["chargeTimer"].GetFloat();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing ChargeState: " << e.what() << std::endl;
        throw;
    }
}