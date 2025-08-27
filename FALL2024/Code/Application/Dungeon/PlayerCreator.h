/****************************************************************
// File Name: PlayerCreator
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (PlayerCreator core), Jacob Wilburn (Layout changes), Alex Humphries (Refactoring UI)
// Description: Class that handles the creation of players and their UI
****************************************************************/

#pragma once
#include "Managers/GameResourceManager.h"
#include "Object/GameObjectFactory.h"
#include "Engine.h"
#include "Input/InputCodes.h"
#include "Object/Components/AudioSourceComponent.h"
#include "Events/PlayerDestroyEvent.h"
#include "Object/Components/AnimationComponent.h"
#include "Components/HealthComponent.h"
#include "Components/EnemyComponent.h"

class PlayerCreator
{
public:
	PlayerCreator();
	virtual GameObject* CreatePlayer(PlayerInfo playerInfo, int playerIndex);

private:
	void SetPlayerByIndex(int playerIndex, Vector3& playerPos,
		Vector3& backgroundUIPosition,
		Vector3& playerUIPos, Vector3& playerHealthUIPos);
};

