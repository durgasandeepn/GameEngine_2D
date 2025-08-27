/****************************************************************
// File Name: GlobalSoundManager
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: External system for managing sound in the game.
****************************************************************/

#pragma once
#include "Object/Components/AudioSourceComponent.h"
#include "Object/GameObjectFactory.h"
class GlobalSoundManager
{
public:
    static GlobalSoundManager& Instance() {
        static GlobalSoundManager instance;
        return instance;
    }

    // Prevent copying
    GlobalSoundManager(const GlobalSoundManager&) = delete;
    GlobalSoundManager& operator=(const GlobalSoundManager&) = delete;

    void Init();
    void Play(std::string name);
    void SetBGMPitch(float newPitch);

    void SetBGMVolume(float newVolume);
    void SetEnvVolume(float newVolume);
    void SetSFXVolume(float newVolume);

    float GetBGMVolume() const { return bgmVolume; }
    float GetEnvVolume() const { return environmentVolume; }
    float GetSFXVolume() const { return sfxVolume; }

    void PlayBGM(); // Play the existing audio attached to the BGM component
    void PlayEnv(); // Play the existing audio attached to the Env component
    void PlayBGM(std::string name); // Play a new BGM song
    void PlayEnv(std::string name); // Play a new ambient soundtrack
    void PauseBGM();
    void PauseEnv();

    bool GetHasInit() const { return hasInit; }
private:
    GlobalSoundManager() = default;
    GameObject* bgm_player;
    GameObject* environment_player;
    GameObject* sfx_player;
    std::shared_ptr<AudioSourceComponent> bgmSourceComponent;
    std::shared_ptr<AudioSourceComponent> environmentSourceComponent;
    std::shared_ptr<AudioSourceComponent> sfxSourceComponent;
    std::unordered_map<std::string, AudioClip*> soundMap;

    float bgmVolume = 0.5f;
    float environmentVolume = 0.1f;
    float sfxVolume = 1.0f;
    bool hasInit = false;
};

