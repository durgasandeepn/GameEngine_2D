/****************************************************************
// File Name: GameObject
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Team - everyone in the team modified this file often
// Description: Extension of a Node. Handles a list of components, and updates them in
// it's Update method. Also calls Node's Update.
****************************************************************/

#include "precompiled.h"
#include "GameObject.h"
#include "MemoryManagement/MemoryManager.h"
#include "ResourceManagement/ResourceManager.h"
#include "SceneManagement/SceneManager.h"
#include "Event/Events/ObjectCreatedEvent.h"
#include "Event/Events/ObjectDeletedEvent.h"
#include "Time/Time.h"

GameObject::GameObject(const std::string& name) : Node(name), isActive(true), shouldDelete(false)
{
	// Stuff related to system,
	// Memory, etc
	std::cout << "Created object: " << name << std::endl;
}

GameObject::GameObject() : Node(""), isActive(true), shouldDelete(false)
{
}

void GameObject::Initialize()
{
	// Things related to the game. Let game programmer manage stuff
	auto componentsIterator = components.begin();
	while (componentsIterator != components.end()) {
		if (!*componentsIterator) {
			std::cout << "Component null in Game Object: " << this->name << std::endl;
		}
		else {
			(*componentsIterator)->Initialize();
		}
		++componentsIterator;
	}

	// Let any existing systems know this object exists
	EventManager::Instance().BroadcastEvent(ObjectCreatedEvent(this));
}

void GameObject::Update(float deltaTime)
{
	if (!isActive)
		return;

	//not the best way to do this
	for (size_t i = 0; i < components.size(); ++i) {
		components[i]->Update(deltaTime);
	}

	Node::Update(deltaTime);
}

void GameObject::Shutdown()
{
	std::cout << "Shutting down: " << name << std::endl;
	for (auto& child : children)
	{
		GameObject* obj = dynamic_cast<GameObject*>(child);
		if (obj) {
			obj->Shutdown();
		}
	}
	children.clear();
	for (auto& component : components) {
		component->Shutdown();
	}
	components.clear();
	MemoryManager::Instance().DeallocateMemory(this);
}

void GameObject::SetIsActive(bool newIsActive)
{
	isActive = newIsActive;
	for (auto& child : GetChildren())
	{
		dynamic_cast<GameObject*>(child)->SetIsActive(newIsActive);
	}
}


void GameObject::AddTag(std::string tagToAdd)
{
	tags.insert(tagToAdd);
}

bool GameObject::CompareTag(std::string tagToCompare)
{
	return tags.find(tagToCompare) != tags.end();
}

GameObject* GameObject::Instantiate(std::string filepath, GameObject* parent)
{
	auto* newObject = ResourceManager::Instance().LoadGameObjectFromJSON(filepath);
	if (parent) {
		SceneManager::Instance().AddObjectToCurrentScene(newObject, parent);
	}
	else {
		SceneManager::Instance().AddObjectToCurrentScene(newObject);
	}

	return newObject;
}

void GameObject::Destroy(GameObject* obj)
{
	for (auto& child : obj->GetChildren())
	{
		Destroy(dynamic_cast<GameObject*>(child));
	}

	if (obj->FindComponent<PhysicsComponent>()) 
	{
		PhysicsManager::Instance().RemoveBody(obj->FindComponent<PhysicsComponent>()->GetBody().get());
	}

	SceneManager::Instance().RemoveObjectFromCurrentScene(obj);
}
