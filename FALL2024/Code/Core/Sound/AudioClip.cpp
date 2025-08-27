/****************************************************************
// File Name: AudioClip
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Data relating to an audio source
****************************************************************/

#include "precompiled.h"
#include"AudioClip.h"

AudioClip::AudioClip(std::string name, AudioManager& manager) : isGenerated(true)
{
	clipName = name;
	sound = manager.CreateSound(clipName);
}

AudioClip::AudioClip(std::string name) : isGenerated(false)
{
	clipName = name;
}

AudioClip::~AudioClip()
{
	if (sound) {
		sound->release();
	}
}

void AudioClip::Generate(AudioManager& manager)
{
	if (!sound) {
		sound = manager.CreateSound(clipName);
		isGenerated = true;
	}
}

std::string AudioClip::GetClipName()
{
	return clipName;
}

FMOD::Sound* AudioClip::GetSound()
{
	return sound;
}