/****************************************************************
// File Name: ObjectCreatedEvent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: An event that announces the creation of an Object.
// Every object announces their creation. Only used in some niche cases.
****************************************************************/

#pragma once

#include "../Event.h"

class ObjectCreatedEvent : public Event {
public:
	ObjectCreatedEvent(GameObject* gameObject)
		: objectToCreate(gameObject){
	}

	GameObject* objectToCreate;
};