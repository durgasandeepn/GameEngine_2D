/****************************************************************
// File Name: DungeonZeroTwo
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn (Refactoring enemy spawns), Ju-ve Chankasemporn (DungeonZeroTwo core)
// Description: Setup for the second tutorial room
****************************************************************/

#include "precompiled.h"
#include "DungeonZeroTwo.h"
#include "EnemyCreator.h"
#include "DungeonObjectCreator.h"

DungeonZeroTwo::DungeonZeroTwo()
{
}

void DungeonZeroTwo::InitDungeon()
{
	Dungeon::InitDungeon();
	
	DungeonObjectCreator dungeonObjectCreator;

	auto attackTut = dungeonObjectCreator.CreateDungeonObject("Tutorial/attack_tutorial.json", Vector3(10.0f, 4.0f, 0.0f));
	dungeonObjects.push_back(attackTut);

	auto reviveTut = dungeonObjectCreator.CreateDungeonObject("Tutorial/revive_tutorial.json", Vector3(-10.0f, 4.0f, 0.0f));
	dungeonObjects.push_back(reviveTut);

	EnemyCreator enemyCreator;

	auto ghost1 = enemyCreator.CreateGhostShooter(playerTargets, Vector3(-2.0f, 5.0f, 0.0f), Vector3(1.5f, 1.5f, 0.0f));
	AddEnemy(ghost1);
	auto ghost2 = enemyCreator.CreateGhostShooter(playerTargets, Vector3(2.0f, 5.0f, 0.0f), Vector3(1.5f, 1.5f, 0.0f));
	AddEnemy(ghost2);
}

void DungeonZeroTwo::CleanDungeon()
{
	Dungeon::CleanDungeon();
}
