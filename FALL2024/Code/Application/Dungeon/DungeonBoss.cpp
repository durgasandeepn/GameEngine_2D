/****************************************************************
// File Name: DungeonBoss
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Setup for the boss room
****************************************************************/

#include "precompiled.h"
#include "DungeonBoss.h"
#include "Managers/GlobalSoundManager.h"
#include "EnemyCreator.h"

DungeonBoss::DungeonBoss()
{
}

void DungeonBoss::InitDungeon()
{
	Dungeon::InitDungeon();

	//GlobalSoundManager::Instance().SetBGMPitch(1.5f);
	GlobalSoundManager::Instance().PauseBGM();
	GlobalSoundManager::Instance().PlayBGM("OLDBGM05castle2.mp3");

	EnemyCreator enemyCreator;

	auto boss = enemyCreator.CreateBossEnemy(Vector3(0.0f, 5.5f, 0.0f), Vector3(6.0f, 6.0f, 0.0f));
	AddEnemy(boss);
}

void DungeonBoss::CleanDungeon()
{
	Dungeon::CleanDungeon();

	//GlobalSoundManager::Instance().SetBGMPitch(1.0f);
}
