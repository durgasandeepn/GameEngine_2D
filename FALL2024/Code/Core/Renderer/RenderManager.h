/****************************************************************
// File Name: RenderManager
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Manages *all* Renderables in the game at once, using a std::vector.
// Can add, remove and clear renderables.
// Also renders these renderables
****************************************************************/

#pragma once

#include "Math/Vector3.h"
#include "Event/EventManager.h"
#include "Event/Events/CollisionEvent.h"
#include "Renderer/Renderable.h"
#include "Renderer/DebugRenderable.h"

class RenderManager {
public:
	static RenderManager& Instance()
	{
		static RenderManager instance;
		return instance;
	}

	/**
	* @brief Adds a given Renderable to the vector of renderables.
	* @param renderable - The Renderable to add to the vector.
	*/
	void AddRenderable(Renderable* renderable);
	void AddUIRenderable(Renderable* renderable);
	void AddDebugRenderable(DebugRenderable* renderable);
	/**
	* @brief Removes a given Renderable to the vector of bodies.
	* @param renderable - The Renderable to remove from the vector.
	*/
	void RemoveRenderable(Renderable* renderable);
	void RemoveUIRenderable(Renderable* renderable);
	void RemoveDebugRenderable(DebugRenderable* renderable);
	/**
	* @brief Clears all renderables stored in the Vector
	*/
	void ClearRenderables();
	/**
	* @brief Loops through the stored PhysicsBodies, calling integrate on each one.
	* @param deltaTime - Time since last frame call.
	*/
	void Render(bool debugMode);

	const std::vector<Renderable*>& GetRenderables() const { return renderables; }

private:
	std::vector<Renderable*> renderables;
	std::vector<Renderable*> uiRenderables;
	std::vector<DebugRenderable*> debugRenderables;
	static RenderManager* instance;

	RenderManager() = default;
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
};