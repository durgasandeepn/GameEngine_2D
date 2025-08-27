/****************************************************************
// File Name: AIEntity
// � 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (AIEntity core), Alex Humphries (AI refactor and overhaul)
// Description: The "brain" of the Enemy AI system. Handles moving
// between states and actually changing values within the Enemy
****************************************************************/

#include "precompiled.h"
#include "AIEntity.h"
#include "Components/EnemyComponent.h"
#include "Managers/GameManager.h"

AIEntity::AIEntity(GameObject* newOwner) : owner(newOwner), stateMap(), initialState("Idle") {
    
}

void AIEntity::Initialize()
{
    animationComponent = owner->FindComponentInChild<AnimationComponent>();
    if (animationComponent == nullptr)
    {
        std::cerr << "Failed to find AnimationComponent " << std::endl;
    }

    renderComponent = owner->FindComponentInChild<RenderComponent2D>();
    if (renderComponent == nullptr) {
        std::cerr << "Failed to find RenderComponent " << std::endl;
    }

    physicsComponent = owner->FindComponent<PhysicsComponent>();
    if (physicsComponent == nullptr)
    {
        std::cerr << "Failed to find PhysicsComponent " << std::endl;
    }

    healthComponent = owner->FindComponentInChild<HealthComponent>();
    if (healthComponent == nullptr)
    {
        std::cerr << "Failed to find HealthComponent " << std::endl;
    }

    if (DoesStateExist(initialState)) {
        currentState = stateMap[initialState];
    }
    
}

void AIEntity::ChangeState(std::string state)
{
    if (currentState) {
        currentState->Exit();
    }
    currentState = stateMap[state];
    if (currentState) {
        currentState->Enter();
    }
}

bool AIEntity::DoesStateExist(std::string stateName)
{
    return stateMap.find(stateName) != stateMap.end();
}

void AIEntity::Update(float deltaTime)
{
    if (healthUIComponent != nullptr)
    {
        Vector3 currentPos = owner->GetLocalPosition();
        currentPos.y += 2.0f;
        healthUIComponent->GetOwner()->SetLocalPosition(currentPos);
    }

    // If we've taken damage blink to show it
    if (isHurt) Blink(deltaTime);

    SetHealthVisually();

    // If we lose our target or they die, find a new target
    if (targetPlayer == nullptr || 
        targetPlayer->FindComponent<MovementComponent2D>()->isDead) {
        CheckAndAssignNewTarget();
    }

    // Update state
    if (currentState) {
        currentState->Update(deltaTime);
    }
}

void AIEntity::SetHealthVisually()
{
    if (healthComponent && renderComponent)
        renderComponent->GetRenderable()->opacity = healthComponent->GetHealth() / healthComponent->GetMaxHealth();
}

void AIEntity::ChangeAnimationState(std::string animState)
{
    if (animationComponent) {
        animationComponent->ChangeAnimationState(animState);
    }
}

void AIEntity::MoveOwner(Vector3 vel)
{
    if (physicsComponent) {
        auto body = physicsComponent->GetBody();
        if (body) {
            body->SetVelocity(vel);
        }
    }
}

void AIEntity::SetIsHurt(bool hurt)
{
    if (!isHurt) {
        if (renderComponent != nullptr)
        {
            renderComponent->GetRenderable()->special_color = Vector3(1.0f, 0.0f, 0.0f);
        }
        
        isHurt = hurt;
        hurtCooldownTime = 0.0f;
    }
}

void AIEntity::CheckAndAssignNewTarget()
{
    auto players = GameManager::Instance().GetAlivePlayers();

    if (players.empty())
    {
        return;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(players.begin(), players.end(), g);

    for (GameObject* player : players)
    {
        if (player)
        {
            targetPlayer = player;
            break;
        }
    }
}

void AIEntity::Blink(float deltaTime)
{
    hurtCooldownTime += deltaTime;
    if (hurtCooldownTime >= 0.3f) {
        if (renderComponent != nullptr)
        {
            renderComponent->GetRenderable()->special_color = Vector3(0.0f, 0.0f, 0.0f);
        }
        isHurt = false;
        hurtCooldownTime = 0.0f;
    }
}
