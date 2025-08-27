/****************************************************************
// File Name: EmptyDungeonBeforeBoss
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Setup for the empty room before boss fight
****************************************************************/

#pragma once
#include "Dungeon.h"
class EmptyDungeonBeforeBoss : public Dungeon
{
public:
	EmptyDungeonBeforeBoss();
	void InitDungeon() override;
	void CleanDungeon() override;
};

