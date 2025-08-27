/****************************************************************
// File Name: CameraCreatedEvent
// © 2025 DigiPen (USA) Corporation
// Authors:  Alex Humphries
// Description: An event that announces the creation of a camera.
// For use with objects that need to get the camera dynamically 
// (since a scene doesn't store it's own camera)
****************************************************************/
#pragma once

#include "../Event.h"
#include "Object/Node.h"
#include "Object/Components/CameraComponent.h"

class CameraCreatedEvent : public Event {
public:
	CameraCreatedEvent(CameraComponent* camera)
		: cam(camera) {
	}

	CameraComponent* cam;
};