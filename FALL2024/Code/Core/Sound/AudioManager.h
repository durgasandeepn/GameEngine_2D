/****************************************************************
// File Name: AudioManager
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Act as a audio file controller
****************************************************************/

#pragma once
#include "fmod.hpp"
#include <fmod_errors.h>
#include <iostream>
#include <unordered_map>
#include <string>

static const std::string audioFolder = "assets/audio/";

class AudioManager
{
public:
	static AudioManager& Instance() {
		static AudioManager instance;
		return instance;
	}

	bool Initialize();
	void Shutdown();

	FMOD::Sound* CreateSound(const std::string& name);
	int PlaySound(FMOD::Sound* sound, FMOD::Channel*& channel, bool loop);
	void SetLoop(bool loop, FMOD::Sound* sound);
	void Update();
	bool StopChannel(int channelId);
	void ResumeAll();
	void PauseAll();

	bool GetIsPaused() const { return isPaused; }
private: 
	AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	FMOD::System* audioSystem{ nullptr };
	std::unordered_map<int, FMOD::Channel*> activeChannels; 
	int nextChannelId{ 0 };
	bool isPaused;
};

