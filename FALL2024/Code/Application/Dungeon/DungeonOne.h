/****************************************************************
// File Name: DungeonOne
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn (Refactoring layout), Ju-ve Chankasemporn (DungeonOne core)
// Description: Setup for dungeon layout number 1
****************************************************************/


#pragma once
#include "Dungeon.h"
class DungeonOne : public Dungeon
{
public:
	DungeonOne();
	void InitDungeon() override;
	void CleanDungeon() override;
};

