/****************************************************************
// File Name: GlobalSoundManager
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: External system for managing sound in the game.
****************************************************************/

#include "precompiled.h"
#include "GlobalSoundManager.h"

void GlobalSoundManager::Init()
{
	bgm_player = GameObject::Instantiate("Sound/bgm_player.json");
	if (!bgm_player) {
		std::cerr << "Failed to create soundOwner" << std::endl;
	};

	bgmSourceComponent = bgm_player->FindComponent<AudioSourceComponent>();
	bgmSourceComponent->SetVolume(bgmVolume);

	environment_player = GameObject::Instantiate("Sound/environment_player.json");
	if (!environment_player) {
		std::cerr << "Failed to create soundOwner" << std::endl;
	};

	environmentSourceComponent = environment_player->FindComponent<AudioSourceComponent>();
	environmentSourceComponent->SetVolume(environmentVolume);

	sfx_player = GameObject::Instantiate("Sound/sfx_player.json");
	if (!sfx_player) {
		std::cerr << "Failed to create soundOwner" << std::endl;
	};

	sfxSourceComponent = sfx_player->FindComponent<AudioSourceComponent>();
	sfxSourceComponent->SetVolume(sfxVolume);
	hasInit = true;
}

void GlobalSoundManager::Play(std::string name)
{
	if (sfxVolume > 0.01f && sfxSourceComponent != nullptr)
	{
		sfxSourceComponent->SetAudioClip(name);
		sfxSourceComponent->Play();
	}
}

void GlobalSoundManager::SetBGMPitch(float newPitch)
{
	if (bgmSourceComponent != nullptr)
	{
		bgmSourceComponent->SetPitch(newPitch);
	}
	
}

void GlobalSoundManager::SetBGMVolume(float newVolume)
{
	if (bgmSourceComponent != nullptr)
	{
		bgmSourceComponent->SetVolume(newVolume);
	}
	bgmVolume = newVolume;
}

void GlobalSoundManager::SetEnvVolume(float newVolume)
{
	if (environmentSourceComponent != nullptr)
	{
		environmentSourceComponent->SetVolume(newVolume);
	}
	environmentVolume = newVolume;
}

void GlobalSoundManager::SetSFXVolume(float newVolume)
{
	if (sfxSourceComponent != nullptr)
	{
		sfxSourceComponent->SetVolume(newVolume);
	}
	sfxVolume = newVolume;
}

void GlobalSoundManager::PlayBGM()
{
	if (bgmSourceComponent) {
		bgmSourceComponent->Play();
	}
}

void GlobalSoundManager::PlayEnv()
{
	if (environmentSourceComponent) {
		environmentSourceComponent->Play();
	}
}

void GlobalSoundManager::PlayBGM(std::string name)
{
	if (bgmSourceComponent != nullptr)
	{
		bgmSourceComponent->SetAudioClip(name);
		bgmSourceComponent->Play();
	}
}

void GlobalSoundManager::PlayEnv(std::string name)
{
	if (environmentSourceComponent != nullptr)
	{
		environmentSourceComponent->SetAudioClip(name);
		environmentSourceComponent->Play();
	}
}

void GlobalSoundManager::PauseBGM()
{
	if (bgmSourceComponent) {
		bgmSourceComponent->Stop();
	}
}

void GlobalSoundManager::PauseEnv()
{
	if (environmentSourceComponent) {
		environmentSourceComponent->Stop();
	}
}


