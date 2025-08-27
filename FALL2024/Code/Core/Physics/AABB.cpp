/****************************************************************
// File Name: AABB
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Simple Axis Aligned Bounding Box for Physics Collisions
****************************************************************/

#include "precompiled.h"
#include "AABB.h"
#include <iostream>

AABB::AABB(const Vector3& min, const Vector3& max)
	: localMin(min), localMax(max),
	worldMin(min), worldMax(max) {}

void AABB::Update(Transform& transform)
{
    // Define all 8 corners of the AABB in local space
    Vector3 corners[8] = {
        Vector3(localMin.x, localMin.y, localMin.z), // Bottom-left-front
        Vector3(localMax.x, localMin.y, localMin.z), // Bottom-right-front
        Vector3(localMin.x, localMax.y, localMin.z), // Top-left-front
        Vector3(localMax.x, localMax.y, localMin.z), // Top-right-front
        Vector3(localMin.x, localMin.y, localMax.z), // Bottom-left-back
        Vector3(localMax.x, localMin.y, localMax.z), // Bottom-right-back
        Vector3(localMin.x, localMax.y, localMax.z), // Top-left-back
        Vector3(localMax.x, localMax.y, localMax.z)  // Top-right-back
    };

    // Get the transformation matrix
    Matrix4 transformMatrix = transform.GetLocalMatrix();

    // Transform the first corner to initialize world bounds
    worldMin = worldMax = transformMatrix * corners[0];

    // Transform the rest of the corners and expand the world bounds
    for (int i = 1; i < 8; i++) {
        Vector3 transformed = transformMatrix * corners[i];
        worldMin.x = std::min(worldMin.x, transformed.x);
        worldMin.y = std::min(worldMin.y, transformed.y);
        worldMin.z = std::min(worldMin.z, transformed.z);
        worldMax.x = std::max(worldMax.x, transformed.x);
        worldMax.y = std::max(worldMax.y, transformed.y);
        worldMax.z = std::max(worldMax.z, transformed.z);
    }
}

