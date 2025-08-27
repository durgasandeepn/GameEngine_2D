/****************************************************************
// File Name: GameManager
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (GameManager core), Jacob Wilburn (Implemented random dungeon selection and cheat codes)
// Description: Manager for all game related pieces. Handles dungeon traversal,
// player management, and game state management.
****************************************************************/
#pragma once
#include "Object/GameObject.h"
#include "Dungeon/DungeonZero.h"
#include "Dungeon/DungeonZeroTwo.h"
#include "Dungeon/DungeonOne.h"
#include "Dungeon/DungeonTwo.h"
#include "Dungeon/DungeonThree.h"
#include "Dungeon/DungeonFour.h"
#include "Dungeon/DungeonFive.h"
#include "Dungeon/DungeonBoss.h"
#include "Dungeon/EmptyDungeonBeforeBoss.h"
#include "Dungeon/DungeonThankYou.h"
#include "Dungeon/Room.h"

class GameManager
{
public:
    static GameManager& Instance() {
        static GameManager instance;
        return instance;
    }

    // Prevent copying
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    void Init();
    void Update(float deltaTime);
    void GoToNextDungeon();

    void AddPlayer(GameObject* player);
    void AddPlayerAfterRevived(GameObject* player);

    void RemovePlayer(GameObject* player);

    void ResetPlayers();

    void SetInitialPlayerInfos(std::vector<PlayerInfo> newPlayerInfos) { initialPlayerInfos = newPlayerInfos; }
    
    bool IsPauseMenuActive() const { return isPauseMenuActive; }
    void ClosePauseMenu();
    void OpenPauseMenu();

    bool GetReachedTheEnd() const { return reachTheEnd; }

	std::vector<GameObject*> GetEnemies() const { return currentDungeon->enemies; }

    Dungeon* currentDungeon;
    Room* currentRoom;
    bool hasDoorOpen = false;
    std::vector<GameObject*> players;
    std::vector<GameObject*> startingPlayers;
    std::vector<GameObject*> enemyList;
    std::vector<PlayerInfo> initialPlayerInfos;
    std::vector<Vector3> initialPlayerPositions;
    std::vector<Dungeon*> dungeons;
    std::vector<Dungeon*> bossRooms;
    size_t currentDungeonIndex = 0;
    void InitializeDungeons();
    void DungeonZeroAdjustment();
    std::vector<GameObject*> GetAlivePlayers() const;
    void CheckIfAllPLayersDie();
    void ResetAfterGameOver(bool hasReachedEnd);

    void GodModeOn();
	void GodModeOff();
    void InstantKillToggle();

	void IsGameOver() {  gameOver = true; }
    void SetBossTrigger(int newCount) { bossTrigger = newCount; }
	void DoorOpen() { hasDoorOpen = true; }

private:
    int currentCount;
    int bossCount;
    uint32_t eventID;
    std::mt19937 randomEngine;

    GameManager() = default;
    bool isPauseMenuActive;
    bool gameOver;
    bool reachTheEnd;
    float gameOverTime = 5.0f;
    float gameOverTimer = 0.0f;
    int bossTrigger = 5;
};

