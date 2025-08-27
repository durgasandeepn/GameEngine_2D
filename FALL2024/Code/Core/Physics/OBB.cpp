/****************************************************************
// File Name: OBB
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Simple Oriented Bounding Box for Physics Collisions
****************************************************************/

#include "precompiled.h"
#include "OBB.h"
#include <iostream>
#include "ResourceManagement/ResourceManager.h"

OBB::OBB(const Vector3& center, const Vector3& halfExtents)
	: localCenter(center), localHalfExtents(halfExtents),
	worldCenter(center), worldHalfExtents(halfExtents)
{
	localRight = worldRight = Vector3(1, 0, 0);
	localUp = worldUp = Vector3(0, 1, 0);
}

void OBB::Update(Transform& transform)
{
	// Get the transform matrix once
	worldCenter = transform.GetPosition();

	// Update orientation vectors using rotation only
	// We can get this directly from the transform's rotation
	Matrix4 transformMatrix = transform.GetLocalMatrix();
	float angle = transform.GetRotation().z; // For 2D we only need Z rotation
	worldRight = Vector3(transformMatrix.GetElement(0, 0), transformMatrix.GetElement(1, 0), 0.0f).Normalized();
	worldUp = Vector3(transformMatrix.GetElement(0, 1), transformMatrix.GetElement(1, 1), 0.0f).Normalized();

	// Update half extents with scale
	Vector3 scale = transform.GetScale();
	worldHalfExtents = Vector3(
		localHalfExtents.x * std::abs(scale.x),
		localHalfExtents.y * std::abs(scale.y),
		0.0f
	);
}

void OBB::GetCorners(Vector3 corners[4]) const
{
	Vector3 rightOffset = worldRight * worldHalfExtents.x;
	Vector3 upOffset = worldUp * worldHalfExtents.y;

	corners[0] = worldCenter - rightOffset - upOffset; // Bottom-left
	corners[1] = worldCenter + rightOffset - upOffset; // Bottom-right
	corners[2] = worldCenter + rightOffset + upOffset; // Top-right
	corners[3] = worldCenter - rightOffset + upOffset; // Top-left
}

void OBB::Project(const Vector3& axis, float& min, float& max) const
{
	// Get absolute position of corners in world space
	Vector3 corners[4];
	GetCorners(corners);

	// Project directly onto axis
	min = max = corners[0].Dot(axis);

	for (int i = 1; i < 4; i++) {
		float proj = corners[i].Dot(axis);
		min = std::min(min, proj);
		max = std::max(max, proj);
	}
}

Vector3 OBB::GetCenter() const
{
	return worldCenter;
}

Vector3 OBB::GetHalfExtents() const
{
	return worldHalfExtents;
}

Vector3 OBB::GetRight() const
{
	return worldRight;
}

Vector3 OBB::GetUp() const
{
	return worldUp;
}
