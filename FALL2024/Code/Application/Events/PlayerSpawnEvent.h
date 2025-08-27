/****************************************************************
// File Name: PlayerSpawnEvent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Allows distant systems to find a player
****************************************************************/

#pragma once
#include "Object/Node.h"
#include "Event/Event.h"

class PlayerSpawnEvent : public Event {
public:
	PlayerSpawnEvent(Node* player)
		: playerRef(player) {
	}

	Node* playerRef;
};