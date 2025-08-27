/****************************************************************
// File Name: HealthComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (HealthComponent Core), Alex Humphries (Compliance with Heart UI)
// Description: Component to handle health of players and enemies
****************************************************************/

#include "precompiled.h"
#include "HealthComponent.h"
#include "Object/GameObject.h"

void HealthComponent::Initialize()
{
}

void HealthComponent::Update(float deltaTime)
{

}

void HealthComponent::Shutdown()
{

}

void HealthComponent::Serialize()
{

}

void HealthComponent::Deserialize(const rapidjson::Value& json)
{

}

void HealthComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{

}

void HealthComponent::SetHealth(float _health)
{
    health = _health;
	maxHealth = health;

    UpdateHealthUI();
}

void HealthComponent::TakeDamage(float damage)
{
	health -= damage;
	if (health <= 0.0f) 
	{
		health = 0.0f;
	}

    UpdateHealthUI();

}

void HealthComponent::Heal(float heal)
{
    health += heal;
    if (health >= maxHealth)
    {
        health = maxHealth;
    }

    UpdateHealthUI();
}

void HealthComponent::ResetHealth()
{
    health = maxHealth;

    UpdateHealthUI();
}

void HealthComponent::UpdateHealthUI()
{
    if (healthUIComponent != nullptr)
    {
        float healthRatio = health / maxHealth;
        Vector3 newScale = healthUIComponent->GetOwner()->GetLocalScale();
        newScale.x = healthRatio * (maxHealth / maxHealth * 4.0f);

        healthUIComponent->GetOwner()->SetLocalScale(newScale);
    }
    else if (createHealthUI){
        // Create our own health bar (using hearts for now)
        // TODO modularity, of course
        int maxHearts = static_cast<int>(maxHealth);
        float wholeHealth = std::floor(health);
        float partial = health - wholeHealth;

        // One-time instantiation
        if (heartUIs.empty())
        {
            for (int i = 0; i < maxHearts; ++i)
            {
                auto heartUI = GameObject::Instantiate("UI/heartHealthUI.json");
                if (heartUI)
                {
                    Vector3 positionOffset(i * 1.5f, 0.0f, 0.0f);
                    heartUI->SetLocalPosition(healthUIPos + positionOffset);
                    heartUIs.push_back(heartUI);
                }
            }
        }

        // Update heart visuals
        for (int i = 0; i < maxHearts; ++i)
        {
            if (!heartUIs[i]) continue;

            float opacity = 0.0f;
            if (i < wholeHealth) {
                opacity = 1.0f;
            }
            else if (i == static_cast<int>(wholeHealth)) {
                opacity = partial;
            }

            auto heartRenderer = heartUIs[i]->FindComponent<UIComponent>();
            if (heartRenderer) {
                heartRenderer->GetRenderable()->opacity = opacity;
            }

            heartUIs[i]->SetIsActive(opacity > 0.0f);
        }
    }
}
