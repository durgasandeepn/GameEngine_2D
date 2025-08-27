/****************************************************************
// File Name: HealthComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (HealthComponent Core), Alex Humphries (Compliance with Heart UI)
// Description: Component to handle health of players and enemies
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/UIComponent.h"
class HealthComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);
	void SetHealth(float _health);
	float GetMaxHealth() { return maxHealth; }
	float GetHealth() { return health;}
	void TakeDamage(float damage);
	void Heal(float heal);
	void ResetHealth();
	void UpdateHealthUI();

	void SetHealthComponent(std::shared_ptr<UIComponent> _healthUIComponent) { healthUIComponent = _healthUIComponent; }
	void SetCreateHealthUI(bool healthUI) { createHealthUI = healthUI; }
	void SetHealthUIPos(Vector3 pos) { healthUIPos = pos; } // Used for a niche setup
private:
	float maxHealth;
	float health;
	Vector3 healthUIPos;
	bool createHealthUI = false;
	std::vector<GameObject*> heartUIs;
	std::shared_ptr<UIComponent> healthUIComponent;
};

