/****************************************************************
// File Name: WanderState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (Wander core), Jacob Wilburn (Behavior refactor)
// Description: An enemy state that handles wandering / moving randomly
****************************************************************/

#include "precompiled.h"
#include "WanderState.h"
#include "AIEntity.h" 

void WanderState::Enter()
{
	GetEntity().currentStateName = "Wander";

	//GetEntity().ChangeAnimationState("Wander");

	std::uniform_real_distribution<> distr(-5.0f, 5.0f);
	float randomX = distr(randomEngine);
	float randomY = distr(randomEngine);
	wanderDirection = Vector3(randomX, randomY, 0.0f).Normalized();

	std::random_device rd;
	randomEngine.seed(rd());
	std::uniform_real_distribution<> distr2(wanderTimerMin, wanderTimerMax);
	float wanderTimer = distr2(randomEngine);
	currentWanderTimer = wanderTimer;
}

void WanderState::Update(float deltaTime)
{
	if (currentWanderTimer <= 0.0f)
	{
		GetEntity().ChangeState("Idle");
	}

	Vector3 desiredVelocity = wanderDirection * wanderSpeed;

	GetEntity().MoveOwner(desiredVelocity);

	currentWanderTimer -= deltaTime;
}

void WanderState::Exit()
{
}

void WanderState::Deserialize(const rapidjson::Value& json)
{
	try
	{
		if (!json.IsObject()) {
			throw std::invalid_argument("Invalid JSON for WanderState: Expected an object.");
		}

		if (json.HasMember("wanderSpeed") && json["wanderSpeed"].IsNumber()) {
			wanderSpeed = json["wanderSpeed"].GetFloat();
		}
		if (json.HasMember("wanderTimerMin") && json["wanderTimerMin"].IsNumber()) {
			wanderTimerMin = json["wanderTimerMin"].GetFloat();
		}
		if (json.HasMember("wanderTimerMax") && json["wanderTimerMax"].IsNumber()) {
			wanderTimerMax = json["wanderTimerMax"].GetFloat();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing WanderState: " << e.what() << std::endl;
		throw;
	}
}
