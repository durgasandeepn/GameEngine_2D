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

#include "precompiled.h"
#include "Node.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <sstream>


Node::Node(std::string name): name(name), parent(nullptr), siblingNumber(0){}

void Node::Update(float deltaTime)
{
    UpdateWorldTransform();

    // Update all children
    for (auto& child : children)
    {
        child->Update(deltaTime);
    }
}

void Node::UpdateWorldTransform()
{
    if (parent)
    {
        Matrix4 parentWorld = parent->GetTransformMatrix();
        worldTransform.SetPosition(parentWorld * localTransform.GetPosition());
        worldTransform.SetRotation(parent->worldTransform.GetRotation() + localTransform.GetRotation());
        worldTransform.SetScale(parent->worldTransform.GetScale() * localTransform.GetScale());
    }
    else
    {
        worldTransform = localTransform;
    }
}

void Node::AddChild(SharedNode node)
{
    children.push_back(node);
    node->siblingNumber = children.size() - 1;
    node->parent = this;
}

void Node::Remove()
{
    if (!parent) return;
    parent->children.erase(parent->children.begin() + siblingNumber); // still have a reference shared in foundNode variable
    parent->UpdateSiblingNumbers(siblingNumber);

    for (auto& child : GetChildren())
        parent->AddChild(child);

    children.clear();
    parent = nullptr;
    siblingNumber = 0;
}

void Node::Reparent(SharedNode node)
{
    if (!parent) return;
    // 1. erase the found node from parent's children vector and update sibling numbers
    size_t removedIndex = siblingNumber;
    parent->children.erase(parent->children.begin() + removedIndex); // still have a reference shared in foundNode variable
    parent->UpdateSiblingNumbers(removedIndex);

    // 2. attach this to dstNode
    node->AddChild(this);
}

Node::SharedNode Node::FindChildNodeFast(SharedNode node)
{
    std::stack<Node*> nodeStack;
    nodeStack.push(this);

    while (!nodeStack.empty())
    {
        Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode == node)
        {
            return currentNode;
        }

        for (auto it = currentNode->children.rbegin(); it != currentNode->children.rend(); ++it)
        {
            nodeStack.push(*it);
        }
    }

    return nullptr;
}

Node::SharedNode Node::FindChildNodeFast(std::string nodeName)
{
    std::stack<Node*> nodeStack;
    nodeStack.push(this);

    while (!nodeStack.empty())
    {
        Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode->GetName() == nodeName)
        {
            return currentNode;
        }

        for (auto it = currentNode->children.rbegin(); it != currentNode->children.rend(); ++it)
        {
            nodeStack.push(*it);
        }
    }

    return nullptr;
}

void Node::UpdateSiblingNumbers(size_t startIndex)
{
    for (size_t i = startIndex; i < children.size(); ++i)
    {
        children[i]->siblingNumber = i;
    }
}

void Node::Shutdown()
{
    std::cout << "Shutting down: " << name << std::endl;
    for (auto& child : children)
    {
        child->Shutdown();
    }
}

void Node::SetLocalPosition(const Vector3& position)
{
    localTransform.SetPosition(position);
}

void Node::SetLocalRotation(const Vector3& rotation)
{
    localTransform.SetRotation(rotation);
}

void Node::SetLocalScale(const Vector3& scale)
{
    localTransform.SetScale(scale);
}

void Node::SetWorldPosition(const Vector3& position)
{
    if (parent) {
        Vector3 localPosition = parent->worldTransform.GetInverseLocalMatrix() * position;
        localTransform.SetPosition(localPosition);
    }
    else {
        localTransform.SetPosition(position);
    }
    //UpdateWorldTransform();
}

void Node::SetWorldRotation(const Vector3& rotation)
{
    if (parent) {
        Vector3 localRotation = rotation - parent->worldTransform.GetRotation();
        localTransform.SetRotation(localRotation);
    }
    else {
        localTransform.SetRotation(rotation);
    }
    //UpdateWorldTransform();
}

void Node::SetWorldScale(const Vector3& scale)
{
    if (parent) {
        Vector3 localScale = scale * parent->worldTransform.GetScale().Reciprocal();
        localTransform.SetScale(localScale);
    }
    else {
        localTransform.SetScale(scale);
    }
    UpdateWorldTransform();
}

void Node::PrintNodeRecursive(std::ostream& os, Node* node, int depth)
{
    if (!node) return;

    // Print indentation
    for (int i = 0; i < depth; ++i)
    {
        os << "  ";
    }

    // Print current node
    os << "+-" << node->GetName() << std::endl;

    // Print children
    for (const auto& child : node->GetChildren())
    {
        PrintNodeRecursive(os, child, depth + 1);
    }
}

// Overload the << operator for Node
std::ostream& operator<<(std::ostream& os, Node& node)
{
    Node::PrintNodeRecursive(os, &node, 0);
    return os;
}