/****************************************************************
// File Name: UUIDGenerator
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: A class for generating a Unique ID based on a simple counter
****************************************************************/
#pragma once

class UUIDGenerator {
public:
	static UUIDGenerator& Instance() {
		static UUIDGenerator instance;
		return instance;
	}

	uint32_t GenerateUUID();

private:
	std::atomic<uint32_t> counter;

	UUIDGenerator() : counter(1) {};
	UUIDGenerator(const UUIDGenerator&) = delete;
	UUIDGenerator& operator=(const UUIDGenerator&) = delete;
};