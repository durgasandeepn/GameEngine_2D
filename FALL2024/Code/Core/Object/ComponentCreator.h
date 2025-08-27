/****************************************************************
// File Name: ComponentCreator
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez
// Description: A singleton class used to both dynamically register new component types
// (coming from a Gameplay programmer), as well as add components to a GameObject.
// This is sort of a black box for me, here's how I think it works.
// Since we're using Templates, we need a unique function for adding a templated Component to a GameObject
// (gameObject->AddComponent<MovementComponent2D> for example).
// This component holds a map of component name to the function needed to add that component to a GameObject.
// (
// "MovementComponent2D" : [](std::shared_ptr<GameObject> gameObject) -> std::shared_ptr<Component> {
//			return gameObject->AddComponent<MovementComponent2D>();
//		};
//	)
// So you first register the component name and add function to the map, then later on you can add the Component without trouble.
****************************************************************/

#pragma once

#include <memory>
#include <functional>
#include "Components/Component.h"
#include "GameObject.h"

class ComponentCreator {
public:
	static ComponentCreator& Instance() {
		static ComponentCreator instance;
		return instance;
	}

	/**
	* @brief Used to register a Component of type <T> to be able to add it to Components later.
	* @param <T> - The type of Component that can now be added to GameObjects.
	* @param typeName - the string value that will get mapped to the "add" function for reference later.
	*/
	template<typename T>
	void RegisterComponent(const std::string& typeName) {
		creators[typeName] = [](GameObject* gameObject) -> std::shared_ptr<Component> {
			return gameObject->AddComponent<T>(); // Store the function to be used later by the factory
		};
	}

	// Function for factory to create the corresponding component from creators
	/**
	* @brief Actually adding the component of type typeName based on the correlating "add" function stored in the map.
	* @param typeName - the string value that will be used to retrieve the "add" function from the map.
	* @param gameObject - the object to add the Component to
	*/
	std::shared_ptr<Component> CreateAndAddComponent(const std::string& typeName, GameObject* gameObject);
private:
	ComponentCreator() = default;
	// Maps a type name to a function that takes a shared pointer of a gameobject as a parameter and returns a shared pointer of a component
	std::unordered_map<std::string, std::function<std::shared_ptr<Component>(GameObject*)>> creators;
};