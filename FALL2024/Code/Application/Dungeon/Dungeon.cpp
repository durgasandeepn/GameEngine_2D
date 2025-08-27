/****************************************************************
// File Name: Dungeon
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (Dungeon Core), Jacob Wilburn (Implementation of health pool)
// Description: Base class for our dungeon layouts, keeps a list of enemies and players
// and checks if the dungeon is completed
****************************************************************/

#include "precompiled.h"
#include "Dungeon.h"

float Dungeon::healthPool = 0.0f;

Dungeon::Dungeon() : isDungeonCompleted(false)
{
    setHealthPool(50.0f);
}

void Dungeon::InitDungeon()
{
    isDungeonCompleted = false;
}

void Dungeon::CleanDungeon()
{
    for (auto obj : dungeonObjects)
    {
        if (obj != nullptr)
        {
            GameObject::Destroy(obj);
        }
    }

    dungeonObjects.clear();
}

void Dungeon::Update(float deltaTime)
{
   
    if (!isDungeonCompleted) {
        bool allEnemiesDefeated = true;

        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if ((*it)->GetShouldDelete()) {
                it = enemies.erase(it); 
            }
            else {
                allEnemiesDefeated = false;
                ++it;
            }
        }

        if (allEnemiesDefeated) {
            isDungeonCompleted = true;
        }
    }
}