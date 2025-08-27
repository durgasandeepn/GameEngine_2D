/****************************************************************
// File Name: PhysicsManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Manages *all* PhysicsBodies in the game at once, using a std::vector.
// Can add, remove and clear bodies.
// Updates the bodies by calling integrate on them.
****************************************************************/

#include "precompiled.h"
#include "PhysicsManager.h"
#include <algorithm>
#include "Object/GameObject.h"

void PhysicsManager::AddBody(PhysicsBody* body)
{
	// Don't allow duplicates
	if (std::find(bodies.begin(), bodies.end(), body) == bodies.end()) {
		bodies.push_back(body);
	}
}

void PhysicsManager::RemoveBody(PhysicsBody* body)
{
	bodies.erase(
		std::remove(bodies.begin(), bodies.end(), body),
		bodies.end()
	);
}

void PhysicsManager::ClearBodies()
{
	bodies.clear();
}

void PhysicsManager::Update(float deltaTime)
{
	for (auto body : bodies) {
		body->Integrate(deltaTime);
	}

	CheckCollisions();
}

void PhysicsManager::CheckCollisions()
{
	if (bodies.empty()) return;
	Contact contact;
	for (size_t i = 0; i < bodies.size(); i++) 
	{
		for (size_t j = i + 1; j < bodies.size(); j++) 
		{
			if (!bodies[i]->CanCollideWith(bodies[j]) ||
				!bodies[j]->CanCollideWith(bodies[i]) ||
				!bodies[i]->GetOwner()->GetIsActive() ||
				!bodies[j]->GetOwner()->GetIsActive())
			{
				continue;
			}

			if (collisionGenerator.GenerateContact(bodies[i], bodies[j], contact)) {
				ResolveCollisions(contact);

				// Don't generate more collision events if we're already deleting either bodies
				if (!contact.bodies[0]->GetOwner()->GetShouldDelete() && !contact.bodies[1]->GetOwner()->GetShouldDelete()) {
					CollisionEvent event(
						contact.bodies[0]->GetOwner(),
						contact.bodies[1]->GetOwner()
					);
					EventManager::Instance().BroadcastEvent(event);
				}
			}
		}
	}
}

void PhysicsManager::ResolveCollisions(const Contact& contact)
{
	PhysicsBody* bodyA = contact.bodies[0];
	PhysicsBody* bodyB = contact.bodies[1];

	if (bodyA->GetIsTrigger() || bodyB->GetIsTrigger()) return;

	if (!bodyA || !bodyB) return;

	// Apply collision resolution logic here
	float correctionDepth = std::max(contact.penetrationDepth, 0.001f);
	correctionDepth = std::min(correctionDepth, 0.1f);
	Vector3 correction = contact.normal * correctionDepth;

	if (!bodyA->GetIsKinematic()) {
		bodyA->GetOwner()->SetLocalPosition(bodyA->GetOwner()->GetLocalPosition() - correction * 0.5f);
	}
	if (!bodyB->GetIsKinematic()) {
		bodyB->GetOwner()->SetLocalPosition(bodyB->GetOwner()->GetLocalPosition() + correction * 0.5f);
	}

	// Adjust velocities based on collision response
	//(e.g., use impulse-based resolution)
	Vector3 relativeVelocity = bodyB->GetVelocity() - bodyA->GetVelocity();
	float separatingVelocity = relativeVelocity.Dot(contact.normal);

	if (separatingVelocity < 0) { // Only resolve if they're moving toward each other
		float restitution = std::min(bodyA->GetRestitution(), bodyB->GetRestitution());
		float impulseMagnitude = -(1.0f + restitution) * separatingVelocity;
		impulseMagnitude /= (bodyA->GetInverseMass() + bodyB->GetInverseMass());
		impulseMagnitude = std::min(impulseMagnitude, 10.0f);

		Vector3 impulse = contact.normal * impulseMagnitude;
		if (!bodyA->GetIsKinematic()) {
			bodyA->SetVelocity(bodyA->GetVelocity() - impulse * bodyA->GetInverseMass());
		}
		if (!bodyB->GetIsKinematic()) {
			bodyB->SetVelocity(bodyB->GetVelocity() + impulse * bodyB->GetInverseMass());
		}
	}

	// Calculate and apply friction
	Vector3 tangent = relativeVelocity - (contact.normal * relativeVelocity.Dot(contact.normal));
	if (tangent.MagnitudeSquared() > 0.0001f) { // Avoid division by zero
		tangent.Normalized();
	}

	float frictionCoefficient = std::min(bodyA->GetFriction(), bodyB->GetFriction());
	float normalForce = correctionDepth; // Approximation; use actual collision normal force if available
	Vector3 frictionForce = tangent * frictionCoefficient * normalForce;

	// Apply friction to both bodies
	if (!bodyA->GetIsKinematic()) {
		bodyA->SetVelocity(bodyA->GetVelocity() + frictionForce * bodyA->GetInverseMass());
	}
	if (!bodyB->GetIsKinematic()) {
		bodyB->SetVelocity(bodyB->GetVelocity() - frictionForce * bodyB->GetInverseMass());
	}
}
