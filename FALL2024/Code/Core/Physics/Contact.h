/****************************************************************
// File Name: Contact
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Holds data relating to the contact made between two physics bodies on a collision
****************************************************************/


#pragma once
#include "PhysicsBody.h"
#include <vector>

class Contact {
public:
	Contact():
		point(Vector3(0,0,0)),
		normal(Vector3(0,0,0)),
		bodies(2, nullptr),
		penetrationDepth(0.0f)
	{}
	
	Vector3 point;
	//std::vector<Vector3> points;
	Vector3 normal; // Collision direction
	float penetrationDepth; // Depth of penetration between the bodies
	std::vector<PhysicsBody*> bodies; // Bodies involved in the collision
};