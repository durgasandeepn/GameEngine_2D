/****************************************************************
// File Name: DungeonFour
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: Setup for dungeon layout number 4
****************************************************************/

#include "precompiled.h"
#include "DungeonFour.h"
#include "EnemyCreator.h"
#include "DungeonObjectCreator.h"

DungeonFour::DungeonFour()
{
}

void DungeonFour::InitDungeon()
{
	Dungeon::InitDungeon();

	EnemyCreator enemyCreator;
	float healthPool = getHealthPool();

	std::vector<GameObject*> enemyList = enemyCreator.SpawnRandomEnemies(healthPool, playerTargets);
	for (int i = 0; i < enemyList.size(); i++) {
		AddEnemy(enemyList[i]);
	}

	DungeonObjectCreator dungeonObjectCreator;

	auto wall1 = dungeonObjectCreator.CreateWall(Vector3(9.0f, 6.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall2 = dungeonObjectCreator.CreateWall(Vector3(9.0f, 7.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall3 = dungeonObjectCreator.CreateWall(Vector3(9.0f, 8.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall4 = dungeonObjectCreator.CreateWall(Vector3(9.0f, 5.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall5 = dungeonObjectCreator.CreateWall(Vector3(9.0f, 4.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall6 = dungeonObjectCreator.CreateWall(Vector3(9.0f, 9.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));

	auto wall7 = dungeonObjectCreator.CreateWall(Vector3(9.0f, -6.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall8 = dungeonObjectCreator.CreateWall(Vector3(9.0f, -7.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall9 = dungeonObjectCreator.CreateWall(Vector3(9.0f, -8.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall10 = dungeonObjectCreator.CreateWall(Vector3(9.0f, -9.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall11 = dungeonObjectCreator.CreateWall(Vector3(9.0f, -5.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall12 = dungeonObjectCreator.CreateWall(Vector3(9.0f, -4.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));

	auto wall13 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, 6.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall14 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, 7.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall15 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, 8.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall16 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, 9.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall17 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, 5.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall18 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, 4.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));

	auto wall19 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, -6.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall20 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, -7.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall21 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, -8.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall22 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, -9.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall23 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, -4.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));
	auto wall24 = dungeonObjectCreator.CreateWall(Vector3(-9.0f, -5.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f));

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
	dungeonObjects.push_back(wall11);
	dungeonObjects.push_back(wall12);
	dungeonObjects.push_back(wall13);
	dungeonObjects.push_back(wall14);
	dungeonObjects.push_back(wall15);
	dungeonObjects.push_back(wall16);
	dungeonObjects.push_back(wall17);
	dungeonObjects.push_back(wall18);
	dungeonObjects.push_back(wall19);
	dungeonObjects.push_back(wall20);
	dungeonObjects.push_back(wall21);
	dungeonObjects.push_back(wall22);
	dungeonObjects.push_back(wall23);
	dungeonObjects.push_back(wall24);
}

void DungeonFour::CleanDungeon()
{
	Dungeon::CleanDungeon();
}
