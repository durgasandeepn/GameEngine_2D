/****************************************************************
// File Name: OBB
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Simple Oriented Bounding Box for Physics Collisions
****************************************************************/

#pragma once

#include "Shape.h"
#include "Renderer/Renderer.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"

class OBB : public Shape {
public:
	OBB(const Vector3& center= Vector3(-0.0f, -0.0f, 0.0f), const Vector3& halfExtents=Vector3(0.5f, 0.5f, 0.0f));
	~OBB() = default;
	Type GetType() const override { return Type::OBB; }

	void Update(Transform& transform) override;

	void GetCorners(Vector3 corners[4]) const;

	void Project(const Vector3& axis, float& min, float& max) const;

	Vector3 GetCenter() const;
	Vector3 GetHalfExtents() const;
	Vector3 GetRight() const;
	Vector3 GetUp() const;

	//void InitializeDebugDraw(Renderer* renderer);
	//void DrawDebugLines(const Matrix4& view, const Matrix4& projection) const;

private:
	// Local space values (original, unchanged)
	Vector3 localCenter;
	Vector3 localHalfExtents;
	Vector3 localRight;
	Vector3 localUp;

	// World space values (transformed)
	Vector3 worldCenter;
	Vector3 worldHalfExtents;
	Vector3 worldRight;
	Vector3 worldUp;


	//std::shared_ptr<Mesh> debugMesh;
	//std::shared_ptr<Material> debugMaterial;
	//Renderer* renderer;
};