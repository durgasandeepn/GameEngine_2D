/****************************************************************
// File Name: RenderComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Component dedicated to handling rendering Objects in the game.
// Creates a renderable object and manages it's lifecycle
****************************************************************/
#pragma once
#include "Component.h"
#include "Renderer/Renderable.h"
class RenderComponent2D : public Component {

public:
	RenderComponent2D();
	~RenderComponent2D() = default;

	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void Shutdown() override;
	virtual void Serialize() override;
	virtual void Deserialize(const rapidjson::Value& json) override;
	virtual void Configure(const std::unordered_map<std::string, std::any>& properties) override;

	std::shared_ptr<Renderable> GetRenderable() { return renderable; }
private:
	std::shared_ptr<Renderable> renderable;

	std::shared_ptr<Material> ParseMaterial(const rapidjson::Value& materialJson) const;
	std::shared_ptr<Shader> ParseShader(const rapidjson::Value& materialJson) const;
	void ApplyTexture(const std::string& textureName, std::shared_ptr<Material>& material) const;

	std::shared_ptr<Mesh> ParseMesh(const rapidjson::Value& meshJson) const;
	std::shared_ptr<Mesh> CreateMesh();
};