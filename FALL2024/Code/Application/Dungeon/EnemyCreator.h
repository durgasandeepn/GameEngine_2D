/****************************************************************
// File Name: EnemyCreator
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (EnemyCreator core), Jacob Wilburn (Random enemy implementation), Alex Humphries (WaveShooter creation)
// Description: Class for creating enemies. Functions include the various
// enemy types as well as the ability to choose random enemies to spawn for rooms
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
class EnemyCreator
{
public:
	EnemyCreator();
	GameObject* CreateGhostShooter(std::vector<GameObject*>& potentialTargets ,Vector3 pos, Vector3 scale);
	GameObject* CreateGhostCharge(std::vector<GameObject*>& potentialTargets, Vector3 pos, Vector3 scale);
	GameObject* CreateWaveShooter(Vector3 pos, Vector3 scale);
	GameObject* CreateBossEnemy(Vector3 pos, Vector3 scale);

	std::vector<GameObject*> SpawnRandomEnemies(float healthLimit, std::vector<GameObject*>& potentialTargets);
};

