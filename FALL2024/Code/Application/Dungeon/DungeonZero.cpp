/****************************************************************
// File Name: DungeonZero
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Setup for the first tutorial room
****************************************************************/

#include "precompiled.h"
#include "DungeonZero.h"
#include "DungeonObjectCreator.h"

DungeonZero::DungeonZero()
{
}

void DungeonZero::InitDungeon()
{
	Dungeon::InitDungeon();

	DungeonObjectCreator dungeonObjectCreator;

	auto reviveTut = dungeonObjectCreator.CreateDungeonObject("Tutorial/revive_tutorial.json", Vector3(8.0f, 3.0f, 0.0f)); 
	dungeonObjects.push_back(reviveTut);

	auto moveTut = dungeonObjectCreator.CreateDungeonObject("Tutorial/move_tutorial.json", Vector3(-8.0f, 0.0f, 0.0f));
	dungeonObjects.push_back(moveTut);

	auto rotateTut = dungeonObjectCreator.CreateDungeonObject("Tutorial/aim_tutorial.json", Vector3(8.0f, -3.0f, 0.0f));
	dungeonObjects.push_back(rotateTut);
}

void DungeonZero::CleanDungeon()
{
	Dungeon::CleanDungeon();
}
