/****************************************************************
// File Name: IdleState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: An enemy state that handles moving us to other enemy states,
// (also idles)
****************************************************************/

#include "precompiled.h"
#include "IdleState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 

void IdleState::Enter()
{
    GetEntity().currentStateName = "Idle";
	GetEntity().ChangeAnimationState("Idle");

	stateTimer = 0.0f;
}
void IdleState::Update(float deltaTime)
{
	if (GetEntity().DoesStateExist("Charge")) {
		
		if (GetEntity().DoesStateExist("Seek")) {
			GetEntity().ChangeState("Seek");
		}
		else if (GetEntity().DoesStateExist("Wander")) {
			GetEntity().ChangeState("Wander");
		}
		
	}
	stateTimer += deltaTime;
	if (stateTimer >= stateChangeThreshold) {
		if (GetEntity().DoesStateExist("Shoot")) {
			GetEntity().ChangeState("Shoot");
		}
		else if (GetEntity().DoesStateExist("StrafeShoot")) {
			GetEntity().ChangeState("StrafeShoot");
		}
		else if (GetEntity().DoesStateExist("WaveShoot")) {
			std::srand(static_cast<unsigned int>(std::time(0)));

			// Generate a random number: 0 or 1
			int flip = rand() % 10; // values 0–9

			if (flip < 4) {
				GetEntity().ChangeState("WaveShoot");
			}
			else {
				if (GetEntity().DoesStateExist("Wander")) {
					GetEntity().ChangeState("Wander");
				}
			}
		}
	}

}
void IdleState::Exit()
{

}

void IdleState::Deserialize(const rapidjson::Value& json)
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
