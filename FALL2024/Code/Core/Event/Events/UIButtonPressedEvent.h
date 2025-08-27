/****************************************************************
// File Name: UIButtonPressedEvent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: An event triggered when a UI button has been pressed.
// The event holds a tag that can be checked for by the subscribing component.
****************************************************************/

#pragma once
#include "../Event.h"
#include "precompiled.h"

class UIButtonPressedEvent : public Event {
public:
	UIButtonPressedEvent(std::string tag)
		: buttonTag(tag){
	}

	std::string buttonTag;
};