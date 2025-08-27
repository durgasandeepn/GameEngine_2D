/****************************************************************
// File Name: Renderable
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Renderable object specific for all non-debug objects.
// Works hand-in-hand with the RenderManager to render each object in the game
****************************************************************/

#pragma once
#include "Math/Vector3.h"

class GameObject;
class Renderer;
class CameraComponent;
class Mesh;
class Material;

class Renderable{

public:
	Renderable() = default;
	Renderable(GameObject* owner);

	void Render();

	void SetRender(Renderer* render) { renderer = render; }
	void SetCamera(CameraComponent* cam) { camera = cam; }
	void SetVisible(bool canSee) { isVisible = canSee; }
	void SetMesh(std::shared_ptr<Mesh> newMesh) { mesh = newMesh; }
	void SetMaterial(std::shared_ptr<Material> newMaterial) { material = newMaterial; }
	void SetOwner(GameObject* newOwner) { owner = newOwner; }
	GameObject* GetOwner() const { return owner; }

	std::shared_ptr<Mesh> GetMesh() { return mesh; }
	std::shared_ptr<Material> GetMaterial() { return material; }
	CameraComponent* GetCamera() { return camera; }

	float opacity = 1.0f;
	Vector3 special_color = Vector3(0.0f, 0.0f, 0.0f);
private:
	Renderer* renderer{ nullptr };
	CameraComponent* camera{ nullptr };
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
	bool isVisible;
	GameObject* owner{ nullptr }; // Who owns the body
};