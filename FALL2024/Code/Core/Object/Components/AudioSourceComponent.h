/****************************************************************
// File Name: AudioSourceComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Sound as a part of the component
****************************************************************/

#pragma once
#include "Component.h"
#include <string>
#include "Math/Vector3.h"
#include <memory>
#include "Sound/AudioClip.h"
#include "Sound/AudioManager.h"
#include "fmod.hpp"
#include <fmod_errors.h>

class AudioSourceComponent : public Component
{
public:
	AudioSourceComponent();
	~AudioSourceComponent() = default;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json) override;
	void Configure(const std::unordered_map<std::string, std::any>& properties) override;

	void SetAudioSystem(AudioManager* audioSystem);
	void SetAudioClip(AudioClip* newAudioClip);
	void SetAudioClip(std::string newAudioName);
	void Play();
	void Stop();
	/**
	* @brief Set voloume.
	* @param  0.0 : min.
	*		  1.0 : max.
	*/
	void SetVolume(float newVolume);
	void SetPitch(float newPitch);
	/**
	* @brief  Set sound loop. 
	* @param  -1 : will cause it to loop indefinitely until stopped.
	*		   0 : makes the sound play once.
	*/
	void SetLoop(bool shouldLoop);


private:
	AudioManager* audioManager{nullptr};
	// sound controller: eg. volume adjust
	FMOD::Channel* channel{ nullptr };
	AudioClip* audioClip{ nullptr };
	float volume;
	float pitch;
	bool loop;
};