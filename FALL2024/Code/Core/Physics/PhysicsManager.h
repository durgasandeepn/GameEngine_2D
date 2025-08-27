/****************************************************************
// File Name: PhysicsManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Manages *all* PhysicsBodies in the game at once, using a std::vector.
// Can add, remove and clear bodies.
// Updates the bodies by calling integrate on them.
****************************************************************/

#pragma once

#include "CollisionGenerator.h"
#include "Event/EventManager.h"
#include "Event/Events/CollisionEvent.h"
#include "PhysicsBody.h"

class PhysicsManager {
public:
	static PhysicsManager& Instance()
	{
		static PhysicsManager instance;
		return instance;
	}

	/**
	* @brief Adds a given PhysicsBody to the vector of bodies.
	* @param body - The PhysicsBody to add to the vector.
	*/
	void AddBody(PhysicsBody* body);
	/**
	* @brief Removes a given PhysicsBody to the vector of bodies.
	* @param body - The PhysicsBody to remove from the vector.
	*/
	void RemoveBody(PhysicsBody* body);
	/**
	* @brief Clears all bodies stored in the Vector
	*/
	void ClearBodies();
	/**
	* @brief Loops through the stored PhysicsBodies, calling integrate on each one.
	* @param deltaTime - Time since last frame call.
	*/
	void Update(float deltaTime);

	const std::vector<PhysicsBody*>& GetBodies() const { return bodies; }
	const Vector3 GetGravity() const { return gravity; }

private:
	std::vector<PhysicsBody*> bodies;
	CollisionGenerator collisionGenerator;
	static PhysicsManager* instance;
	Vector3 gravity = Vector3(0.0f, -9.8f, 0.0f);

	PhysicsManager() = default;
	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;

	/**
	* @brief Loops through the stored PhysicsBodies, checking if any two are colliding with one another, using
	* CollisionGenerator.
	*/
	void CheckCollisions();
	/**
	* @brief Addresses a collision "Contact", correcting the position of the two colliding Bodies if needed.
	* @param contact - A Contact that represents who where and how two bodies collided.
	*/
	void ResolveCollisions(const Contact& contact);
};