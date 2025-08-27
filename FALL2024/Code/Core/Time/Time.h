/****************************************************************
// File Name: Time
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Also can be considered "FramerateController", handles starting and ending a frame,
// keeping track of delta time, using an accumulator for physics time, getting time since game start, etc.
****************************************************************/

#pragma once
#include <glfw3.h>
#define MILLISECOND 1000

class Time
{
public:
	float GetDeltaTime(float scale) {
		return DeltaTime * scale;
	}
	float DeltaTime;

	static Time& Instance() {
		static Time instance;
		return instance;
	}
	
	void StartFrame();
	void EndFrame();

	bool ShouldUpdatePhysics(float timeStep) const;
	void ConsumePhysicsTime(float timeStep);
	void ResetAccumulator();

	float GetFPS() const;
	double GetTimeInSeconds();

	void SetTargetFrameRate(unsigned int framerate);
private:
	Time();
	~Time() = default;
	int frameCount;
	float accumulator;
	double startFrameTime;
	double endFrameTime;
	int targetFrameTime;
	static Time* instance;

};