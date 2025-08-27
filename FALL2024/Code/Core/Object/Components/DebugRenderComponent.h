/****************************************************************
// File Name: DebugRenderComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Component dedicated to handling rendering debug data in game.
// Things like physics collision boxes, and velocity.
****************************************************************/

#pragma once

#include "Object/Components/Component.h"
#include "Renderer/DebugRenderable.h"

class PhysicsComponent;

class DebugRenderComponent : public Component
{
public:

	DebugRenderComponent();
	~DebugRenderComponent() = default;

	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void Shutdown() override;
	virtual void Serialize() override;
	virtual void Deserialize(const rapidjson::Value& json) override;
	virtual void Configure(const std::unordered_map<std::string, std::any>& properties) override;

	std::shared_ptr<DebugRenderable> GetRenderable() { return renderable; }

private:
	std::shared_ptr<DebugRenderable> renderable;
};

