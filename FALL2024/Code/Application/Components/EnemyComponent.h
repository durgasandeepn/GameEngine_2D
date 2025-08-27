/****************************************************************
// File Name: EnemyComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries (State System Integration), Ju-ve Chankasemporn (EnemyComponent Core)
// Description: Base component for enemies, initializing the AI entity and its states
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Statemachine/AIEntity.h"

class EnemyComponent : public Component, public std::enable_shared_from_this<EnemyComponent>
{
public:
	EnemyComponent();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

	std::shared_ptr<AIEntity> GetEntity() const { return aiEntity; }
private:
	std::shared_ptr<AIEntity> aiEntity;

	void AddAndInitializeState(std::string name, const rapidjson::Value& stateJson);
};

