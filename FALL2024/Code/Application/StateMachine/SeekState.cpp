/****************************************************************
// File Name: SeekState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (SeekState core), Jacob Wilburn (Behavior overhaul)
// Description: An enemy state that handles seeking after players
****************************************************************/

#include "precompiled.h"
#include "SeekState.h"
#include "AIEntity.h" 

void SeekState::Enter()
{
	GetEntity().currentStateName = "Seek";
	GetEntity().ChangeAnimationState("Idle");
	currentSeekTimer = seekTimer;
}

void SeekState::Update(float deltaTime)
{
	if (currentSeekTimer <= 0.0f)
	{
		if (GetEntity().DoesStateExist("Charge")) {
			GetEntity().ChangeState("Charge");
		}
		else if (GetEntity().DoesStateExist("BossIdle")) {
			GetEntity().ChangeState("BossIdle");
		}
		else if (GetEntity().DoesStateExist("Idle")) {
			GetEntity().ChangeState("Idle");
		}
	}

	if (GetEntity().GetTargetPlayer() == nullptr)
	{
		return;
	}

	Vector3 currentPos = GetEntity().GetOwner()->GetLocalPosition();
	Vector3 direction = (GetEntity().GetTargetPlayer()->GetLocalPosition() - currentPos).Normalized();

	Vector3 desiredVelocity = direction * seekSpeed;

	GetEntity().MoveOwner(desiredVelocity);

	currentSeekTimer -= deltaTime;
}

void SeekState::Exit()
{
}

void SeekState::Deserialize(const rapidjson::Value& json)
{
	try
	{
		if (!json.IsObject()) {
			throw std::invalid_argument("Invalid JSON for WanderState: Expected an object.");
		}

		if (json.HasMember("seekSpeed") && json["seekSpeed"].IsNumber()) {
			seekSpeed = json["seekSpeed"].GetFloat();
		}

		if (json.HasMember("seekTimer") && json["seekTimer"].IsNumber()) {
			seekTimer = json["seekTimer"].GetFloat();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing WanderState: " << e.what() << std::endl;
		throw;
	}
}
