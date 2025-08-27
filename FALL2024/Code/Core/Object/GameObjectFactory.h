/****************************************************************
// File Name: GameObjectFactory
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Handles building game objects. This is done with our Builder subclass, that takes in
// an object name, makes the object, then different methods on Builder are used to populate the values of the object.
****************************************************************/

#pragma once
#include <any>
#include "GameObject.h"
#include "ComponentCreator.h"
#include "MemoryManagement/MemoryManager.h"

#include "document.h"

class GameObjectFactory {
public:
	static GameObjectFactory& Instance() {
		static GameObjectFactory instance;
		return instance;
	}

	// A builder class that allows for function chaining for object creation
	class Builder {
	public:
		Builder(const std::string& name) : gameObject(nullptr) {
			gameObject = MemoryManager::Instance().AllocateMemory();
			gameObject->SetName(name);
		}

		Builder& WithTag(const std::string& tag);

		// Support for system-level component creation in compilation time
		template <typename T>
		Builder& WithComponent(const std::unordered_map<std::string, std::any>& properties = {}) {
			auto component = gameObject->AddComponent<T>();
			if (!properties.empty()) {
				component->Configure(properties);
			}
			return *this;
		}

		// Support for unknown components (made by game programmer) creation in run time
		Builder& WithComponent(const std::string& typeName, const std::unordered_map<std::string, std::any>& properties = {});

		Builder& WithComponentFromJson(const std::string& typeName, const rapidjson::Value& json);

		// Transform is default, this allows an initial transform to be set
		Builder& WithTransform(const Vector3& position, const Vector3& rotation, const Vector3& scale);

		// Builds the gameObject with the given child object
		Builder& WithChild(GameObject* childObj);

		GameObject* Build();
		GameObject* BuildAndAdd(SceneGraph& sceneGraph);
	
	private:
		GameObject* gameObject;

	};
	// End of builder

	// Utilize the builder subclass for GameObjectFactory's object creation
	static Builder CreateGameObject(const std::string& name) {
		return Builder(name);
	}

	GameObject* CreateFromJSON(const rapidjson::Document& jsonDoc);
private:
	static GameObjectFactory* instance;
	GameObjectFactory() = default;
	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&) = delete;
};