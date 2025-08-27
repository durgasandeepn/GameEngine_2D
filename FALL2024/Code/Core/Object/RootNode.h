/****************************************************************
// File Name: RootNode
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: The first node of the SceneGraph (always). Cannot be removed or reparented.
****************************************************************/

#pragma once
#include "Node.h"

class RootNode : public Node
{
public:
	RootNode() : Node("Root") {}
	~RootNode() override = default;

	void Remove() override { throw std::runtime_error("Cannot remove root node."); }
	void Reparent(SharedNode node) override { throw std::runtime_error("Cannot reparent root node."); }
	void Update(float deltaTime) override
	{
		worldTransform = localTransform;

		// Call super
		Node::Update(deltaTime);
	}

	void Shutdown() {
		Node::Shutdown();
	}
};