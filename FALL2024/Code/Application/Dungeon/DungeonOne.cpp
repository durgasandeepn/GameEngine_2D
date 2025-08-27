/****************************************************************
// File Name: DungeonOne
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn (Refactoring layout), Ju-ve Chankasemporn (DungeonOne core)
// Description: Setup for dungeon layout number 1
****************************************************************/

#include "precompiled.h"
#include "DungeonOne.h"
#include "EnemyCreator.h"
#include "DungeonObjectCreator.h"

DungeonOne::DungeonOne()
{
}

void DungeonOne::InitDungeon()
{
	Dungeon::InitDungeon();

	EnemyCreator enemyCreator;
	float healthPool = getHealthPool();

	std::vector<GameObject*> enemyList = enemyCreator.SpawnRandomEnemies(healthPool, playerTargets);
	for (int i = 0; i < enemyList.size(); i++) {
		AddEnemy(enemyList[i]);
	}

	DungeonObjectCreator dungeonObjectCreator;

	auto wall1 = dungeonObjectCreator.CreateWall(Vector3(-7.5f, 2.0f, 0.0f), Vector3(6.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall1);

	auto wall2 = dungeonObjectCreator.CreateWall(Vector3(7.5f, 2.0f, 0.0f), Vector3(6.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall2);

	auto wall3 = dungeonObjectCreator.CreateWall(Vector3(9.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall3);

	auto wall4 = dungeonObjectCreator.CreateWall(Vector3(-9.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall4);

	auto wall5 = dungeonObjectCreator.CreateWall(Vector3(-9.5f, -2.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall5);

	auto wall6 = dungeonObjectCreator.CreateWall(Vector3(9.5f, -2.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall6);
}

void DungeonOne::CleanDungeon()
{
	Dungeon::CleanDungeon();
}
