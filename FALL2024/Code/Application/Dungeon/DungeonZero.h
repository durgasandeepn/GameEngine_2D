/****************************************************************
// File Name: DungeonZero
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Setup for the first tutorial room
****************************************************************/

#pragma once
#include "Dungeon.h"
class DungeonZero : public Dungeon
{
public:
	DungeonZero();
	void InitDungeon() override;
	void CleanDungeon() override;
};

