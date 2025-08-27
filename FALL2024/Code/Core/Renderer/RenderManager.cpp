/****************************************************************
// File Name: RenderManager
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Manages *all* Renderables in the game at once, using a std::vector.
// Can add, remove and clear renderables.
// Also renders these renderables
****************************************************************/

#include "precompiled.h"
#include "RenderManager.h"
#include "Object/GameObject.h"

void RenderManager::AddRenderable(Renderable* renderable)
{
	if (std::find(renderables.begin(), renderables.end(), renderable) == renderables.end()) {
		renderables.push_back(renderable);
	}
}

void RenderManager::AddUIRenderable(Renderable* renderable)
{
	if (std::find(uiRenderables.begin(), uiRenderables.end(), renderable) == uiRenderables.end()) {
		uiRenderables.push_back(renderable);
	}
}

void RenderManager::AddDebugRenderable(DebugRenderable* renderable)
{
	if (std::find(debugRenderables.begin(), debugRenderables.end(), renderable) == debugRenderables.end()) {
		debugRenderables.push_back(renderable);
	}
}

void RenderManager::RemoveRenderable(Renderable* renderable)
{
	renderables.erase(
		std::remove(renderables.begin(), renderables.end(), renderable),
		renderables.end()
	);
}

void RenderManager::RemoveUIRenderable(Renderable* renderable)
{
	uiRenderables.erase(
		std::remove(uiRenderables.begin(), uiRenderables.end(), renderable),
		uiRenderables.end()
	);
}

void RenderManager::RemoveDebugRenderable(DebugRenderable* renderable)
{
	debugRenderables.erase(
		std::remove(debugRenderables.begin(), debugRenderables.end(), renderable),
		debugRenderables.end()
	);
}

void RenderManager::ClearRenderables()
{
	renderables.clear();
	uiRenderables.clear();
	debugRenderables.clear();
}

void RenderManager::Render(bool debugMode)
{
	for (auto renderable : renderables) {
		if (renderable && renderable->GetOwner()->GetIsActive())
		{
			renderable->Render();
		}
	}

	for (auto ui : uiRenderables) {
		if (ui && ui->GetOwner()->GetIsActive()) {
			ui->Render();
		}
	}

	if (debugMode) {
		for (auto debug : debugRenderables) {
			debug->Render();
		}
	}
}
