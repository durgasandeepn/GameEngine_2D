/****************************************************************
// File Name: TransitionManager
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: System for managing transitions between game scenes
****************************************************************/

#pragma once
#include "Object/GameObject.h"
#include "Components/TransitionComponent.h"

class SceneManager;

class TransitionManager
{
public:
    static TransitionManager& Instance() {
        static TransitionManager instance;
        return instance;
    }

    void CreateFadeOutUI();

    void CreateFadeInUI();

    template <typename T>
    void QueueSceneChange(const std::string& sceneName, bool fadeIn=true) {
        CreateFadeInUI();

        pendingSceneChange = [sceneName, fadeIn]() {
            SceneManager::Instance().template ChangeScene<T>(sceneName, fadeIn);
            };
    }

    void ExecuteQueuedChange() {
        if (pendingSceneChange) {
            pendingSceneChange();
            pendingSceneChange = nullptr;
        }
    }

    void Update(float deltaTime);

private:
    TransitionManager() = default;

    std::function<void()> pendingSceneChange{ nullptr };
    bool isFadingInActive = false;
    float countDown = 0.0f;
};

