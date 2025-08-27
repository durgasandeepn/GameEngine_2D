/****************************************************************
// File Name: AudioManager
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Act as a audio file controller
****************************************************************/

#include "precompiled.h"
#include "AudioManager.h"

bool AudioManager::Initialize()
{
    try {
        FMOD_RESULT result = FMOD::System_Create(&audioSystem);
        if (result != FMOD_OK) {
            throw (FMOD_ErrorString(result));
        }

        result = audioSystem->init(512, FMOD_INIT_NORMAL, nullptr);
        if (result != FMOD_OK) {
            audioSystem->release();
            throw (FMOD_ErrorString(result));
        }
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Audio System creation failed: " << e.what() << std::endl;
        return false;
    }
}

void AudioManager::Shutdown()
{
    for (auto& pair : activeChannels) {
        pair.second->stop();
    }
    activeChannels.clear();

    if (audioSystem != nullptr) {
        audioSystem->close();
        audioSystem->release();
        audioSystem = nullptr;
    }
}

FMOD::Sound* AudioManager::CreateSound(const std::string& name)
{
    FMOD::Sound* sound = nullptr;
    std::cout << "create sound" << std::endl;
    FMOD_RESULT result = audioSystem->createSound((audioFolder + name).c_str(), FMOD_LOOP_NORMAL, nullptr, &sound);
    if (result != FMOD_OK) {
        std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
    }
    return sound;
}

int AudioManager::PlaySound(FMOD::Sound* sound, FMOD::Channel*& channel, bool loop)
{
    sound->setLoopCount(loop ? -1 : 0);

    FMOD_RESULT result = audioSystem->playSound(sound, nullptr, false, &channel);

    if (result != FMOD_OK) {
        std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
        return -1;
    }

    int channelId = nextChannelId++;
    activeChannels[channelId] = channel;
    return channelId;
}

void AudioManager::SetLoop(bool loop, FMOD::Sound* sound)
{
    sound->setLoopCount(loop ? -1 : 0);
}

void AudioManager::Update()
{
    if (audioSystem == nullptr) 
    {
        return;
    }

    audioSystem->update();
}

bool AudioManager::StopChannel(int channelId) {
    auto it = activeChannels.find(channelId);
    if (it == activeChannels.end()) return false;

    it->second->stop();
    activeChannels.erase(it);
    return true;
}

void AudioManager::PauseAll() {
    for (auto& pair : activeChannels) {
        bool isPlaying = false;
        if (pair.second->isPlaying(&isPlaying) == FMOD_OK && isPlaying) {
            pair.second->setPaused(true);
        }
    }
    isPaused = true;
}

void AudioManager::ResumeAll() {
    for (auto& pair : activeChannels) {
        bool isPaused = false;
        if (pair.second->getPaused(&isPaused) == FMOD_OK && isPaused) {
            pair.second->setPaused(false);
        }
    }
    isPaused = false;
}