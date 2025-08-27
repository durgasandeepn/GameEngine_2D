/****************************************************************
// File Name: AudioClip
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Data relating to an audio source
****************************************************************/

#pragma once
#include <iostream>
#include <string>
#include <fmod.hpp>
#include "AudioManager.h"

class AudioClip 
{
public:
	AudioClip(std::string name, AudioManager& manager);
	AudioClip(std::string name);
	~AudioClip();
	// Used this for delayed sound generation if the AudioManager isn't available
	// until later
	void Generate(AudioManager& manager);
	std::string GetClipName();
	FMOD::Sound* GetSound();
	bool IsGenerated() const { return isGenerated; }
private:
	bool isGenerated;

	std::string clipName;
	FMOD::Sound* sound;
};