/****************************************************************
// File Name: DebugRenderComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Component dedicated to handling rendering debug data in game.
// Things like physics collision boxes, and velocity.
****************************************************************/

#include "precompiled.h"
#include "DebugRenderComponent.h"
#include "Engine.h"

DebugRenderComponent::DebugRenderComponent()
{
	renderable = std::make_unique<DebugRenderable>();
}

void DebugRenderComponent::Initialize()
{
	RenderManager::Instance().AddDebugRenderable(renderable.get());
	renderable->SetOwner(owner);
}

void DebugRenderComponent::Update(float deltaTime)
{  
}

void DebugRenderComponent::Shutdown()
{
	RenderManager::Instance().RemoveDebugRenderable(renderable.get());
	renderable.reset();
}

void DebugRenderComponent::Serialize()
{

}

void DebugRenderComponent::Deserialize(const rapidjson::Value& json)
{

}

void DebugRenderComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}