/****************************************************************
// File Name: DungeonObjectCreator
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Class to set up various objects for the dungeon layouts
****************************************************************/

#pragma once
#include "Managers/GameResourceManager.h"
#include "Object/GameObjectFactory.h"

class DungeonObjectCreator
{
	const std::string& wallFilePath = "BossBattle/wall.json";

public:
	DungeonObjectCreator();
	GameObject* CreateDungeonObject(std::string file_name, Vector3 pos, Vector3 scale = Vector3(10.0f,10.0,1.0f));
	GameObject* CreateWall(Vector3 pos, Vector3 scale);
};

