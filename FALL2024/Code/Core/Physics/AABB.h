/****************************************************************
// File Name: AABB
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Simple Axis Aligned Bounding Box for Physics Collisions
****************************************************************/
#pragma once

#include "Shape.h"
#include "Math/Vector3.h"

class AABB : public Shape {
public:
	AABB(const Vector3& min = Vector3(-0.5f, -0.5f, -0.5f),
		const Vector3& max = Vector3(0.5f, 0.5f, 0.5f));
	~AABB() = default;

	Type GetType() const override { return Type::AABB; }
	void Update(Transform& transform) override;

	Vector3 GetMin()			const { return worldMin; }
	Vector3 GetMax()			const { return worldMax; }
	Vector3 GetCenter()			const { return (worldMin + worldMax) * 0.5f; }
	Vector3 GetHalfExtents()	const { return (worldMax - worldMin) * 0.5f; }
	float GetWidth()			const { return worldMax.x - worldMin.x; }
	float GetHeight()			const { return worldMax.y - worldMin.y; }
private:
	Vector3 localMin, localMax;
	Vector3 worldMin, worldMax;
};