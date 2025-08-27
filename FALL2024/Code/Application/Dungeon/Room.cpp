/****************************************************************
// File Name: Room
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn (Layout changes), Ju-ve Chankasemporn (Room core)
// Description: Sets up the base room layout for the game with the outer
// walls and doors
****************************************************************/

#include "precompiled.h"
#include "Room.h"
#include "DungeonObjectCreator.h"

Room::Room()
{
}

void Room::InitRoom()
{
	DungeonObjectCreator dungeonObjectCreator;

	//upper wall
	dungeonObjectCreator.CreateWall(Vector3(-15.0f, 12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(-10.0f, 12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(-5.0f, 12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(15.0f, 12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(10.0f, 12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(5.0f, 12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	//lower wall
	dungeonObjectCreator.CreateWall(Vector3(-15.0f, -12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(-10.0f, -12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(-5.0f, -12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(15.0f, -12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(10.0f, -12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(5.0f, -12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(0.0f, -12.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	//leftwall

	dungeonObjectCreator.CreateWall(Vector3(-20.0f, 10.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(-20.0f, 5.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(-20.0f, 0.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(-20.0f, -5.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(-20.0f, -10.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	//rightwall
	dungeonObjectCreator.CreateWall(Vector3(20.0f, 10.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(20.0f, 5.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(20.0f, 0.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(20.0f, -5.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	dungeonObjectCreator.CreateWall(Vector3(20.0f, -10.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));

	door = GameObject::Instantiate("BossBattle/door.json");
	if (!door) {
		std::cerr << "**********Failed to create door********" << std::endl;
	}
	else 
	{
		std::cerr << "*******************success eatedoor*********" << std::endl;
	};
	door->SetLocalPosition(Vector3(0.0f, 12.0f, 0.0f));

}

void Room::OpenDoor()
{
	GameObject::Destroy(door);
	newPoint = GameObject::Instantiate("BossBattle/newPoint.json");
	if (!newPoint) {
		std::cerr << "Failed to create block" << std::endl;
	};
	newPoint->SetLocalPosition(Vector3(0.0f, 12.0f, 0.0f));
	newPoint->Update(1.0f);
}

void Room::CloseDoor()
{
	GameObject::Destroy(newPoint);
	door = GameObject::Instantiate("BossBattle/door.json");
	if (!door) {
		std::cerr << "Failed to create block" << std::endl;
	};
	door->SetLocalPosition(Vector3(0.0f, 12.0f, 0.0f));
}
