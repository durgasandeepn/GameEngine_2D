/****************************************************************
// File Name: Circle
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Simple Circle collider for Physics Collisions
****************************************************************/

#include "precompiled.h"
#include "Circle.h"
#include <iostream>

Circle::Circle(const Vector3& center, float radius)
	: center(center), radius(radius)
{
}

void Circle::Update(Transform& transform)
{
	// Update center pos
	Matrix4 transformMatrix = transform.GetLocalMatrix();
	center = Vector3(
		transformMatrix.GetElement(3, 0), // X translation
		transformMatrix.GetElement(3, 1), // Y translation
		0.0f
	);

	Vector3 scale = transform.GetScale();
	float maxScale = std::max({ std::abs(scale.x), std::abs(scale.y), std::abs(scale.z)});
	radius *= maxScale;
}
