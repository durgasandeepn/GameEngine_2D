/****************************************************************
// File Name: DungeonTwo
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn (Refactoring layout), Ju-ve Chankasemporn (DungeonTwo core)
// Description: Setup for dungeon layout number 2
****************************************************************/

#include "precompiled.h"
#include "DungeonTwo.h"
#include "EnemyCreator.h"
#include "DungeonObjectCreator.h"

DungeonTwo::DungeonTwo()
{
}

void DungeonTwo::InitDungeon()
{
	Dungeon::InitDungeon();

	EnemyCreator enemyCreator;
	float healthPool = getHealthPool();

	std::vector<GameObject*> enemyList = enemyCreator.SpawnRandomEnemies(healthPool, playerTargets);
	for (int i = 0; i < enemyList.size(); i++) {
		AddEnemy(enemyList[i]);
	}

	DungeonObjectCreator dungeonObjectCreator;

	auto wall1 = dungeonObjectCreator.CreateWall(Vector3(8.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall2 = dungeonObjectCreator.CreateWall(Vector3(6.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall3 = dungeonObjectCreator.CreateWall(Vector3(4.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall4 = dungeonObjectCreator.CreateWall(Vector3(2.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall5 = dungeonObjectCreator.CreateWall(Vector3(0.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall6 = dungeonObjectCreator.CreateWall(Vector3(-2.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall7 = dungeonObjectCreator.CreateWall(Vector3(-4.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall8 = dungeonObjectCreator.CreateWall(Vector3(-6.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	auto wall9 = dungeonObjectCreator.CreateWall(Vector3(-8.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f));
	dungeonObjects.push_back(wall1);
	dungeonObjects.push_back(wall2);
	dungeonObjects.push_back(wall3);
	dungeonObjects.push_back(wall4);
	dungeonObjects.push_back(wall5);
	dungeonObjects.push_back(wall6);
	dungeonObjects.push_back(wall7);
	dungeonObjects.push_back(wall8);
	dungeonObjects.push_back(wall9);
}

void DungeonTwo::CleanDungeon()
{
	Dungeon::CleanDungeon();
}
