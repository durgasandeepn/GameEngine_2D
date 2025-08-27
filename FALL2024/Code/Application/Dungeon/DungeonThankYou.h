/****************************************************************
// File Name: DungeonThankYou
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Setup for the thank you scene after defeating the boss
****************************************************************/

#pragma once
#include "Dungeon.h"
class DungeonThankYou : public Dungeon
{
public:
	DungeonThankYou();
	void InitDungeon() override;
	void CleanDungeon() override;
	void Update(float deltaTime) override;
private:
	float countDownToNewScene = 0.1f;
	bool readyToGoToNextScene;
};

