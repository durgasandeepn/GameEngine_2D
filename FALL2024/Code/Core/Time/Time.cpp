/****************************************************************
// File Name: Time
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Also can be considered "FramerateController", handles starting and ending a frame,
// keeping track of delta time, using an accumulator for physics time, getting time since game start, etc.
****************************************************************/

#include "precompiled.h"
#include "Time/Time.h"
#include <thread>
#include <iostream>


Time::Time() : frameCount(0), startFrameTime(0.0), endFrameTime(0.0), DeltaTime(0.0f), accumulator(0.0f), targetFrameTime(0) 
{
	// Framerate is 60 by default but can be changed later
	SetTargetFrameRate(60);
}

void Time::StartFrame()
{
	startFrameTime = glfwGetTime();
}

void Time::EndFrame()
{
	endFrameTime = glfwGetTime();
	// What we want the time difference to be, dependent on intended framerate
	double targetDelta = (targetFrameTime / 1000.0);
	while (endFrameTime - startFrameTime < targetDelta) // add a delay to match framerate
		endFrameTime = glfwGetTime();

	DeltaTime = (float)(endFrameTime - startFrameTime);

	accumulator += DeltaTime;
	++frameCount;
}

bool Time::ShouldUpdatePhysics(float timeStep) const
{
	return accumulator >= timeStep;
}

void Time::ConsumePhysicsTime(float timeStep)
{
	accumulator -= timeStep;
}

void Time::ResetAccumulator()
{
	accumulator = 0.0f;
}

float Time::GetFPS() const
{
	return 1.0f / DeltaTime;
}

void Time::SetTargetFrameRate(unsigned int framerate)
{
	targetFrameTime = (int)(MILLISECOND / framerate);
}

double Time::GetTimeInSeconds()
{
	return glfwGetTime();
}
