/****************************************************************
// File Name: EnemyCreator
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (EnemyCreator core), Jacob Wilburn (Random enemy implementation), Alex Humphries (WaveShooter creation)
// Description: Class for creating enemies. Functions include the various
// enemy types as well as the ability to choose random enemies to spawn for rooms
****************************************************************/

#include "precompiled.h"
#include "EnemyCreator.h"

EnemyCreator::EnemyCreator()
{
}

GameObject* EnemyCreator::CreateGhostShooter(std::vector<GameObject*>& potentialTargets, Vector3 pos, Vector3 scale)
{
	auto ghost1 = GameObject::Instantiate("BossBattle/minion.json");
	if (!ghost1) {
		std::cerr << "Failed to create floatingblock" << std::endl;
	};
	ghost1->SetLocalScale(scale);
	ghost1->SetLocalPosition(pos);

	auto ghost1Component = ghost1->FindComponent<EnemyComponent>();


	ghost1->AddComponent<HealthComponent>();
	auto ghost1HealthComponent = ghost1->FindComponent<HealthComponent>();
	ghost1HealthComponent->SetHealth(15.0f);
	ghost1Component->GetEntity()->SetHealthComponent(ghost1HealthComponent);

	return  ghost1;
}

GameObject* EnemyCreator::CreateGhostCharge(std::vector<GameObject*>& potentialTargets, Vector3 pos, Vector3 scale)
{
	auto ghost1 = GameObject::Instantiate("BossBattle/ghost2.json");
	if (!ghost1) {
		std::cerr << "Failed to create floatingblock" << std::endl;
	};
	ghost1->SetLocalScale(scale);
	ghost1->SetLocalPosition(pos);

	auto ghost1Component = ghost1->FindComponent<EnemyComponent>();

	ghost1->AddComponent<HealthComponent>();
	auto ghost1HealthComponent = ghost1->FindComponent<HealthComponent>();
	ghost1HealthComponent->SetHealth(25.0f);
	ghost1Component->GetEntity()->SetHealthComponent(ghost1HealthComponent);

	return  ghost1;
}

GameObject* EnemyCreator::CreateWaveShooter(Vector3 pos, Vector3 scale)
{
	auto ghost1 = GameObject::Instantiate("BossBattle/waveshooter.json");
	if (!ghost1) {
		std::cerr << "Failed to create floatingblock" << std::endl;
	};
	ghost1->SetLocalScale(scale);
	ghost1->SetLocalPosition(pos);

	auto ghost1Component = ghost1->FindComponent<EnemyComponent>();


	ghost1->AddComponent<HealthComponent>();
	auto ghost1HealthComponent = ghost1->FindComponent<HealthComponent>();
	ghost1HealthComponent->SetHealth(15.0f);
	ghost1Component->GetEntity()->SetHealthComponent(ghost1HealthComponent);

	return  ghost1;
}

GameObject* EnemyCreator::CreateBossEnemy(Vector3 pos, Vector3 scale)
{
	auto boss = GameObject::Instantiate("BossBattle/boss.json");
	if (!boss) {
		std::cerr << "Failed to create floatingblock" << std::endl;
	};
	boss->SetLocalScale(scale);
	boss->SetLocalPosition(pos);
	boss->AddComponent<EnemyComponent>();
	auto bossComponent = boss->FindComponent<EnemyComponent>();

	auto bossHealthUI = GameObject::Instantiate("UI/healthUI.json");
	if (!bossHealthUI) {
		std::cerr << "Failed to create UIComponent" << std::endl;
	};

	boss->AddComponent<HealthComponent>();
	auto bossHealthComponent = boss->FindComponent<HealthComponent>();

	bossHealthComponent->SetHealthComponent(bossHealthUI->FindComponent<UIComponent>());

	bossHealthComponent->SetHealth(100.0f);

	bossComponent->GetEntity()->SetHealthUIComponent(bossHealthUI->FindComponent<UIComponent>());

	return boss;
}

std::vector<GameObject*> EnemyCreator::SpawnRandomEnemies(float healthLimit, std::vector<GameObject*>& potentialTargets) {
	float currentPool = 0.0f;
	std::vector<GameObject*> list;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distr(0, 99);
	std::uniform_int_distribution<> distr2(-15, 15);
	
	while (currentPool < healthLimit) {
		int enemyType = distr(gen);
		Vector3 position(distr2(gen), 5.0f, 0.0f);

		if(enemyType < 60) {

			auto enemy = CreateGhostShooter(potentialTargets, position, Vector3(1.5f, 1.5f, 0.0f));
			list.push_back(enemy);
			currentPool += 15.0f;
		}
		else if (enemyType > 60 && enemyType < 80) {
			auto enemy = CreateWaveShooter(position, Vector3(1.5f, 1.5f, 0.0f));
			list.push_back(enemy);
			currentPool += 15.0f;
		}
		else {
			if (currentPool + 25 > healthLimit) continue;
			auto enemy = CreateGhostCharge(potentialTargets, position, Vector3(2.0f, 2.0f, 0.0f));
			list.push_back(enemy);
			currentPool += 25.0f;
		}
	}
	return list;
}