/****************************************************************
// File Name: Engine
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Team - everyone in the team modified this file often
// Description: Core engine system. Singleton that handles the main game loop's update
// and draw calls. Holds references to core game systems.
****************************************************************/

#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "Renderer/Renderer.h"
#include "GameWindow.h"
#include "Physics/PhysicsManager.h"
#include "Renderer/RenderManager.h"
#include "Input/Input.h"
#include "Time/Time.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"
#include "Object/GameObjectFactory.h"
#include "Object/ComponentCreator.h"
#include "ResourceManagement/ResourceManager.h"
#include "SceneManagement/SceneManager.h"
#include "Sound/AudioManager.h"
#include "DebugWindow/ImguiWrapper.h"


class Engine {
public:
	// Struct representing optional engine configurations
	struct EngineConfig {
		int windowWidth = 1920;
		int windowHeight = 1080;
		std::string windowTitle = "Love Wizards";
		float fixedTimeStep = 1.0f / 60.0f;
		bool debugMode = false;
	};

	static Engine& Instance() {
		static Engine instance;
		return instance;
	}

	/**
	* @brief Initializes the engine using the EngineConfig struct. Instantiates all engine systems
	* @param config - Optional EngineConfig struct. If omitted, uses the default above.
	* @return True if initialization was a success, else false.
	*/
	bool Initialize(const EngineConfig& config = EngineConfig());
	/**
	* @brief Main logical loop of the engine. Starts the current frame for Time, then polls for Input,
	* as well as Window events, runs the PhysicsManager, then calls update on the Scene.
	* @return void
	*/
	void Update();
	/**
	* @brief Main rendering (drawing) loop of the engine. Calls render for the given Scene,
	* then swaps the Renderer's buffer, then ends the frame.
	* @return void
	*/
	void Render();
	/**
	* @brief Whether or not the engine is currently running.
	* @return True if the Engine's window has not been asked to close, otherwise false.
	*/
	bool IsRunning() const;
	/**
	* @brief Ends processes from the engine, including shutting down all systems. Called automatically in main.cpp
	* @return void
	*/
	void Shutdown();
	/**
	* @brief Called when turning the engine off, i.e. closing the game. Different from shutdown. Sets IsRunning to false.
	* @return void
	*/
	void Quit();

	void SetDebugMode(bool isDebug) { debugMode = isDebug; }
	bool GetDebugMode() { return debugMode; }

	/* Getters for engine systems */
	GameWindow* GetWindow() const { return window.get(); }
	Renderer* GetRenderer() const { return renderer.get(); }
	Time* GetTime() { return time; }
	AudioManager* GetAudioSystem(){ return audioManager; };

	void SetFullscreen(bool isFullscreen);
	void SetResolution(Resolution res);

private:
	// Used with the physics accumulator
	float fixedTimeStep{0.0f};
	bool debugMode;

	// core systems
	std::unique_ptr<GameWindow> window;
	std::unique_ptr<Renderer> renderer;

	// Singletons only ever instanced once
	Time* time{ nullptr };
	Input* input{ nullptr };
	PhysicsManager* physicsManager{ nullptr };
	RenderManager* renderManager{ nullptr };
	ResourceManager* resourceManager{ nullptr };
	AudioManager* audioManager{ nullptr };
	//
	//Adding Debug Window with Imgui
	ImguiWrapper* debugWindow{ nullptr };

	Engine() = default;
	~Engine() = default;
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	// Initializers
	bool InitializeWindow(const EngineConfig& config);
	bool InitializeRenderer();
	bool InitializeAudioSystem();
	bool InitializeDebugWindowSystem( );//DebugWindow
};



