/****************************************************************
// File Name: BulletComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (BulletComponent core), Jacob Wilburn (collision logic)
// Description: Component for bullet behavior. Contains logic for the damage of bullets
// and collision behavior between bullets and other game objects
****************************************************************/
#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/AnimationComponent.h"
#include "Object/Components/RenderComponent2D.h"
class BulletComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);
	float GetDamage() { return damage; }
	void SetPlayerBulletDamage(float multiplier) { damage = multiplier * damage; }
	GameObject* GetSpawner() { return spawner; }
	void SetSpawner(GameObject* _spawner) { spawner = _spawner; }
private:
	uint32_t eventID;
	float destroyTime;
	float damage;
	bool undestroyable;
	GameObject* spawner;
	std::shared_ptr<AnimationComponent> animationComponent;
};

