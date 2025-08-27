/****************************************************************
// File Name: BossIdleState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An enemy state specific to boss that
// handles moving us to other boss states, (also idles)
****************************************************************/

#include "precompiled.h"
#include "BossIdleState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 


void BossIdleState::Enter()
{
	GetEntity().currentStateName = "BossIdle";
	GetEntity().ChangeAnimationState("Idle");

	stateTimer = 0.0f;
}

void BossIdleState::Update(float deltaTime)
{
	stateTimer += deltaTime;
	if (stateTimer >= stateChangeThreshold) {
		int randomValue = dist(rng);

		if (randomValue < 30) {
			GetEntity().ChangeState("PrepareCharge");
		}
		else if (randomValue < 60) {
			GetEntity().ChangeState("PrepareShoot");
		}
		else if (randomValue < 80){
			GetEntity().ChangeState("PrepareSpawn");
		}
		else {
			if (GetEntity().DoesStateExist("Seek")) {
				GetEntity().ChangeState("Seek");
			}
			else if (GetEntity().DoesStateExist("Wander")) {
				GetEntity().ChangeState("Wander");
			}
		}
		stateTimer = 0.0f;
	}
}

void BossIdleState::Exit()
{
}

void BossIdleState::Deserialize(const rapidjson::Value& json)
{
	try
	{
		if (!json.IsObject()) {
			throw std::invalid_argument("Invalid JSON for WanderState: Expected an object.");
		}

		if (json.HasMember("stateChangeThreshold") && json["stateChangeThreshold"].IsNumber()) {
			stateChangeThreshold = json["stateChangeThreshold"].GetFloat();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing WanderState: " << e.what() << std::endl;
		throw;
	}
}
