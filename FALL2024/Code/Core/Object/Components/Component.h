/****************************************************************
// File Name: Component
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Base Component - extend off of this to create unique components
// that can be added to GameObjects.
// A component is effectively a script that runs independent of the logic inside of base
// "GameObject". More about ECS here: https://en.wikipedia.org/wiki/Entity_component_system
****************************************************************/

#pragma once
#include "SceneManagement/SceneGraph.h"
#include "Event/EventManager.h"
#include "Time/Time.h"
#include "Input/Input.h"

class GameObject;
class Component {
public:
	/**
	* @brief Handle memory related things here, like creating new pointers.
	*/
	Component() { active = false; };
	virtual ~Component() = default;

	/**
	* @brief Handle any non-memory related initialization here. Things like event listening or variable assigning
	*/
	virtual void Initialize() = 0;
	/**
	* @brief Called by GameObject. Core logic of the component should be handled here. Should modify owner not self.
	* @param deltaTime - DeltaTime passed in by Engine's Time component
	*/
	virtual void Update(float deltaTime) = 0;
	/**
	* @brief Memory or non memory related shutdowns can happen here. Ptr destruction for example.
	*/
	virtual void Shutdown() = 0;
	/**
	* @brief Not currently implemented. Usually used for saving the Component for later
	*/
	virtual void Serialize() = 0;

	/**
	* @brief Handles Component configuration using external JSON files. Reads in the JSON and uses the correlating data to set up this component.
	* * @param json - A rapidjson JSON data object. Parsing this will give values that can be used in the Component.
	*/
	virtual void Deserialize(const rapidjson::Value& json) = 0;
	
	/**
	* @brief Handles Component configuration using using a map of values. Reads in the map and uses the correlating data to set up this component.
	* * @param properties - The data map mapping a string data name to it's potential value. Need to check for the data name in order to get the correlating value.
	*/
	virtual void Configure(const std::unordered_map<std::string, std::any>& properties) = 0;

	GameObject* GetOwner() const { return owner; }
	void SetOwner(GameObject* gameObject) { owner = gameObject; }

protected:
	bool active;
	GameObject* owner{nullptr};
};