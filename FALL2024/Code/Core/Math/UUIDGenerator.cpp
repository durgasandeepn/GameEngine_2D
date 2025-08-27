/****************************************************************
// File Name: UUIDGenerator
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: A class for generating a Unique ID based on a simple counter
****************************************************************/

#include "precompiled.h"
#include "UUIDGenerator.h"

uint32_t UUIDGenerator::GenerateUUID()
{
    return counter.fetch_add(1, std::memory_order_relaxed);
}
