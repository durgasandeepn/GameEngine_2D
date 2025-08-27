/****************************************************************
// File Name: AIEntity
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (AIEntity core), Alex Humphries (AI refactor and overhaul)
// Description: The "brain" of the Enemy AI system. Handles moving
// between states and actually changing values within the Enemy
****************************************************************/

#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "State.h"
#include "Object/Components/AnimationComponent.h"
#include "Object/Components/PhysicsComponent.h"
#include "Components/HealthComponent.h"
#include "Components/BulletComponent.h"
#include "Components/MovementComponent2D.h"
#include "Object/Components/UIComponent.h"

class EnemyComponent;

class AIEntity {
public:
    AIEntity() = default;
    AIEntity(GameObject* owner);

    void Initialize();
    void ChangeState(std::string stateName);
    template <typename State>
    std::shared_ptr<State> RegisterState(std::string stateName);
    bool DoesStateExist(std::string stateName);
    void Update(float deltaTime);

    void SetHealthVisually();
    void SetOwner(GameObject* newOwner) { owner = newOwner; }
    GameObject* GetOwner()			const { return owner; }

    void ChangeAnimationState(std::string animState);
    void MoveOwner(Vector3 vel);
    void SetTargetPlayer(GameObject* _targetPlayer) { targetPlayer = _targetPlayer; }
    GameObject* GetTargetPlayer() { return targetPlayer; }

    void SetHealthComponent(std::shared_ptr<HealthComponent> _healthComponent) { healthComponent = _healthComponent; }
    void SetHealthUIComponent(std::shared_ptr<UIComponent> _healthUIComponent)
    {
        healthUIComponent = _healthUIComponent;
    }
    void SetIsHurt(bool hurt);
    void CheckAndAssignNewTarget();

    void SetInitialState(std::string newState) { initialState = newState; }

    std::string currentStateName;
private:
    std::shared_ptr<AnimationComponent> animationComponent;
    std::shared_ptr<PhysicsComponent> physicsComponent;
    std::shared_ptr<HealthComponent> healthComponent;
    std::shared_ptr<UIComponent> healthUIComponent;
    std::shared_ptr<RenderComponent2D> renderComponent;
    std::string initialState;
    std::shared_ptr<State> currentState;

    std::unordered_map<std::string, std::shared_ptr<State>> stateMap;

    GameObject* targetPlayer;;
    GameObject* owner;
    
    bool isHurt;
    float hurtCooldownTime;

    void Blink(float deltaTime);
};

template<typename State>
inline std::shared_ptr<State> AIEntity::RegisterState(std::string stateName)
{
    if (!DoesStateExist(stateName)) {
        std::shared_ptr<State> newState = std::make_shared<State>(*this);
        stateMap[stateName] = newState;
        return newState;
    }
    else {
        return nullptr;
    }
}
