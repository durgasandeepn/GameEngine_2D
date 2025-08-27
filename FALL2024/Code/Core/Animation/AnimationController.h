/****************************************************************
// File Name: AnimationController
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn - base code, Alex Humphries - upgrades and refactors
// Description: Handles changing and playing the different animation players (states).
****************************************************************/

#pragma once
#include <string>
#include "AnimationPlayer.h"

class AnimationController 
{
public:
    AnimationController();
    ~AnimationController();
    void Update(float deltaTime);
    void AddAnimationState(std::string animationState, AnimationPlayer* animationPlayer);
    void ChangeAnimationState(std::string animationState);
    std::string GetCurrentState();
private:
    //string represents the state name of the animation
    std::unordered_map<std::string, AnimationPlayer*> animationPlayers;
    AnimationPlayer* currentAnimationPlayer;
    std::string currentAnimationState;
};