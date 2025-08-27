/****************************************************************
// File Name: PhysicsBody
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Equivalent to a RigidBody in similar Engines.
// A physics object in a greater physics system. Handles simulating the physics
// of the object using variables like mass, force, etc.
****************************************************************/

#include "precompiled.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include <iostream>


PhysicsBody::PhysicsBody(GameObject* owner)
	: owner(owner) {}

void PhysicsBody::SetMass(float newMass)
{
	mass = newMass;
	inverseMass = newMass > 0.0f ? 1.0f / newMass : 0.0f;
	isKinematic = (newMass == 0.0f);
}

void PhysicsBody::SetKinematic(bool kinematicValue)
{
	isKinematic = kinematicValue;
	if (isKinematic) {
		mass = 0.0f;
		inverseMass = 0.0f;
	}
}

void PhysicsBody::Integrate(float dt)
{
	if (isKinematic) {
		if (collisionShape)
			UpdateCollisionShape();
		return;
	}

	if (useGravity) {
		force += PhysicsManager::Instance().GetGravity() * mass;
	}

	// Semi-implicit Euler integration
	// TODO determine if a different integration should be used
	velocity = velocity + (force * inverseMass + acceleration) * dt;

	// Linear drag
	velocity = velocity * (1.0f - drag * dt);

	// Check if object is going too fast, cap it's speed
	if (velocity.Magnitude() > terminalVelocity) {
		velocity = velocity.Normalized() * terminalVelocity;
	}

	// Update position through the owner's transform
	Vector3 newPosition = owner->GetLocalPosition() + velocity * dt;
	owner->SetLocalPosition(newPosition);

	// Update collision shape
	if (collisionShape) {
		UpdateCollisionShape();
	}

	// Reset force accumulator
	force = Vector3(0, 0, 0);
}

bool PhysicsBody::CanCollideWith(const PhysicsBody* other) const
{
	return (collisionMask & static_cast<uint32_t>(other->GetLayer())) != 0;
}

void PhysicsBody::UpdateCollisionShape()
{
	Transform currentTransform;
	currentTransform.SetPosition(owner->GetLocalPosition());
	currentTransform.SetRotation(owner->GetLocalRotation());
	currentTransform.SetScale(owner->GetLocalScale());

	collisionShape->Update(currentTransform);
}
