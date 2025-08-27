/****************************************************************
// File Name: DungeonFive
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: Setup for dungeon layout number 5
****************************************************************/

#include "precompiled.h"
#include "DungeonFive.h"
#include "EnemyCreator.h"
#include "DungeonObjectCreator.h"

DungeonFive::DungeonFive()
{
}

void DungeonFive::InitDungeon()
{
	Dungeon::InitDungeon();

	EnemyCreator enemyCreator;
	float healthPool = getHealthPool();

	std::vector<GameObject*> enemyList = enemyCreator.SpawnRandomEnemies(healthPool, playerTargets);
	for(int i = 0; i < enemyList.size(); i++) {
		AddEnemy(enemyList[i]);
	}

	DungeonObjectCreator dungeonObjectCreator;

	auto wall1 = dungeonObjectCreator.CreateWall(Vector3(12.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall2 = dungeonObjectCreator.CreateWall(Vector3(10.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall3 = dungeonObjectCreator.CreateWall(Vector3(8.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall4 = dungeonObjectCreator.CreateWall(Vector3(6.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall5 = dungeonObjectCreator.CreateWall(Vector3(4.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));

	auto wall6 = dungeonObjectCreator.CreateWall(Vector3(-12.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall7 = dungeonObjectCreator.CreateWall(Vector3(-10.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall8 = dungeonObjectCreator.CreateWall(Vector3(-8.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall9 = dungeonObjectCreator.CreateWall(Vector3(-6.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall10 = dungeonObjectCreator.CreateWall(Vector3(-4.5f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall1);
	dungeonObjects.push_back(wall2);
	dungeonObjects.push_back(wall3);
	dungeonObjects.push_back(wall4);
	dungeonObjects.push_back(wall5);
	dungeonObjects.push_back(wall6);
	dungeonObjects.push_back(wall7);
	dungeonObjects.push_back(wall8);
	dungeonObjects.push_back(wall9);
	dungeonObjects.push_back(wall10);
}

void DungeonFive::CleanDungeon()
{
	Dungeon::CleanDungeon();
}
