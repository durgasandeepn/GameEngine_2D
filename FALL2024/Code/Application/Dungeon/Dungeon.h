/****************************************************************
// File Name: Dungeon
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (Dungeon Core), Jacob Wilburn (Implementation of health pool)
// Description: Base class for our dungeon layouts, keeps a list of enemies and players
// and checks if the dungeon is completed
****************************************************************/

#pragma once

#include "Managers/GameResourceManager.h"
#include "Object/GameObjectFactory.h"
#include "Engine.h"
#include "Input/InputCodes.h"
#include "Object/Components/AudioSourceComponent.h"
#include "Events/PlayerDestroyEvent.h"
#include "Object/Components/AnimationComponent.h"
#include "Components/HealthComponent.h"
#include "Components/EnemyComponent.h"
#include "Events/PlayerDestroyEvent.h"
#include "Room.h"
class Dungeon
{
public:
	Dungeon();
	~Dungeon() = default;
	virtual void InitDungeon();
	virtual void CleanDungeon();
	virtual void Update(float deltaTime);
	std::vector<GameObject*> playerTargets;
	void AddPlayerTarget(GameObject* player) { playerTargets.push_back(player); }
	std::vector<GameObject*> enemies;
	void AddEnemy(GameObject* enemy) { enemies.push_back(enemy); }
	void SetIsDungeonCompleted(bool _isDungeonCompleted) { isDungeonCompleted = _isDungeonCompleted; }
	bool IsDungeonCompleted() const { return isDungeonCompleted; }
	static void setHealthPool(float _healthPool) { healthPool = _healthPool; }
	float getHealthPool() { return healthPool; }
	bool isDungeonCompleted;

	std::vector<GameObject*> dungeonObjects;
private:
	static float healthPool;
};

