/****************************************************************
// File Name: CollisionGenerator
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: A series of checks that can be used by the PhysicsManager
// to see if any two collision shapes are colliding with one another.
****************************************************************/

#pragma once

#include "Shape.h"
#include "Contact.h"
#include <array>
#include <vector>

class CollisionGenerator {
public:
	using CollisionCheck = bool(*)(const Shape*, const Shape*, Contact&);

	CollisionGenerator();

	bool GenerateContact(PhysicsBody* body1, PhysicsBody* body2, Contact& contact);

private:
	std::array<std::array<CollisionCheck, 3>, 3> collisionChecks;

	void InitializeCollisionMatrix();

	static bool AABBvsAABB(const Shape* a, const Shape* b, Contact& contact);
	static bool AABBvsOBB(const Shape* a, const Shape* b, Contact& contact);
	static bool AABBvsCircle(const Shape* a, const Shape* b, Contact& contact);

	static bool OBBvsOBB(const Shape* a, const Shape* b, Contact& contact);
	void DrawProjection(const Vector3& axis, float minProjection, float maxProjection, const Vector3& center, const Vector3& color);
	static bool OBBvsAABB(const Shape* a, const Shape* b, Contact& contact);
	static bool OBBvsCircle(const Shape* a, const Shape* b, Contact& contact);
	
	static bool CirclevsCircle(const Shape* a, const Shape* b, Contact& contact);
	static bool CirclevsAABB(const Shape* a, const Shape* b, Contact& contact);
	static bool CirclevsOBB(const Shape* a, const Shape* b, Contact& contact);
};