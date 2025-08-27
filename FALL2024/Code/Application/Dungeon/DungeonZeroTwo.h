/****************************************************************
// File Name: DungeonZeroTwo
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn (Refactoring enemy spawns), Ju-ve Chankasemporn (DungeonZeroTwo core)
// Description: Setup for the second tutorial room
****************************************************************/
#pragma once
#include "Dungeon.h"
class DungeonZeroTwo :public Dungeon
{
public:
	DungeonZeroTwo();
	void InitDungeon() override;
	void CleanDungeon() override;
};

