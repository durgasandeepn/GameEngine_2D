/****************************************************************
// File Name: DungeonFour
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: Setup for dungeon layout number 4
****************************************************************/

#pragma once
#include "Dungeon.h"
class DungeonFour : public Dungeon
{
public:
	DungeonFour();
	void InitDungeon() override;
	void CleanDungeon() override;
};

