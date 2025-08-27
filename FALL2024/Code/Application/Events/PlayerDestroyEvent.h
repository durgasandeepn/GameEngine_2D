/****************************************************************
// File Name: PlayerDestroyedEvent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Destroy event to clean up pointers
****************************************************************/

#pragma once
#include "Object/Node.h"
#include "Event/Event.h"

class PlayerDestroyEvent : public Event {
public:
	PlayerDestroyEvent(Node* player)
		: playerRef(player) {
	}

	Node* playerRef;
};