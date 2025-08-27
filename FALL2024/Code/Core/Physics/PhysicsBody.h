/****************************************************************
// File Name: PhysicsBody
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Equivalent to a RigidBody in similar Engines.
// A physics object in a greater physics system. Handles simulating the physics
// of the object using variables like mass, force, etc.
****************************************************************/

#pragma once
#include <memory>
#include "Math/Vector3.h"
#include "Shape.h"
#include "Object/GameObject.h"
#include "CollisionLayer.h"

class PhysicsBody {
	friend class PhysicsManager;
public:
	PhysicsBody() = default;
	PhysicsBody(GameObject* owner);

	void SetOwner(GameObject* newOwner) { owner = newOwner; }

	void SetMass(float newMass);
	void SetKinematic(bool kinematicValue);
	void SetTrigger(bool triggerValue)				{ isTrigger = triggerValue; }
	void SetVelocity(const Vector3& vel)			{ velocity = vel; }
	void SetAcceleration(const Vector3& acc)		{ acceleration = acc; }
	void ApplyForce(const Vector3& f)				{ force = f; }
	void SetRestitution(float r)					{ restitution = r; }
	void SetFriction(float f)						{ friction = f; }
	void SetDrag(float d)							{ drag = d; }
	void SetTerminalVelocity(float f)				{ terminalVelocity = f; }
	void SetLayer(CollisionLayer newLayer)			{ layer = newLayer; }
	void SetCollisionMask(uint32_t mask)			{ collisionMask = mask; }
	void SetShape(std::shared_ptr<Shape> newShape)	{ collisionShape = newShape; }
	void SetUseGravity(bool gravityVal)				{ useGravity = gravityVal; }


	float GetMass()				const { return mass; }
	float GetInverseMass()		const { return inverseMass; }
	Vector3 GetVelocity()		const { return velocity; }
	Vector3 GetAcceleration()	const { return acceleration; }
	Vector3 GetForce()			const { return force; }
	float GetRestitution()		const { return restitution; }
	float GetFriction()			const { return friction; }
	float GetDrag()				const { return drag; }
	bool GetIsKinematic()		const { return isKinematic; }
	bool GetIsTrigger()			const { return isTrigger; }
	bool GetUseGravity()        const { return useGravity; }
	CollisionLayer GetLayer()   const { return layer; }
	uint32_t GetCollisionMask() const { return collisionMask; }
	Shape* GetShape()			const { return collisionShape.get(); }
	GameObject* GetOwner()			const { return owner; }
	/**
	* @brief Uses math and algorithms to set the position of the Body on a given grame
	* @param dt - DeltaTime
	*/
	void Integrate(float dt);

	/**
	* @brief Uses the collisionMask and the collision layer of the other PhysicsBody
	* to determine if these two bodies are allowed to collide
	* @param other - The other PhysicsBody to check
	*/
	bool CanCollideWith(const PhysicsBody* other) const;

private:
	float mass				= 1.0f; // Weight of body
	float inverseMass		= 1.0f; // Inverse weight of body
	Vector3 velocity		= Vector3(0, 0, 0); // Speed * direction of motion of body
	Vector3 acceleration	= Vector3(0, 0, 0); // Currently unused
	Vector3 force			= Vector3(0, 0, 0); // A force to be applied to the body
	float restitution		= 0.5f; // ?
	float friction			= 0.3f; // Friction of object, i.e. "stickiness"
	float terminalVelocity	= 10.0f; // Max velocity of the body
	float drag				= 0.0f;
	bool isKinematic		= false; // Whether the body is static
	bool isTrigger			= false; // Whether the body still triggers collisions, but isn't solid (passes through things)
	bool useGravity			= false; // Whether the body uses gravity
	CollisionLayer layer	= CollisionLayer::Default; // The layer this collision object is on
	uint32_t collisionMask	= ~0; // The collision mask for this object
	std::shared_ptr<Shape> collisionShape; // The collision shape of the body, AABB, OBB, or Circle
	GameObject* owner		{nullptr}; // Who owns the body

	void UpdateCollisionShape();
};