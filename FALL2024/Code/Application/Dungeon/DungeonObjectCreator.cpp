/****************************************************************
// File Name: DungeonObjectCreator
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Class to set up various objects for the dungeon layouts
****************************************************************/

#include "precompiled.h"
#include "DungeonObjectCreator.h"

DungeonObjectCreator::DungeonObjectCreator()
{
}

GameObject* DungeonObjectCreator::CreateDungeonObject(std::string file_name, Vector3 pos, Vector3 scale)
{
	auto dungeonObject = GameObject::Instantiate(file_name);
	if (!dungeonObject) {
		std::cerr << "Failed to create dungeonObject" << std::endl;
	};
	dungeonObject->SetLocalPosition(pos);
	dungeonObject->SetLocalScale(scale);

	return dungeonObject;
}

GameObject* DungeonObjectCreator::CreateWall(Vector3 pos, Vector3 scale)
{
	auto wall = GameObject::Instantiate(wallFilePath);
	if (!wall) {
		std::cerr << "Failed to create wall" << std::endl;
	};
	wall->SetLocalPosition(pos);
	wall->SetLocalScale(scale);

	return wall;
}
