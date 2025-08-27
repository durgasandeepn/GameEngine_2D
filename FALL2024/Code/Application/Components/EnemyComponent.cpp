/****************************************************************
// File Name: EnemyComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries (State System Integration), Ju-ve Chankasemporn (EnemyComponent Core)
// Description: Base component for enemies, initializing the AI entity and its states
****************************************************************/

#include "precompiled.h"
#include "EnemyComponent.h"
#include "Managers/GameManager.h"
#include "Dungeon/EnemyCreator.h"
#include "Statemachine/IdleState.h"
#include "StateMachine/BossIdleState.h"
#include "Statemachine/PrepareChargeState.h"
#include "Statemachine/PrepareShootState.h"
#include "Statemachine/PrepareSpawnState.h"
#include "StateMachine/SpawnState.h"
#include "Statemachine/ShootState.h"
#include "StateMachine/StrafeShootState.h"
#include "Statemachine/ChargeState.h"
#include "StateMachine/SeekState.h"
#include "StateMachine/WanderState.h"
#include "StateMachine/WaveShootState.h"
EnemyComponent::EnemyComponent()
{
	aiEntity = std::make_shared<AIEntity>();
}
void EnemyComponent::Initialize()
{
	if (aiEntity) {
		aiEntity->SetOwner(owner);
		aiEntity->Initialize();
	}
}

void EnemyComponent::Update(float deltaTime)
{
	if (aiEntity) 
	{
		aiEntity->Update(deltaTime);
	}
}

void EnemyComponent::Shutdown()
{

}

void EnemyComponent::Serialize()
{

}

void EnemyComponent::Deserialize(const rapidjson::Value& json)
{
	// Find the states and their properties here, add them to the state map
	// in the aiEntity
    try
    {
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for EnemyComponent: Expected an object.");
        }
		if (json.HasMember("initialState") && json["initialState"].IsString()) {
			aiEntity->SetInitialState(json["initialState"].GetString());
		}
		if (json.HasMember("states") && json["states"].IsArray()) {
			const auto& states = json["states"].GetArray();
			for (const auto& state : states) {
				if (!state.IsObject() || !state.HasMember("name") || !state["name"].IsString() || !state.HasMember("properties") || !state["properties"].IsObject()) {
					throw std::invalid_argument("EnemyComponent::Deserialize - Invalid state: Missing or invalid 'name'.");
				}

				std::string stateName = state["name"].GetString();

				AddAndInitializeState(stateName, state["properties"]);
			}
		}
		else {
			throw std::invalid_argument("EnemyComponent::Deserialize - Invalid 'states'");
		}
    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing EnemyComponent: " << e.what() << std::endl;
        throw;
    }
}

void EnemyComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{

}

void EnemyComponent::AddAndInitializeState(std::string name, const rapidjson::Value& stateJson)
{
	if (name == "Idle") {
		std::shared_ptr<IdleState> idleState = aiEntity->RegisterState<IdleState>(name);
		if (idleState)
			idleState->Deserialize(stateJson);
	}
	else if (name == "BossIdle") {
		std::shared_ptr<BossIdleState> bossIdleState = aiEntity->RegisterState<BossIdleState>(name);
		if (bossIdleState)
			bossIdleState->Deserialize(stateJson);
	}
	else if (name == "Seek") {
		std::shared_ptr<SeekState> seekState = aiEntity->RegisterState<SeekState>(name);
		if (seekState)
			seekState->Deserialize(stateJson);
	}
	else if (name == "Wander") {
		std::shared_ptr<WanderState> wanderState = aiEntity->RegisterState<WanderState>(name);
		if (wanderState)
			wanderState->Deserialize(stateJson);
	}
	else if (name == "Shoot") {
		std::shared_ptr<ShootState> shootState = aiEntity->RegisterState<ShootState>(name);
		if (shootState)
			shootState->Deserialize(stateJson);
	}
	else if (name == "StrafeShoot") {
		std::shared_ptr<StrafeShootState> shootState = aiEntity->RegisterState<StrafeShootState>(name);
		if (shootState)
			shootState->Deserialize(stateJson);
	}
	else if (name == "WaveShoot") {
		std::shared_ptr<WaveShootState> shootState = aiEntity->RegisterState<WaveShootState>(name);
		if (shootState)
			shootState->Deserialize(stateJson);
	}
	else if (name == "Charge") {
		std::shared_ptr<ChargeState> chargeState = aiEntity->RegisterState<ChargeState>(name);
		if (chargeState)
			chargeState->Deserialize(stateJson);
	}
	else if (name == "Spawn") {
		std::shared_ptr<SpawnState> spawnState = aiEntity->RegisterState<SpawnState>(name);
		if (spawnState)
			spawnState->Deserialize(stateJson);
	}
	else if (name == "PrepareCharge") {
		std::shared_ptr<PrepareChargeState> prepareChargeState = aiEntity->RegisterState<PrepareChargeState>(name);
		if (prepareChargeState)
			prepareChargeState->Deserialize(stateJson);
	}
	else if (name == "PrepareShoot") {
		std::shared_ptr<PrepareShootState> prepareShootState = aiEntity->RegisterState<PrepareShootState>(name);
		if (prepareShootState)
			prepareShootState->Deserialize(stateJson);
	}
	else if (name == "PrepareSpawn") {
		std::shared_ptr<PrepareSpawnState> prepareSpawnState = aiEntity->RegisterState<PrepareSpawnState>(name);
		if (prepareSpawnState)
			prepareSpawnState->Deserialize(stateJson);
	}
	else {
		throw std::invalid_argument("EnemyComponent::Deserialize - Unknown state: " + name);
	}
}
