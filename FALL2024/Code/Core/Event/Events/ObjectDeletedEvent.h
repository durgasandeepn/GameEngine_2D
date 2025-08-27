/****************************************************************
// File Name: ObjectDeletedEvent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: An event that announces the deletion of an Object.
// Every object announces their deletion. Only used in some niche cases.
****************************************************************/

#pragma once

#include "../Event.h"

class ObjectDeletedEvent : public Event {
public:
	ObjectDeletedEvent(GameObject* gameObject)
		: objectToDelete(gameObject) {
	}

	GameObject* objectToDelete;
};