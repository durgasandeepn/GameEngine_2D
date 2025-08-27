/****************************************************************
// File Name: UISliderValueChangedEvent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: An event triggered when a UI slider's value is changed
// Holds both a tag to the element, as well as the new value.
****************************************************************/

#pragma once
#include "../Event.h"
#include "precompiled.h"

class UISliderValueChangedEvent: public Event{
public:
	UISliderValueChangedEvent(std::string tag, float newVal)
		: sliderTag(tag), value(newVal) {
	}

	std::string sliderTag;
	float value=0.0f;
};