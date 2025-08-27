/****************************************************************
// File Name: DungeonFive
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn
// Description: Setup for dungeon layout number 5
****************************************************************/

#pragma once
#include "Dungeon.h"
class DungeonFive : public Dungeon
{
public:
	DungeonFive();
	void InitDungeon() override;
	void CleanDungeon() override;
};

