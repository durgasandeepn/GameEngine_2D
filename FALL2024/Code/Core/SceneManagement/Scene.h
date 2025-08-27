/****************************************************************
// File Name: Scene
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: A level. Specifically, holds a SceneGraph that holdes all the objects in the scene.
// Is responsible for calling update and render on the SceneGraph. Can be paused, can also
// process unique logic when the scene is entered, exited, resumed, paused, etc.
****************************************************************/

#pragma once

#include <memory>
#include <string>
#include "Engine.h"
#include "SceneGraph.h"
/**
* @brief GameObjects to be added to the scene between frames
* Leave parent null if the GameObject has no parent
*/
struct PendingObject {
	GameObject* object;
	GameObject* parent;
};

class Scene {
public:
	Scene(const std::string& name) : name(name), isInitialized(false), isPaused(false) {};
	virtual ~Scene() = default;

	// Core scene lifecycle
	virtual void Initialize()=0;
	virtual void Update(float deltaTime);
	virtual void Shutdown();

	const std::string& GetName() const { return name; }
	SceneGraph* GetSceneGraph() const { return sceneGraph.get(); }
	bool IsInitialize() const { return isInitialized; }
	bool IsPaused() const { return isPaused; }

	void AddGameObject(PendingObject objectToAdd);
	void RemoveGameObject(GameObject* gameObject);
	void RemoveGameObject(std::string gameObjectName);

protected:
	void Spawn();
	void Cleanup();

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void OnResume() = 0;
	virtual void OnPause() = 0;

	std::string name;
	std::unique_ptr<SceneGraph> sceneGraph;
	// Parents mapped to children
	std::vector<PendingObject> nodesToAdd;
	std::vector<GameObject*> nodesToDelete;
	bool isInitialized;
	bool isPaused;
};