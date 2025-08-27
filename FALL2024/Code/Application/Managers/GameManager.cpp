/****************************************************************
// File Name: GameManager
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (GameManager core), Jacob Wilburn (Implemented random dungeon selection and cheat codes)
// Description: Manager for all game related pieces. Handles dungeon traversal,
// player management, and game state management.
****************************************************************/

#include "precompiled.h"
#include "GameManager.h"
#include "Dungeon/PlayerCreator.h"
#include "GlobalSoundManager.h"
#include "SceneManagement/SceneManager.h"
#include "Time/Time.h"
#include "Scenes/PauseScene.h"
#include "Scenes/CreditsScene.h"
#include "Scenes/MainMenu.h"

void GameManager::Init()
{
	Dungeon::setHealthPool(50.0f);
	gameOver = false;
	reachTheEnd = false;
	hasDoorOpen = false;
	currentDungeon = nullptr;
	currentRoom = nullptr;
	currentCount = 0;
	bossTrigger = 5;

	GlobalSoundManager::Instance().PauseBGM();
	GlobalSoundManager::Instance().PlayBGM("OLDBGM06adventure2.mp3");
	GlobalSoundManager::Instance().PlayEnv();

	currentRoom = new Room();
	currentRoom->InitRoom();

	PlayerCreator playerCreator;
	for (int i = 0; i < initialPlayerInfos.size(); i++) {
		if (initialPlayerInfos[i].isReady) {
			auto player = playerCreator.CreatePlayer(initialPlayerInfos[i], i);
			AddPlayer(player);
		}
	}

	InitializeDungeons();

	initialPlayerPositions.push_back(Vector3(-5.0f, -4.0f, 0.0f)); 
	initialPlayerPositions.push_back(Vector3(-2.0f, -4.0f, 0.0f));
	initialPlayerPositions.push_back(Vector3(2.0f, -4.0f, 0.0f));  
	initialPlayerPositions.push_back(Vector3(5.0f, -4.0f, 0.0f));

	currentDungeon = new DungeonZero();

	currentDungeon->InitDungeon();

	//For dungeon zero only
	DungeonZeroAdjustment();

	std::random_device rd;
	randomEngine.seed(rd());

	eventID = EventManager::Instance().AddListener<CollisionEvent>(
		[this](const CollisionEvent& event) {

			if (event.object1->CompareTag("player") && event.object2->CompareTag("newPoint"))
			{
				GameManager::Instance().GoToNextDungeon();
				return;
			}
			if (event.object1->CompareTag("player") && event.object2->CompareTag("enemy_bullet"))
			{

				GameObject::Destroy(event.object2);

				auto movementComponent = event.object1->FindComponent<MovementComponent2D>();

				if (movementComponent->GetIsInvincible()) {
					return;
				}

				if (!movementComponent->isDead && !movementComponent->isHurt)
				{
					GlobalSoundManager::Instance().Play("URGH.mp3");
				}


				if (movementComponent != nullptr)
				{
					movementComponent->SetIsHurt(true);
				}

				auto healthComponent = event.object1->FindComponent<HealthComponent>();
				if (healthComponent != nullptr)
				{


					healthComponent->TakeDamage(1.0f);

					if (healthComponent->GetHealth() <= 0)
					{
						if (movementComponent)
						{
							movementComponent->SetIsDead(true);
						}
					}
				}

			}

		}
	);
}

void GameManager::Update(float deltaTime)
{
	if (reachTheEnd) 
	{
		return;
	}

	if (!gameOver && (Input::Instance().IsKeyPressed(KeyCode::Escape) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 0) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 1) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 2) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 3))
		)
	{
		if (!isPauseMenuActive)
		{
			OpenPauseMenu();
		}
		else 
		{
			ClosePauseMenu();
		}
	}

	if (currentDungeon != nullptr)
	{
		currentDungeon->Update(deltaTime);

		if (currentDungeon->IsDungeonCompleted())
		{
			if (!hasDoorOpen)
			{
				currentRoom->OpenDoor();
				hasDoorOpen = true;
			}
		}
	}

	CheckIfAllPLayersDie();

	if (gameOver) {
		gameOverTimer -= deltaTime;
		if (gameOverTimer <= 0 ||
			Input::Instance().IsKeyPressed(KeyCode::Escape) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 0) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 1) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 2) ||
			Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_Start, 3)
			) {
			GameManager::Instance().ResetAfterGameOver(false);
			TransitionManager::Instance().QueueSceneChange<MainMenu>("MainMenuScene");
		}
	}
}

void GameManager::GoToNextDungeon()
{
	int dunCount = dungeons.size();
	

	if (hasDoorOpen)
	{
		//currentRoom->CloseDoor();

		if (currentDungeon != nullptr)
		{
			currentDungeon->CleanDungeon();
			currentDungeon = nullptr;
		}

		if (currentCount >= bossTrigger) {
			if (bossCount < bossRooms.size()) {
				currentDungeon = bossRooms[bossCount];
				bossCount++;
			}

		}
		else if (currentCount == 0) {
			currentDungeon = dungeons[1];
			currentCount++;
		}
		else {
			int end = dunCount - 1;
			int start = 2;
			
			std::uniform_int_distribution<> distr(start, end);
			int randomRoom = distr(randomEngine);
			currentDungeon = dungeons[randomRoom];
			currentCount++;
			float currentHealthPool = currentDungeon->getHealthPool();
			Dungeon::setHealthPool(currentHealthPool + 5.0f);
		}

		currentDungeon->InitDungeon();

		for (auto player : players)
		{
			currentDungeon->AddPlayerTarget(player);
		}

		

		currentRoom->CloseDoor();
		hasDoorOpen = false;

		ResetPlayers();
	}
	else if (currentDungeonIndex + 1 >= dungeons.size())
	{
		std::cout << "Game Over!" << std::endl;
		SceneManager::Instance().PushScene<CreditsScene>("CreditsMenu");
	}
}

void GameManager::AddPlayer(GameObject* player)
{
	players.push_back(player);

	startingPlayers.push_back(player);
}

void GameManager::AddPlayerAfterRevived(GameObject* player)
{
	players.push_back(player);
}

void GameManager::RemovePlayer(GameObject* player)
{
	auto it = std::find(players.begin(), players.end(), player);

	if (it != players.end())
	{
		size_t index = std::distance(players.begin(), it);

		players.erase(it);
	}
}

void GameManager::ResetPlayers()
{
	for (size_t i = 0; i < startingPlayers.size(); ++i)
	{
		startingPlayers[i]->SetLocalPosition(initialPlayerPositions[i]);
	}
}

void GameManager::ClosePauseMenu()
{
	SceneManager::Instance().SetIsPause(false);
	isPauseMenuActive = false;
	SceneManager::Instance().PopScene();
}

void GameManager::OpenPauseMenu()
{
	SceneManager::Instance().SetIsPause(true);
	isPauseMenuActive = true;
	SceneManager::Instance().PushScene<PauseScene>("Pause Scene");
}

void GameManager::InitializeDungeons()
{
	dungeons.push_back(new DungeonZero());   
	dungeons.push_back(new DungeonZeroTwo());
	dungeons.push_back(new DungeonOne());
	dungeons.push_back(new DungeonTwo());
	dungeons.push_back(new DungeonThree());
	dungeons.push_back(new DungeonFour());
	dungeons.push_back(new DungeonFive());

	bossRooms.push_back(new EmptyDungeonBeforeBoss());
	bossRooms.push_back(new DungeonBoss());
	bossRooms.push_back(new DungeonThankYou());
}

void GameManager::DungeonZeroAdjustment()
{
	if (players.size() >= 1)
	{
		players[0]->SetLocalPosition(Vector3(0.0f, -2.0f, 0.0f));
	}
	if (players.size() >= 2)
	{
		players[1]->SetLocalPosition(Vector3(0.0f, 3.0f, 0.0f)); 
	}
	if (players.size() >= 3)
	{
		players[2]->SetLocalPosition(Vector3(-2.0f, 3.0f, 0.0f));
	}
	if (players.size() >= 4)
	{
		players[3]->SetLocalPosition(Vector3(2.0f, 3.0f, 0.0f)); 
	}

	for (size_t i = 1; i < players.size(); ++i) 
	{
		auto healthComponent = players[i]->FindComponent<HealthComponent>();
		if (healthComponent != nullptr)
		{
			healthComponent->TakeDamage(1000.0f);

			if (healthComponent->GetHealth() <= 0)
			{
				auto moveComponent = players[i]->FindComponent<MovementComponent2D>();
				if (moveComponent)
				{
					moveComponent->SetIsDead(true);
				}
			}
		}
	}
}

void GameManager::CheckIfAllPLayersDie()
{


	for (GameObject* player : startingPlayers)
	{
		if (player)
		{
			auto movementComponent = player->FindComponent<MovementComponent2D>();

			if (movementComponent && !movementComponent->isDead)
			{
				return;
			}
		}
	}

	if (reachTheEnd)
	{
		return;
	}
	
	if (!gameOver) 
	{
		auto reviveTut = GameObject::Instantiate("Tutorial/game_over.json");
		if (!reviveTut) {
			std::cerr << "Failed to create block" << std::endl;
		};
		reviveTut->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));

		gameOver = true;
		gameOverTimer = gameOverTime;
	}
}

void GameManager::ResetAfterGameOver(bool hasReachedEnd)
{
	reachTheEnd = hasReachedEnd;

	// Remove event listener
	EventManager::Instance().RemoveListener<CollisionEvent>(eventID);

	players.clear();
	startingPlayers.clear();

	// Delete all dungeons
	dungeons.clear();

	// Reset other state
	initialPlayerInfos.clear();
	initialPlayerPositions.clear();
	currentDungeonIndex = 0;
	hasDoorOpen = false;
	gameOver = false;
}

std::vector<GameObject*> GameManager::GetAlivePlayers() const
{
	std::vector<GameObject*> alivePlayers;

	for (GameObject* player : players)
	{
		if (player)
		{
			auto healthComponent = player->FindComponent<HealthComponent>();
			auto movementComponent = player->FindComponent<MovementComponent2D>();

			if (healthComponent && movementComponent &&
				healthComponent->GetHealth() > 0 && !movementComponent->isDead)
			{
				alivePlayers.push_back(player);
			}
		}
	}

	return alivePlayers;
}

void GameManager::GodModeOn() {
	for (auto player : players) {
		auto movementComponent = player->FindComponent<MovementComponent2D>();
		if (movementComponent != nullptr) {
			movementComponent->setGodMode();
			movementComponent->ActivateBarrier();
		}
	}
}

void GameManager::GodModeOff() {
	for (auto player : players) {
		auto movementComponent = player->FindComponent<MovementComponent2D>();
		if (movementComponent != nullptr) {
			movementComponent->setGodMode();
			movementComponent->DeactivateBarrier();
		}
	}
}

void GameManager::InstantKillToggle() {
	for (auto player : players) {
		auto MovementComponent = player->FindComponent<MovementComponent2D>();
		if (MovementComponent != nullptr) {
			MovementComponent->setInstantKill();
		}
	}
}