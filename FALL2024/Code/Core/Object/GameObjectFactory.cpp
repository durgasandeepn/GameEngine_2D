/****************************************************************
// File Name: GameObjectFactory
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Handles building game objects. This is done with our Builder subclass, that takes in
// an object name, makes the object, then different methods on Builder are used to populate the values of the object.
****************************************************************/

#include "precompiled.h"
#include "GameObjectFactory.h"
#include "ResourceManagement/ResourceManager.h"

GameObjectFactory::Builder& GameObjectFactory::Builder::WithTag(const std::string& tag)
{
	gameObject->AddTag(tag);
	return *this;
}

GameObjectFactory::Builder& GameObjectFactory::Builder::WithComponent(const std::string& typeName, const std::unordered_map<std::string, std::any>& properties)
{
	auto component = ComponentCreator::Instance().CreateAndAddComponent(typeName, gameObject);
	if (component && !properties.empty()) {
		component->Configure(properties);
	}
	return *this;
}

GameObjectFactory::Builder& GameObjectFactory::Builder::WithComponentFromJson(const std::string& typeName, const rapidjson::Value& json)
{
	auto component = ComponentCreator::Instance().CreateAndAddComponent(typeName, gameObject);
	if (component) {
		component->Deserialize(json);
	}
	return *this;
}

GameObjectFactory::Builder& GameObjectFactory::Builder::WithTransform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
{
	gameObject->SetLocalPosition(position);
	gameObject->SetLocalRotation(rotation);
	gameObject->SetLocalScale(scale);

	return *this;
}

GameObjectFactory::Builder& GameObjectFactory::Builder::WithChild(GameObject* childObj)
{
	gameObject->AddChild(dynamic_cast<Node*>(childObj));
	return *this;
}

GameObject* GameObjectFactory::Builder::Build()
{
	gameObject->Initialize();
	return gameObject;
}

GameObject* GameObjectFactory::Builder::BuildAndAdd(SceneGraph& sceneGraph)
{
	auto obj = Build();
	sceneGraph.AddNode(obj);
	return obj;
}

GameObject* GameObjectFactory::CreateFromJSON(const rapidjson::Document& jsonDoc)
{
	// Validate json was parsed correctly
	if (!jsonDoc.IsObject()) {
		return nullptr;
	}

	// Validate properties of a GameObject from JSON
	if (!jsonDoc.HasMember("name") || !jsonDoc["name"].IsString()) { // GameObject's name
		std::cerr << "Error, JSON file is missing name" << std::endl;
		return nullptr;
	}

	// Use functions in builder to compose our object
	Builder builder(jsonDoc["name"].GetString());

	if (jsonDoc.HasMember("tags") && jsonDoc["tags"].IsArray()) { // GameObject's tags
		const auto& tags = jsonDoc["tags"].GetArray();
		for (const auto& tag : tags) {
			if (tag.IsString()) {
				builder.WithTag(tag.GetString());
			}
		}
	}

	if (jsonDoc.HasMember("transform") && jsonDoc["transform"].IsObject()) {
		const auto& transform = jsonDoc["transform"];
		Vector3 position, rotation, scale(1, 1, 1); // Default transform values

		if (transform.HasMember("position") && transform["position"].IsObject()) {
			const auto& pos = transform["position"];
			position = Vector3(pos["x"].GetFloat(), pos["y"].GetFloat(), pos["z"].GetFloat());
		}

		if (transform.HasMember("rotation") && transform["rotation"].IsObject()) {
			const auto& rot = transform["rotation"];
			rotation = Vector3(rot["x"].GetFloat(), rot["y"].GetFloat(), rot["z"].GetFloat());
		}

		if (transform.HasMember("scale") && transform["scale"].IsObject()) {
			const auto& sc = transform["scale"];
			scale = Vector3(sc["x"].GetFloat(), sc["y"].GetFloat(), sc["z"].GetFloat());
		}

		builder.WithTransform(position, rotation, scale);
	}

	if (jsonDoc.HasMember("children") && jsonDoc["children"].IsArray()) {
		const auto& children = jsonDoc["children"].GetArray();
		for (const auto& child : children) {
			GameObject* childObject = ResourceManager::Instance().LoadGameObjectFromJSON(child.GetString());
			builder.WithChild(childObject);
		}
	}

	// Handle all other components, whatever they are
	if (jsonDoc.HasMember("components") && jsonDoc["components"].IsArray()) {
		const auto& components = jsonDoc["components"].GetArray();
		for (const auto& component : components) {
			if (component.HasMember("type") && component["type"].IsString()) {
				std::string type = component["type"].GetString();
				// Component handles property validity
				// pass properties directly
				builder.WithComponentFromJson(type, component["properties"]);
			}
		}
	}
	return builder.Build();
}
