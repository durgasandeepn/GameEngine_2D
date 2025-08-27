/****************************************************************
// File Name: CollisionEvent
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez
// Description: An event for collisions.
// Takes in two Nodes and passes them off to the listener
****************************************************************/

#pragma once
#include "../Event.h"

class GameObject;
class CollisionEvent : public Event {
public:
	CollisionEvent(GameObject* obj1, GameObject* obj2)
		: object1(obj1), object2(obj2) {}

	GameObject* object1;
	GameObject* object2; 
};