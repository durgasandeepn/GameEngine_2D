/****************************************************************
// File Name: CollisionLayer
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: The different collision layers for the Physics system
****************************************************************/
#pragma once
#include "precompiled.h"

enum class CollisionLayer : uint32_t {
	Default		= 1 << 0,
	Player		= 1 << 1,
	Enemy		= 1 << 2,
	Environment = 1 << 3,
	Projectile	= 1 << 4
};