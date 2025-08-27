/****************************************************************
// File Name: DungeonThankYou
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Setup for the thank you scene after defeating the boss
****************************************************************/

#include "precompiled.h"
#include "DungeonThankYou.h"

#include "DungeonObjectCreator.h"
#include "Scenes/EndGameScene.h"
#include "Managers/GameManager.h"

DungeonThankYou::DungeonThankYou()
{
}

void DungeonThankYou::InitDungeon()
{
	Dungeon::InitDungeon();

	//GlobalSoundManager::Instance().Play("QuestionOrComment.mp3");

	DungeonObjectCreator dungeonObjectCreator;

	auto thank_you = dungeonObjectCreator.CreateDungeonObject("Tutorial/thank_you.json", Vector3(0.0f, 0.0f, 0.0f));
	dungeonObjects.push_back(thank_you);
}

void DungeonThankYou::CleanDungeon()
{
	Dungeon::CleanDungeon();
}

void DungeonThankYou::Update(float deltaTime)
{
	Dungeon::Update(deltaTime);

	countDownToNewScene -= deltaTime;

	if (!readyToGoToNextScene && countDownToNewScene <= 0)
	{
		countDownToNewScene = 0.0f;
		readyToGoToNextScene = true;
		GameManager::Instance().ResetAfterGameOver(true);
		TransitionManager::Instance().QueueSceneChange<EndGameScene>("EndGameScene");
	}
}