/****************************************************************
// File Name: DungeonBoss
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Setup for the boss room
****************************************************************/

#pragma once
#include "Dungeon.h"
class DungeonBoss : public Dungeon
{
public:
	DungeonBoss();
	void InitDungeon() override;
	void CleanDungeon() override;
};

