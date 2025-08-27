/****************************************************************
// File Name: Circle
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Simple Circle collider for Physics Collisions
****************************************************************/
#pragma once

#include "Shape.h"
#include <algorithm>
#include "Math/Transform.h"

class Circle : public Shape {
public:
	Circle(const Vector3& center = Vector3(0, 0, 0), float radius = 0.5f);

	Type GetType() const override { return Type::CIRCLE; }
	void Update(Transform& transform) override;
	Vector3 GetCenter() const { return center; }
	float GetRadius() const { return radius; }

private:
	Vector3 center;
	float radius;
};