/****************************************************************
// File Name: GameplayDemo
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: The main gameplay scene. Internal room changes
// are handled by the GameManager class.
****************************************************************/

#pragma once
#include "SceneManagement/Scene.h"
#include "Object/GameObject.h"
#include "Dungeon/DungeonOne.h"
#include "Dungeon/DungeonTwo.h"
#include "Dungeon/DungeonBoss.h"
#include "Dungeon/Room.h"
#include "Managers/GameManager.h"


class GameplayDemo : public Scene {
public:
	GameplayDemo(const std::string& name);

	void Initialize() override;
	void Update(float deltaTime) override;
protected:
	void OnEnter() override;
	void OnExit() override;
	void OnResume() override;
	void OnPause() override;

};