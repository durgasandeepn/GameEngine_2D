/****************************************************************
// File Name: CollisionGenerator
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: A series of checks that can be used by the PhysicsManager
// to see if any two collision shapes are colliding with one another.
****************************************************************/

#include "precompiled.h"
#include "CollisionGenerator.h"
#include "AABB.h"
#include "OBB.h"
#include "Circle.h"

CollisionGenerator::CollisionGenerator()
{
	InitializeCollisionMatrix();
}

bool CollisionGenerator::GenerateContact(PhysicsBody* body1, PhysicsBody* body2, Contact& contact)
{
	Shape* shape1 = body1->GetShape();
	Shape* shape2 = body2->GetShape();

	// Ensure neither body is missing a shape
	if (!shape1 || !shape2) return false;

	// Retrieve shape types as integers to index into the collision matrix
	int type1 = static_cast<int>(shape1->GetType());
	int type2 = static_cast<int>(shape2->GetType());

	CollisionCheck check = collisionChecks[type1][type2];
	if (check) {
		// If a collision check function exists, call it.
		if (check(shape1, shape2, contact)) {
			// Populate the contact structure with the colliding bodies
			contact.bodies[0] = body1;
			contact.bodies[1] = body2;
			return true;
		}
	}
	return false;
}

/*Initializes the collision function matrix to map shape types to specific functions.
Potential improvement: If the number of shape types grows, a more scalable mapping (e.g., a hash map) might be better. */
void CollisionGenerator::InitializeCollisionMatrix()
{
	for (auto& row : collisionChecks)
		for (auto& check : row)
			check = nullptr;

	// Set up existing collision checks
	collisionChecks[static_cast<int>(Shape::Type::AABB)][static_cast<int>(Shape::Type::AABB)] = &AABBvsAABB;
	collisionChecks[static_cast<int>(Shape::Type::AABB)][static_cast<int>(Shape::Type::OBB)] = &AABBvsOBB;
	collisionChecks[static_cast<int>(Shape::Type::AABB)][static_cast<int>(Shape::Type::CIRCLE)] = &AABBvsCircle;


	collisionChecks[static_cast<int>(Shape::Type::OBB)][static_cast<int>(Shape::Type::OBB)] = &OBBvsOBB;
	collisionChecks[static_cast<int>(Shape::Type::OBB)][static_cast<int>(Shape::Type::AABB)] = &OBBvsAABB;
	collisionChecks[static_cast<int>(Shape::Type::OBB)][static_cast<int>(Shape::Type::CIRCLE)] = &OBBvsCircle;

	collisionChecks[static_cast<int>(Shape::Type::CIRCLE)][static_cast<int>(Shape::Type::CIRCLE)] = &CirclevsCircle;
	collisionChecks[static_cast<int>(Shape::Type::CIRCLE)][static_cast<int>(Shape::Type::AABB)] = &CirclevsAABB;
	collisionChecks[static_cast<int>(Shape::Type::CIRCLE)][static_cast<int>(Shape::Type::OBB)] = &CirclevsOBB;
}

bool CollisionGenerator::AABBvsAABB(const Shape* a, const Shape* b, Contact& contact)
{
	const AABB* aabb1 = static_cast<const AABB*>(a);
	const AABB* aabb2 = static_cast<const AABB*>(b);

	// Obtain min and max bounds of each AABB
	Vector3 min1 = aabb1->GetMin();
	Vector3 max1 = aabb1->GetMax();
	Vector3 min2 = aabb2->GetMin();
	Vector3 max2 = aabb2->GetMax();


	// Check for overlap along each axis
	float overlapX = std::min(max1.x, max2.x) - std::max(min1.x, min2.x);
	float overlapY = std::min(max1.y, max2.y) - std::max(min1.y, min2.y);
	float overlapZ = std::min(max1.z, max2.z) - std::max(min1.z, min2.z);

	// If there is no overlap on any axis, return false
	if (overlapX < 0 || overlapY < 0 || overlapZ < 0)
		return false;
	

	// Check overlaps and determine the smallest positive overlap axis
	if (overlapX > 0 && (overlapX < overlapY || overlapY <= 0) && (overlapX < overlapZ || overlapZ <= 0))
	{
		contact.penetrationDepth = overlapX;
	}
	else if (overlapY > 0 && (overlapY < overlapX || overlapX <= 0) && (overlapY < overlapZ || overlapZ <= 0))
	{ 
		contact.penetrationDepth = overlapY;
	}
	else if (overlapZ > 0)
	{
		contact.penetrationDepth = overlapZ;
	}

	// Calculate relative positions
	Vector3 center1 = aabb1->GetCenter();
	Vector3 center2 = aabb2->GetCenter();
	Vector3 relativePosition = center2 - center1;

	// Assign the contact normal based on the dominant axis of relative position
	if (std::abs(relativePosition.x) > std::abs(relativePosition.y) && std::abs(relativePosition.x) > std::abs(relativePosition.z)) {
		contact.normal = Vector3(relativePosition.x > 0.0f ? 1.0f : -1.0f, 0.0f, 0.0f); // X-axis
	}
	else if (std::abs(relativePosition.y) > std::abs(relativePosition.z)) {
		contact.normal = Vector3(0.0f, relativePosition.y > 0.0f ? 1.0f : -1.0f, 0.0f); // Y-axis
	}
	else {
		contact.normal = Vector3(0.0f, 0.0f, relativePosition.z > 0.0f ? 1.0f : -1.0f); // Z-axis
	}

	// Approximate contact points as overlapping midpoints (could refine further)
	contact.point = (center1 + center2) * 0.5f;
	return true;
}

bool CollisionGenerator::AABBvsOBB(const Shape* a, const Shape* b, Contact& contact)
{
	// Convert AABB to OBB and call OBBvsOBB on it
	const AABB* aabb = static_cast<const AABB*>(a);
	const OBB* obb = static_cast<const OBB*>(b);

	Vector3 aabbCenter = (aabb->GetMin() + aabb->GetMax()) * 0.5;
	Vector3 halfExtents = (aabb->GetMax() - aabb->GetMin()) * 0.5;

	OBB aabbAsOBB(aabbCenter, halfExtents);

	return OBBvsOBB(&aabbAsOBB, obb, contact);
}

bool CollisionGenerator::AABBvsCircle(const Shape* a, const Shape* b, Contact& contact)
{
	return CirclevsAABB(b, a, contact);
}

// TODO: This fails at direct corner->axis collisions, never found a solution    ->         /
// If getting weird false detections, might need to respec this.                             [ ]
bool CollisionGenerator::OBBvsOBB(const Shape* a, const Shape* b, Contact& contact)
{
	const OBB* obb1 = static_cast<const OBB*>(a);
	const OBB* obb2 = static_cast<const OBB*>(b);

	Vector3 centerDiff = obb2->GetCenter() - obb1->GetCenter();
	float scale = obb1->GetHalfExtents().x * 2.0f;
	Vector3 axes[4] =
	{
		obb1->GetRight().Normalized(),
		obb1->GetUp().Normalized(),
		obb2->GetRight().Normalized(),
		obb2->GetUp().Normalized()
	};

	float minPenetration = std::numeric_limits<float>::max();
	Vector3 bestAxis;

	for (int i = 0; i < 4; ++i)
	{
		// Project both OBBs onto the axis
		float min1, max1, min2, max2;
		obb1->Project(axes[i], min1, max1);
		obb2->Project(axes[i], min2, max2);

		float extent1 = (max1 - min1) * 0.5f;
		float extent2 = (max2 - min2) * 0.5f;

		float rawDistance = std::abs(centerDiff.Dot(axes[i]));
		float scaledDistance = rawDistance * scale;

		// Check for overlap
		if (rawDistance > extent1 + extent2)
		{
			return false; // Separating axis found
		}

		float overlap = (extent1 + extent2) - scaledDistance;
		if (overlap > 0.0f && overlap < minPenetration) {
			minPenetration = overlap;
		}
	}

	contact.penetrationDepth = minPenetration;

	Vector3 relativePosition = obb2->GetCenter() - obb1->GetCenter();
	Vector3 localRelative = Vector3(
		relativePosition.Dot(obb1->GetRight()),    // Projection onto the right axis
		relativePosition.Dot(obb1->GetUp()),       // Projection onto the up axis
		0.0f
	);

	// Determine the dominant axis in local space
	if (std::abs(localRelative.x) > std::abs(localRelative.y) && std::abs(localRelative.x) > std::abs(localRelative.z)) {
		contact.normal = obb1->GetRight() * (localRelative.x > 0.0f ? 1.0f : -1.0f);
	}
	else if (std::abs(localRelative.y) > std::abs(localRelative.z)) {
		contact.normal = obb1->GetUp() * (localRelative.y > 0.0f ? 1.0f : -1.0f);
	}

	// If no separating axis is found, we                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    have a collision
	contact.point = (obb1->GetCenter() + obb2->GetCenter()) * 0.5f;
	printf("We are colliding!\n");
	return true;
}

bool CollisionGenerator::OBBvsAABB(const Shape* a, const Shape* b, Contact& contact)
{
	return AABBvsOBB(b, a, contact);
}

bool CollisionGenerator::OBBvsCircle(const Shape* a, const Shape* b, Contact& contact)
{
	return CirclevsOBB(b, a, contact);
}

bool CollisionGenerator::CirclevsCircle(const Shape* a, const Shape* b, Contact& contact)
{
	const Circle* circle1 = static_cast<const Circle*>(a);
	const Circle* circle2 = static_cast<const Circle*>(b);
	if (!circle1 || !circle2) return false;

	Vector3 diff = circle2->GetCenter() - circle1->GetCenter();
	float distSquared = diff.MagnitudeSquared();
	float radiusSum = circle1->GetRadius() + circle2->GetRadius();

	if (distSquared <= radiusSum * radiusSum) {
		contact.point = circle1->GetCenter() + diff * 0.5f;
		return true;
	}
	return false;
}

bool CollisionGenerator::CirclevsAABB(const Shape* a, const Shape* b, Contact& contact)
{
	const Circle* circle = static_cast<const Circle*>(a);
	const AABB* aabb = static_cast<const AABB*>(b);
	if (!circle || !aabb) return false;

	Vector3 closestPoint;
	Vector3 circleCenter = circle->GetCenter();

	closestPoint.x = std::max(aabb->GetMin().x, std::min(circleCenter.x, aabb->GetMax().x));
	closestPoint.y = std::max(aabb->GetMin().y, std::min(circleCenter.y, aabb->GetMax().y));
	closestPoint.z = 0.0f;

	Vector3 diff = circleCenter - closestPoint;
	float distSquared = diff.MagnitudeSquared();

	if (distSquared <= circle->GetRadius() * circle->GetRadius()) {
		contact.point = closestPoint;
		return true;
	}
	return false;
}

bool CollisionGenerator::CirclevsOBB(const Shape* a, const Shape* b, Contact& contact)
{
	const Circle* circle = static_cast<const Circle*>(a);
	const OBB* obb = static_cast<const OBB*>(b);
	if (!circle || !obb) return false;

	// Convert circle center to OBB's local space
	Vector3 circleCenter = circle->GetCenter() - obb->GetCenter();

	// Get local space position using OBB's axis
	Vector3 localCenter(
		circleCenter.Dot(obb->GetRight()),
		circleCenter.Dot(obb->GetUp()),
		0.0f
	);

	// Find closes point in local space (clampped to OBB bounds)
	Vector3 closestPoint;
	closestPoint.x = std::max(-obb->GetHalfExtents().x,
		std::min(localCenter.x, obb->GetHalfExtents().x));
	closestPoint.y = std::max(-obb->GetHalfExtents().y,
		std::min(localCenter.y, obb->GetHalfExtents().y));

	// Convert back to world space
	Vector3 worldClosest = obb->GetCenter() +
		obb->GetRight() * closestPoint.x +
		obb->GetUp() * closestPoint.y;

	// Check if closest point is within circle's radius
	Vector3 diff = circle->GetCenter() - worldClosest;
	float distSquared = diff.MagnitudeSquared();

	if (distSquared <= circle->GetRadius() * circle->GetRadius()) {
		contact.point = worldClosest;
		contact.normal = -diff.Normalized();
		contact.penetrationDepth = circle->GetRadius() - diff.Magnitude();
		return true;
	}
	return false;
}
