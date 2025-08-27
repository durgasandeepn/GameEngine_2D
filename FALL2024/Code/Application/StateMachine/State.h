/****************************************************************
// File Name: State
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A base enemy state that can be extended from
****************************************************************/

#pragma once

class AIEntity;
class Vector3;
class State 
{
public:
    State(AIEntity& entity) : aiEntity{ entity } {};
    virtual ~State() = default;
    virtual void Enter() {}
    virtual void Update(float deltaTime) {}
    virtual void Exit() {}
    virtual void Deserialize(const rapidjson::Value& json) {}

protected:
    AIEntity& GetEntity() { return aiEntity; }

    /* Methods used amongst more than one state*/
    void Shoot();
    void ShootAtTarget(Vector3 target, float speed, float multiplier);
    void WaveShoot(float speed, int waveShootIndex);
private:
    AIEntity& aiEntity;
};
