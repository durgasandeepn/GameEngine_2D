/****************************************************************
// File Name: State
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: A base enemy state that can be extended from
****************************************************************/

#include "precompiled.h"
#include "State.h"
#include "AIEntity.h"
#include "Object/GameObject.h"

void State::Shoot()
{
    Vector3 enemyPos = GetEntity().GetOwner()->GetLocalPosition();

    auto* bullet = GameObject::Instantiate("BossBattle/enemy_bullet.json");
    bullet->SetLocalPosition(Vector3(enemyPos.x, enemyPos.y - 2, enemyPos.z));
    bullet->FindComponent<PhysicsComponent>()->GetBody()->SetVelocity(Vector3(0.0f, -8.0f, 0.0f));

    auto* bullet2 = GameObject::Instantiate("BossBattle/enemy_bullet.json");
    bullet2->SetLocalPosition(Vector3(enemyPos.x, enemyPos.y + 2, enemyPos.z));
    bullet2->FindComponent<PhysicsComponent>()->GetBody()->SetVelocity(Vector3(0.0f, +8.0f, 0.0f));

    auto* bullet3 = GameObject::Instantiate("BossBattle/enemy_bullet.json");
    bullet3->SetLocalPosition(Vector3(enemyPos.x - 2, enemyPos.y, enemyPos.z));
    bullet3->FindComponent<PhysicsComponent>()->GetBody()->SetVelocity(Vector3(-8.0f, 0.0f, 0.0f));

    auto* bullet4 = GameObject::Instantiate("BossBattle/enemy_bullet.json");
    bullet4->SetLocalPosition(Vector3(enemyPos.x + 2, enemyPos.y, enemyPos.z));
    bullet4->FindComponent<PhysicsComponent>()->GetBody()->SetVelocity(Vector3(8.0f, 0.0f, 0.0f));
}

void State::ShootAtTarget(Vector3 target, float speed, float multiplier)
{
    Vector3 currentPos = GetEntity().GetOwner()->GetLocalPosition();
    Vector3 direction = (target - currentPos).Normalized();

    Vector3 desiredVelocity = direction * speed * multiplier;

    auto* bullet4 = GameObject::Instantiate("BossBattle/enemy_bullet.json");
    bullet4->SetLocalPosition(Vector3(currentPos.x, currentPos.y, currentPos.z));
    bullet4->FindComponent<PhysicsComponent>()->GetBody()->SetVelocity(desiredVelocity);
}

void State::WaveShoot(float speed, int waveShootIndex)
{
    Vector3 enemyPos = GetEntity().GetOwner()->GetLocalPosition();

    const int bulletCount = 12;
    const float radius = 2.0f;
    const float spawnOffsetMultiplier = 0.0f;
    const float PI = 3.14159265359f;

    // One bullet per call, increment index each time
    float angle = (2.0f * PI * waveShootIndex) / bulletCount;
    float dx = cos(angle);
    float dy = sin(angle);

    Vector3 velocity(dx * speed, dy * speed, 0.0f);
    Vector3 offset(-dx * radius * spawnOffsetMultiplier, -dy * radius * spawnOffsetMultiplier, 0.0f);
    Vector3 bulletPos = enemyPos + offset;

    auto* bullet = GameObject::Instantiate("BossBattle/enemy_bullet.json");
    bullet->SetLocalPosition(bulletPos);
    bullet->FindComponent<PhysicsComponent>()->GetBody()->SetVelocity(velocity);

    waveShootIndex = (waveShootIndex + 1) % bulletCount; // loop around
}
