/****************************************************************
// File Name: Scene
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: A level. Specifically, holds a SceneGraph that holdes all the objects in the scene.
// Is responsible for calling update and render on the SceneGraph. Can be paused, can also
// process unique logic when the scene is entered, exited, resumed, paused, etc.
****************************************************************/

#include "precompiled.h"
#include "Scene.h"

void Scene::Update(float deltaTime)
{
	Spawn();
	Cleanup();
	sceneGraph->Update(deltaTime);

}

void Scene::Shutdown()
{
	// Unregister collision event listeners for this scene
	//EventManager::Instance().FlushEvents();

	// Deregister any physics bodies
	//PhysicsManager::Instance().ClearBodies();

	// Deregister any renderables
	//RenderManager::Instance().ClearRenderables();

	// Let scenegraph shutdown and deallocate actual objects
	sceneGraph->Shutdown();

	// Destroy the scene graph
	sceneGraph.reset();
}

void Scene::AddGameObject(PendingObject objectToAdd)
{
	nodesToAdd.push_back(objectToAdd);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	if (!gameObject->GetShouldDelete()) {
		gameObject->SetShouldDelete(true);
		nodesToDelete.push_back(gameObject);
	}
}
	

void Scene::RemoveGameObject(std::string gameObjectName)
{
	GameObject* nodeToRemove = static_cast<GameObject*>(sceneGraph->FindNode(gameObjectName));
	if (nodeToRemove) {
		nodesToDelete.push_back(nodeToRemove);
	}
}

void Scene::Spawn()
{
	// Add anything queued up to be added
	for (const auto& entry : nodesToAdd) {
		if (entry.object) {
			if (entry.parent) {
				entry.parent->AddChild(entry.object);
			}
			else {
				sceneGraph->AddNode(entry.object);
			}
		}
	}
	nodesToAdd.clear(); // Clear after processing
}

void Scene::Cleanup()
{
	if (!sceneGraph) {  
		return; 
	}

	// Delete anything queued up to be deleted
	for (auto& obj : nodesToDelete) {
		if (obj && sceneGraph->FindNode(obj)) {
			sceneGraph->RemoveNode(obj);
		}
	}
	nodesToDelete.clear();
}
