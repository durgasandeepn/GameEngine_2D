/****************************************************************
// File Name: BulletComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (BulletComponent core), Jacob Wilburn (collision logic)
// Description: Component for bullet behavior. Contains logic for the damage of bullets
// and collision behavior between bullets and other game objects
****************************************************************/

#include "precompiled.h"
#include "BulletComponent.h"
#include "Object/GameObject.h"
#include "Managers/GlobalSoundManager.h"
#include "Event/Events/CollisionEvent.h"
#include "Components/EnemyComponent.h"

void BulletComponent::Initialize()
{
    if (animationComponent == nullptr)
    {
        animationComponent = owner->FindComponentInChild<AnimationComponent>();
    }
	eventID = EventManager::Instance().AddListener<CollisionEvent>(
		[this](const CollisionEvent& event) {

			if (event.object1->CompareTag("wall") && event.object2->CompareTag("player_bullet"))
			{
				if (event.object2 == owner) {
					GameObject::Destroy(event.object2);
				}
			}
			if (event.object1->CompareTag("wall") && event.object2->CompareTag("enemy_bullet"))
			{
				if (event.object2 == owner) {
					GameObject::Destroy(event.object2);
				}
			}
			if (event.object1->CompareTag("wall") && event.object2->CompareTag("healer_bullet"))
			{
				if (event.object2 == owner) {
					GameObject::Destroy(event.object2);
				}
			}
			if (event.object1->CompareTag("enemy") && event.object2->CompareTag("healer_bullet"))
			{
				if (event.object2 == owner) {
					GameObject::Destroy(event.object2);
				}
			}

			if (event.object1->CompareTag("enemy") && event.object2->CompareTag("player_bullet"))
			{
				if (event.object2 == owner) {
					auto enemyComponent = event.object1->FindComponent<EnemyComponent>();
					if (enemyComponent != nullptr)
					{
						enemyComponent->GetEntity()->SetIsHurt(true);
					}

					auto healthComponent = event.object1->FindComponent<HealthComponent>();
					auto bulletComponent = event.object2->FindComponent<BulletComponent>();
					if (healthComponent != nullptr)
					{
						if (bulletComponent != nullptr)
						{

							healthComponent->TakeDamage(bulletComponent->GetDamage());
							if (healthComponent->GetHealth() <= 0)
							{

								GlobalSoundManager::Instance().Play("55_Encounter_02.mp3");

								auto explosion = GameObject::Instantiate("BossBattle/explosion.json");
								if (!explosion) {
									std::cerr << "Failed to create explosion" << std::endl;
								};
								explosion->SetLocalPosition(event.object1->GetLocalPosition());


								GameObject::Destroy(event.object1);
							}
							else
							{
								GlobalSoundManager::Instance().Play("Bloody punch.mp3");

								//bonus damage
								// comment to avoid bugs
								//if (bulletComponent->GetDamage() >= 0.75f)
								//{
								//	auto explosion2 = GameObject::Instantiate("BossBattle/player_bullet_explosion.json");
								//	if (!explosion2) {
								//		std::cerr << "Failed to create explosion" << std::endl;
								//	};
								//	explosion2->SetLocalPosition(event.object1->GetLocalPosition());
								//}
							}
						}
					}
					GameObject::Destroy(event.object2);
				}
			}

			if (event.object1->CompareTag("player") && event.object2->CompareTag("healer_bullet"))
			{
				if (event.object2 == owner) {
					if (event.object1 != spawner) {

						auto bulletComponent = event.object2->FindComponent<BulletComponent>();

						GlobalSoundManager::Instance().Play("02_Heal_02.mp3");

						auto healthComponent = event.object1->FindComponent<HealthComponent>();
						if (healthComponent != nullptr)
						{
							if (healthComponent->GetHealth() > 0)
							{
								healthComponent->Heal(bulletComponent->GetDamage());
								auto movementComponent = event.object1->FindComponent<MovementComponent2D>();
								if (movementComponent != nullptr)
								{
									movementComponent->SetIsHeal(true);
								}
							}
							else
							{
								auto movementComponent = event.object1->FindComponent<MovementComponent2D>();
								if (movementComponent != nullptr)
								{
									movementComponent->SetReviveProgress(bulletComponent->GetDamage());
								}
							}
						}

						GameObject::Destroy(event.object2);
					}
				}
			}
		}
	);
}

void BulletComponent::Update(float deltaTime)
{
    if (owner->GetShouldDelete()) 
    {
        return;
    }


    if (animationComponent && animationComponent->GetCurrentState() != "Idle") {
        animationComponent->ChangeAnimationState("Idle");
    }

	if (undestroyable) 
	{
		return;
	}

	destroyTime -= deltaTime;

	if (destroyTime <= 0.0f) 
	{
        auto renderComponent = owner->FindComponentInChild<RenderComponent2D>();

        if (renderComponent != nullptr)
        {
        	renderComponent->GetRenderable()->SetVisible(false);
        }

		GameObject::Destroy(owner);
	}
}

void BulletComponent::Shutdown()
{
	EventManager::Instance().RemoveListener<CollisionEvent>(eventID);
}

void BulletComponent::Serialize()
{

}

void BulletComponent::Deserialize(const rapidjson::Value& json)
{
    if (json.HasMember("destroyTime") && json["destroyTime"].IsNumber())
    {
        destroyTime = json["destroyTime"].GetFloat();
    }

    if (json.HasMember("damage") && json["damage"].IsNumber())
    {
        damage = json["damage"].GetFloat();
    }

	if (json.HasMember("undestroyable") && json["undestroyable"].IsBool())
	{
		undestroyable = json["undestroyable"].GetBool();
	}
}

void BulletComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{

}