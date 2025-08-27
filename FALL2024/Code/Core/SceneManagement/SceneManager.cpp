/****************************************************************
// File Name: SceneManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Uses the Scene Stack model, where the top level scene in a stack is what the player
// sees and interacts with. New scenes can be added to the top of the stack and processed, then, when a player wants
// to go back to the original scene, the top scene is popped off the stack.
****************************************************************/

#include "precompiled.h"
#include "SceneManager.h"

void SceneManager::PopScene()
{
	// Exit the current scene first, and notify
	if (sceneStack.empty()) return;
	SceneTransitionEvent::TransitionType exitTransition = SceneTransitionEvent::TransitionType::EXIT;
	SceneTransitionEvent exitEvent(exitTransition, sceneStack.top().get());
	EventManager::Instance().BroadcastEvent(exitEvent);
	sceneStack.top()->Shutdown();
	sceneStack.pop();
	
	// Check if stack is empty again due to previous pop,
	// Notify that the new scene needs to be resumed
	if (sceneStack.empty()) return;
	SceneTransitionEvent::TransitionType resumeTransition = SceneTransitionEvent::TransitionType::RESUME;
	SceneTransitionEvent resumeEvent(resumeTransition, sceneStack.top().get());
	EventManager::Instance().BroadcastEvent(resumeEvent);
}

Scene* SceneManager::GetCurrentScene() const
{
	return sceneStack.empty() ? nullptr : sceneStack.top().get();
}

Scene* SceneManager::GetPreviousScene() const
{
	if (sceneStack.size() < 2) return nullptr;
	auto it = sceneStack._Get_container().rbegin();
	++it;
	return it->get();
}

void SceneManager::Update(float deltaTime)
{
	if (!sceneStack.empty()) {
		sceneStack.top()->Update(deltaTime);
		TransitionManager::Instance().Update(deltaTime);
	}
}

void SceneManager::Shutdown()
{
	while (!sceneStack.empty()) {
		SceneTransitionEvent::TransitionType transition = SceneTransitionEvent::TransitionType::EXIT;
		SceneTransitionEvent exitEvent(transition, sceneStack.top().get());
		EventManager::Instance().BroadcastEvent(exitEvent);
		sceneStack.top()->Shutdown();
		sceneStack.pop();
	}
}

void SceneManager::AddObjectToCurrentScene(GameObject* objectToAdd, GameObject* parent)
{
	if (!sceneStack.empty()) {
		sceneStack.top()->AddGameObject({ objectToAdd, parent });
	}
}

void SceneManager::RemoveObjectFromCurrentScene(GameObject* objectToRemove)
{
	if (!sceneStack.empty()) {
		sceneStack.top()->RemoveGameObject(objectToRemove);
	}
}
