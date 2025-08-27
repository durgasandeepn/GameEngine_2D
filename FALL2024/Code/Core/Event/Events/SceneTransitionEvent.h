/****************************************************************
// File Name: SceneTransitionEvent
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez
// Description: An event that triggers when a scene is changed. Can
// be the following types:
// ENTER - entering a scene
// EXIT - exiting a scene
// PAUSE - scene is paused (no update logic is running)
// RESUME - scene is resumed (update logic is resumed)
****************************************************************/

#pragma once

#include "Event/Event.h"

class Scene;
class SceneTransitionEvent : public Event {
public:
	enum class TransitionType {
		ENTER,
		EXIT,
		PAUSE,
		RESUME
	};

	SceneTransitionEvent(TransitionType type, Scene* scene) : transitionType(type), scene(scene) {}

	// Data we need when a scene transition happens
	TransitionType transitionType;
	Scene* scene;
};