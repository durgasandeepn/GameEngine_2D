/****************************************************************
// File Name: Shape
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Base class for all collision shapes.
// Currently holds types for AABB, OBB, and Circle
****************************************************************/

#pragma once

#include "Math/Transform.h"

class Shape {
public:
	enum class Type {
		AABB,
		OBB,
		CIRCLE
	};

	virtual ~Shape() = default;
	virtual Type GetType() const = 0;
	virtual void Update(Transform& transform) = 0;
};