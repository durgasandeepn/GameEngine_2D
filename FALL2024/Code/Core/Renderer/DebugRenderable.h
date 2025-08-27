/****************************************************************
// File Name: DebugRenderable
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Renderable object specific to Debugging
****************************************************************/
#pragma once
#include "Math/Vector3.h"

class GameObject;
class Renderer;
class CameraComponent;
class PhysicsComponent;
class OBB;
class AABB;
class Circle;
class Mesh;
class Material;

class DebugRenderable {

public:
	DebugRenderable() = default;
	DebugRenderable(GameObject* owner);

	void Render();

	void SetRender(Renderer* render) { renderer = render; }
	void SetCamera(CameraComponent* cam) { camera = cam; }
	void SetOwner(GameObject* newOwner) { owner = newOwner; }

	void InitializeDebugDraw();
	void DrawDebugLines();
private:
	Renderer* renderer{ nullptr };
	CameraComponent* camera{ nullptr };
	std::shared_ptr<Mesh> debugMesh;
	std::shared_ptr<Material> debugMaterial;
	std::shared_ptr<PhysicsComponent> physicsComponent;
	GameObject* owner{ nullptr }; // Who owns the body

	void DrawOBB(const OBB* obb) const;
	void DrawAABB(const AABB* aabb) const;
	void DrawCircle(const Circle* circle) const;
	void DrawVelocity(const Vector3 velocity) const;
};