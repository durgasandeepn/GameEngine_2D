/****************************************************************
// File Name: Room
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn (Layout changes), Ju-ve Chankasemporn (Room core)
// Description: Sets up the base room layout for the game with the outer
// walls and doors
****************************************************************/

#pragma once
#include "Managers/GameResourceManager.h"
#include "Object/GameObjectFactory.h"
class Room
{
public:
	Room();
	virtual void InitRoom();
	GameObject* door;
	GameObject* newPoint;
	void OpenDoor();
	void CloseDoor();
};

