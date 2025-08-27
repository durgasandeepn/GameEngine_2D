/****************************************************************
// File Name: AnimationController
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn - base code, Alex Humphries - upgrades and refactors
// Description: Handles changing and playing the different animation players (states).
****************************************************************/

#include "precompiled.h"
#include "AnimationController.h"

AnimationController::AnimationController() : currentAnimationPlayer(nullptr)
{

}

AnimationController::~AnimationController()
{
    for (auto& pair : animationPlayers)
    {
        delete pair.second;
    }

    animationPlayers.clear();
}

void AnimationController::Update(float deltaTime)
{
    if (currentAnimationPlayer != nullptr)
    {
        currentAnimationPlayer->Update(deltaTime);
    }
}

void AnimationController::AddAnimationState(std::string animationState, AnimationPlayer* animationPlayer)
{
    animationPlayers[animationState] = animationPlayer;

    if (currentAnimationPlayer == nullptr)
    {
        currentAnimationPlayer = animationPlayer;
        currentAnimationState = animationState;
        currentAnimationPlayer->Play();
    }
}

void AnimationController::ChangeAnimationState(std::string animationState)
{
    if (currentAnimationPlayer && currentAnimationPlayer == animationPlayers[animationState])
    {
        return;
    }

    auto it = animationPlayers.find(animationState);

    if (it != animationPlayers.end())
    {
        currentAnimationPlayer = it->second;
        currentAnimationState = it->first;
        currentAnimationPlayer->Reset();
        currentAnimationPlayer->Play();
    }
}

std::string AnimationController::GetCurrentState()
{
    return currentAnimationState;
}
