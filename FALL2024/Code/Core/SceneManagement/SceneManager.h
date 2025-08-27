/****************************************************************
// File Name: SceneManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Uses the Scene Stack model, where the top level scene in a stack is what the player
// sees and interacts with. New scenes can be added to the top of the stack and processed, then, when a player wants
// to go back to the original scene, the top scene is popped off the stack.
****************************************************************/

#pragma once

#include <stack>
#include <memory>
#include "Scene.h"
#include "Event/EventManager.h"
#include "Event/Events/SceneTransitionEvent.h"
#include "Managers/TransitionManager.h"

class SceneManager {
public:
	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	}

	template <typename T>
	void PushScene(const std::string& name, bool fadeIn=true) {
		static_assert(std::is_base_of<Scene, T>::value, "T must inherit from Scene");

		// Pause current scene until game programmer decides what to do with it
		if (!sceneStack.empty()) {
			SceneTransitionEvent::TransitionType transition = SceneTransitionEvent::TransitionType::PAUSE;
			SceneTransitionEvent pauseEvent(transition, sceneStack.top().get());
			EventManager::Instance().BroadcastEvent(pauseEvent);
		}

		// Create a new scene
		auto newScene = std::make_unique<T>(name);

		// Need to push the scene before notifying
		// an event on the scene entrance
		sceneStack.push(std::move(newScene));

		// Notify the entry of the new scene
		SceneTransitionEvent::TransitionType transition = SceneTransitionEvent::TransitionType::ENTER;
		SceneTransitionEvent enterEvent(transition, sceneStack.top().get());
		EventManager::Instance().BroadcastEvent(enterEvent);

		// Finally initializes everything in the scene
		sceneStack.top().get()->Initialize();
		if (fadeIn) {
			TransitionManager::Instance().CreateFadeOutUI();
		}
	}

	// Function to switch to another scene
	template <typename T>
	void ChangeScene(const std::string& anotherScene, bool fadeIn=true) {
		transitioning = true;
		// Notify that the current scene is exiting
		if (!sceneStack.empty()) {
			SceneTransitionEvent::TransitionType transition = SceneTransitionEvent::TransitionType::EXIT;
			SceneTransitionEvent exitEvent(transition, sceneStack.top().get());
			EventManager::Instance().BroadcastEvent(exitEvent);
			sceneStack.top()->Shutdown();
			sceneStack.pop();
		}
		PushScene<T>(anotherScene, fadeIn);
		transitioning = false;
	}

	void PopScene();
	Scene* GetCurrentScene() const;
	Scene* GetPreviousScene() const;
	size_t GetSceneCount() const { return sceneStack.size(); }
	void Update(float deltaTime);
	void Shutdown();

	void AddObjectToCurrentScene(GameObject* objectToAdd, GameObject* parent = nullptr);
	void RemoveObjectFromCurrentScene(GameObject* objectToRemove);

	bool IsTransitioning() const { return transitioning; }

	void SetIsPause(bool pause) { isPause = pause; }
	bool IsPause() const { return isPause; }
private:
	std::stack<std::unique_ptr<Scene>> sceneStack;
	bool transitioning = false;
	bool isPause;
};