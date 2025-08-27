/****************************************************************
// File Name: SeekState
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (SeekState core), Jacob Wilburn (Behavior overhaul)
// Description: An enemy state that handles seeking after players
****************************************************************/

#pragma once
#include <iostream>
#include "State.h"
#include "Math/Vector3.h"

class SeekState : public State {
public:
    SeekState(AIEntity& entity) : State(entity) {};
    void Enter() override;
    void Update(float deltaTime) override;
    void Exit() override;
    void Deserialize(const rapidjson::Value& json) override;
private:
    float seekSpeed = 1.0f;
    float seekTimer = 1.0f;
    float currentSeekTimer = 0.0f;
};