/****************************************************************
// File Name: MemoryManager
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn - base code, Alex Humphries - advising development
// Description: Tool used to allocate and deallocate memory efficiently.
****************************************************************/

#include "precompiled.h"
#include "MemoryManager.h"
#include <vector>

MemoryManager::MemoryManager() : memoryPool(1000) 
{
	for (GameObject& obj : memoryPool) {
		freeList.push_back(&obj);
	}
}

void MemoryManager::Initialize() {}

GameObject* MemoryManager::AllocateMemory() {
	// If we ever can't grab another node, make the memory pool bigger
	if (freeList.empty()) {
		Reallocate();
	}
	GameObject* obj = freeList.front();

	freeList.pop_front();
	allocatedObjects++;
	totalCreatedObject++;

	new (obj) GameObject();

	return obj;
}

void MemoryManager::DeallocateMemory(GameObject* object) {
	if (!object) {
		return;
	}

	object->~GameObject();
	freeList.push_back(object);
	allocatedObjects--;
}

void MemoryManager::Reallocate() 
{
	auto poolSize = memoryPool.size();
	std::vector<GameObject>::iterator iter = memoryPool.end();
	memoryPool.resize(poolSize * 2);
	for (iter; iter < memoryPool.end(); iter++) {
		freeList.push_back(&*iter);
	}
}

void MemoryManager::Shutdown() {
	freeList.clear();
	memoryPool.clear();
}

MemoryData MemoryManager::GetDebugMemoryData()
{
	MemoryData data{ allocatedObjects, memoryPool.size(), freeList.size(), totalCreatedObject};
	return data;
}