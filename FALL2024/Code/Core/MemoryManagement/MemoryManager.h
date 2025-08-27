/****************************************************************
// File Name: MemoryManager
// © 2025 DigiPen (USA) Corporation
// Authors: Jacob Wilburn - base code, Alex Humphries - advising development
// Description: Tool used to allocate and deallocate memory efficiently.
****************************************************************/

#pragma once
#include "Object/GameObject.h"

struct MemoryData {
	int allocatedObjects;
	size_t memoryPoolSize;
	size_t freeListSize;
	uint32_t totalCreatedObject;
};

class MemoryManager {
public:
	static MemoryManager& Instance() {
		static MemoryManager instance;
		return instance;
	}

	void Initialize();

	/**
	* @brief uses the memory allocated in bulk on creation and sets the memory to use that 
	* instead of creating memory on the spot, allowing for fast allocation
	* @return a pointer to the GameObject allocated
	*/
	GameObject* AllocateMemory();

	/**
	* @brief calls the destructor on the game object being deallocated, then replaces the 
	* memory in the pooled memory allocated on creation
	* @param object - pointer to the object that is to be deallocated
	*/
	void DeallocateMemory(GameObject* object);

	/**
	* @brief frees all existing memory still allocated when engine is shut down
	*/
	void Shutdown();

	/**
	* @brief Returns a struct of memory data
	*/
	MemoryData GetDebugMemoryData();
private:
	std::vector<GameObject> memoryPool;
	std::list<GameObject*> freeList;
	int allocatedObjects = 0;
	uint32_t totalCreatedObject = 0;

	/**
	* Constructor, used to allocate a large pool of memory at compile time
	*/
	MemoryManager();

	/**
	* @brief function that will double the size of the memory pool if there is no more empty space
	*/
	void Reallocate();
};
