/****************************************************************
// File Name: SceneGraph
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Handles the hierarchy of objects in a scene. Namely, the SceneGraph
// holds a reference to a root node, which can have child object nodes, which can in turn have more child nodes.
// SceneGraph handles updating and rendering each object, by calling their internal update and render functions.
****************************************************************/

#include "precompiled.h"
#include "SceneGraph.h"
#include "MemoryManagement/MemoryManager.h"	

SceneGraph::SceneGraph(Renderer* renderer) :renderer(renderer), root(new RootNode())
{
	std::cout << "Scene graph created." << std::endl;
}

void SceneGraph::AddNode(SharedNode node)
{
	if (!node)
	{
		throw std::invalid_argument("Cannot add null node to the scene graph.");
	}
	root->AddChild(node);
}

void SceneGraph::RemoveNode(std::string nodeName)
{
	auto node = FindNode(nodeName);

	if (!node)
	{
		throw std::invalid_argument("Cannot remove null node from scene graph");
	}
	if (node == root)
	{
		throw std::runtime_error("Cannot remove the root node");
	}
	node->Remove();
}

SceneGraph::SharedNode SceneGraph::FindNode(std::string nodeName)
{
	return root->FindChildNodeFast(nodeName);
}

void SceneGraph::RemoveNode(SharedNode nodeToRemove)
{
	auto node = FindNode(nodeToRemove);

	if (!node)
	{
		throw std::invalid_argument("Cannot remove null node from scene graph");
	}
	if (node == root)
	{
		throw std::runtime_error("Cannot remove the root node");
	}
	node->Remove();
	GameObject* gameObject = dynamic_cast<GameObject*>(node);
	gameObject->Shutdown();
}

SceneGraph::SharedNode SceneGraph::FindNode(SharedNode nodeToFind)
{
	return root->FindChildNodeFast(nodeToFind);
}

// Updates all child nodes of the scene
void SceneGraph::Update(float deltaTime)
{
	root->Update(deltaTime);
}

// Clear all object pointers and deallocate everything
// in the scene graph
void SceneGraph::Shutdown()
{
	for (auto& child : root->GetChildren())
	{
		GameObject* obj = dynamic_cast<GameObject*>(child);
		if (obj) {
			obj->Shutdown();
		}
		else {
			child->Shutdown();
		}
	}
}
