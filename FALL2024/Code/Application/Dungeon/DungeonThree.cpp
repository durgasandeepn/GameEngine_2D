/****************************************************************
// File Name: DungeonThree
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: Setup for dungeon layout number 3
****************************************************************/

#include "precompiled.h"
#include "DungeonThree.h"
#include "EnemyCreator.h"
#include "DungeonObjectCreator.h"

DungeonThree::DungeonThree()
{
}

void DungeonThree::InitDungeon()
{
	Dungeon::InitDungeon();

	EnemyCreator enemyCreator;
	float healthPool = getHealthPool();

	std::vector<GameObject*> enemyList = enemyCreator.SpawnRandomEnemies(healthPool, playerTargets);
	for (int i = 0; i < enemyList.size(); i++) {
		AddEnemy(enemyList[i]);
	}

	DungeonObjectCreator dungeonObjectCreator;

	auto wall1 = dungeonObjectCreator.CreateWall(Vector3(0.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall2 = dungeonObjectCreator.CreateWall(Vector3(9.0f, 3.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall3 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, 3.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall4 = dungeonObjectCreator.CreateWall(Vector3(9.0f, -3.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall5 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, -3.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall1);
	dungeonObjects.push_back(wall2);
	dungeonObjects.push_back(wall3);
	dungeonObjects.push_back(wall4);
	dungeonObjects.push_back(wall5);

}

void DungeonThree::CleanDungeon()
{
	Dungeon::CleanDungeon();
}
