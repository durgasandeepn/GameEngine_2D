/****************************************************************
// File Name: DungeonThree
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: Setup for dungeon layout number 3
****************************************************************/


#pragma once
#include "Dungeon.h"
class DungeonThree : public Dungeon
{
public:
	DungeonThree();
	void InitDungeon() override;
	void CleanDungeon() override;
};

