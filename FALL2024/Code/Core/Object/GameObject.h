/****************************************************************
// File Name: GameObject
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Team - everyone in the team modified this file often
// Description: Extension of a Node. Handles a list of components, and updates them in
// it's Update method. Also calls Node's Update.
****************************************************************/

#pragma once
#include <unordered_set>
#include "Node.h"
#include "Components/Component.h"

class GameObject : public Node{
public:
	GameObject();
	GameObject(const std::string& name);
	virtual ~GameObject() = default;
	void Initialize();
	// Updates all the components
	void Update(float deltaTime) override;
	void Shutdown() override;

	bool GetIsActive() const { return isActive; }
	void SetIsActive(bool newIsActive);
	/**
	* @brief Adds a component to the list of components on the GameObject
	* @param class <T> - Adds component of templated type T to the GameObject
	* @return the <T> component that was created
	*/
	template <class T>
	std::shared_ptr<T> AddComponent() {
		auto component = std::make_shared<T>();
		component->SetOwner(dynamic_cast<GameObject*>(this));
		components.push_back(component);
		return component;
	}
	/**
	* @brief Finds the component of type T within the GameObject and returns it
	* @param class <T> - The component to look for
	* @return the <T> component that if it was found, else nullptr
	*/
	template <class T>
	std::shared_ptr<T> FindComponent() {
		std::shared_ptr<T> found = nullptr;
		auto it = std::find_if(components.begin(), components.end(),
			[&found](const std::shared_ptr<Component>& component) {
				found = std::dynamic_pointer_cast<T>(component);
				return found != nullptr;
			});
		return found;
	}
	template <class T>
	std::shared_ptr<T> FindComponentInChild() {
		std::shared_ptr<T> found = FindComponent<T>();
		if (found) return found;

		for (auto& child : children) {
			auto* childGameObject = dynamic_cast<GameObject*>(child);
			if (childGameObject) {
				found = childGameObject->FindComponentInChild<T>();
				if (found) return found;
			}
		}

		return found;
	}

	bool GetShouldDelete() const { return shouldDelete; }
	void SetShouldDelete(bool shouldDelete) { this->shouldDelete = shouldDelete; }

	void AddTag(std::string tagToAdd);
	bool CompareTag(std::string tagToCompare);

	/**
	* @brief Add a GameObject to the current scene,
	* with or without a parent
	* @param filepath - The path of the JSON to be added
	* @param parent - Optional parent
	* @return the created GameObject*
	*/
	static GameObject* Instantiate(std::string filepath, GameObject* parent = nullptr);

	/**
	* @brief Marks the GameObject as "to be deleted"
	* Not to be confused with "Shutdown" or the destructor,
	* This tells a Scene that holds this Object to queue it for deletion between frames
	*/
	static void Destroy(GameObject* obj);


	
private:
	std::vector<std::shared_ptr<Component>> components;
	bool isActive;
	bool shouldDelete;

	std::unordered_set<std::string> tags;
};