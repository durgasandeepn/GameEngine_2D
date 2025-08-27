/****************************************************************
// File Name: Node
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: "Base" unit of the object system.
// Handles a transform (both local and world)
// a name, (optional) children and parent,
// Also handles adding its own children, removing
// its own children, and printing it's child tree
// Processed by a SceneGraph
****************************************************************/


#pragma once
#include <iostream>
#include <vector>
#include "Math/Transform.h"

class Node : public std::enable_shared_from_this<Node>
{
// Note - due to the "using" definitions here, protected needs to come before public.
protected:
	using ChildrenContainer = std::vector<Node*>;
	using SharedNode = Node*;

	Node* parent;
	ChildrenContainer children;
	std::string name;
	size_t siblingNumber;

	Transform localTransform;
	Transform worldTransform;

	static void PrintNodeRecursive(std::ostream& os, Node* node, int depth);
	friend std::ostream& operator<<(std::ostream& os, Node& node);

	void UpdateWorldTransform();
public:
	Node(std::string name);
	virtual ~Node() { std::cout << "Node: " << name << " destroyed\n"; }

	// Execution every frame
	virtual void Update(float deltaTime);

	// Api methods
	void		 AddChild(SharedNode node);
	virtual void Remove();
	virtual void Reparent(SharedNode node);
	SharedNode   FindChildNodeFast(std::string nodeName);
	SharedNode   FindChildNodeFast(SharedNode node);
	void         UpdateSiblingNumbers(size_t startIndex);

	virtual void Shutdown();

	void SetLocalPosition(const Vector3& position);
	void SetLocalRotation(const Vector3& rotation);
	void SetLocalScale(const Vector3& scale);
	Vector3 GetLocalPosition() const { return localTransform.GetPosition(); };
	Vector3 GetLocalRotation() const { return localTransform.GetRotation(); };
	Vector3 GetLocalScale() const { return localTransform.GetScale(); };

	void SetWorldPosition(const Vector3& position);
	void SetWorldRotation(const Vector3& rotation);
	void SetWorldScale(const Vector3& scale);
	Vector3 GetWorldPosition() const { return worldTransform.GetPosition(); };
	Vector3 GetWorldRotation() const { return worldTransform.GetRotation(); };
	Vector3 GetWorldScale() const { return worldTransform.GetScale(); };

	Matrix4 GetTransformMatrix() { return worldTransform.GetLocalMatrix(); }

	// Getters
	Node*					 GetParent()       const { return parent; }
	const ChildrenContainer& GetChildren()     const { return children; }
	std::string				 GetName()	       const { return name;  }

	void SetName(const std::string newName) { name = newName; }
};