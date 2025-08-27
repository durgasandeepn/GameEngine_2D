/****************************************************************
// File Name: DungeonTwo
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn (Refactoring layout), Ju-ve Chankasemporn (DungeonTwo core)
// Description: Setup for dungeon layout number 2
****************************************************************/

#pragma once
#include "Dungeon.h"
class DungeonTwo : public Dungeon
{
public:
	DungeonTwo();
	void InitDungeon() override;
	void CleanDungeon() override;
};

