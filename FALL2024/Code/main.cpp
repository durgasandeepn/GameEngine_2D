/****************************************************************
// File Name: main.cpp
// Authors: Mariojulio Alvarez, Alex Humphries
// Description: Entry point for the program. Initializes engine and runs
// the game loop.
****************************************************************/

#include "precompiled.h"
#include "windows.h"
#include "Engine.h"
#include "Managers/GameResourceManager.h"
#include "Scenes/GameplayDemo.h"
#include "Scenes/MainMenu.h"
#include "Scenes/DigiPenSplashScene.h"

#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	// Game main file
	Engine::EngineConfig config;
	// Set up config here
	config.windowWidth = 800;
	//...

	// Initialize all engine systems, including any
	// system-level component to be used in final game
	if (!Engine::Instance().Initialize()) {
		return -1;
	}

	// Set up Time and set framerate
	Engine::Instance().GetTime()->SetTargetFrameRate(60);

	// Initialize game resource manager
	GameResourceManager::Instance().Initialize();

	// Create and push initial scene
	// TODO, change this to be a engine config variable;
	// i.e.: "starting_level": "test_level.json"
	//SceneManager::Instance().PushScene<GameplayDemo>("Gameplay Demo");
	//SceneManager::Instance().PushScene<MainMenu>("Main Menu");
	SceneManager::Instance().PushScene<DigiPenSplashScene>("DigiPenSplashScene");

	// Game loop
	while (Engine::Instance().IsRunning()) {
		Engine::Instance().GetWindow()->PollEvents();

		if (!Engine::Instance().GetWindow()->IsWindowMinimized()) 
		{
			Engine::Instance().Update();
			Engine::Instance().Render();
			if (Engine::Instance().GetAudioSystem()->GetIsPaused()) {
				Engine::Instance().GetAudioSystem()->ResumeAll();
			}
		}
		else 
		{
			if (!Engine::Instance().GetAudioSystem()->GetIsPaused()) {
				Engine::Instance().GetAudioSystem()->PauseAll();
			}
		}
	}

	// Shut down the engine and reset all ptrs
	Engine::Instance().Shutdown();
	return 0;
}