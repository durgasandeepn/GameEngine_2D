/****************************************************************
// File Name: SceneGraph
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Handles the hierarchy of objects in a scene. Namely, the SceneGraph
// holds a reference to a root node, which can have child object nodes, which can in turn have more child nodes.
// SceneGraph handles updating and rendering each object, by calling their internal update and render functions.
****************************************************************/

#pragma once
#include "Renderer/Renderer.h"
#include "Object/Node.h"
#include "Math/Transform.h"
#include "Object/RootNode.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Renderer/Texture.h"
#include "Time/Time.h"
#include <memory>

class SceneGraph
{
private:

	using SharedNode = Node*;
	RootNode* root;
	Renderer* renderer;
public:
	SceneGraph(Renderer* renderer);

	const SharedNode& GetRoot() const { return root; };
	Renderer* GetRenderer() const { return renderer; }

	void AddNode(SharedNode node);

	void RemoveNode(std::string nodeName);

	SharedNode FindNode(std::string nodeName);

	void RemoveNode(SharedNode node);

	SharedNode FindNode(SharedNode node);

	void Update(float deltaTime);

	void Shutdown();

};