/****************************************************************
// File Name: UIComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Durga Sandeep - Created the base, Ju-ve Chankasemporn - advised in development
// Description: Component for rendering the UI
****************************************************************/

#pragma once

#include "Component.h"
#include "Renderer/Renderable.h"

// Rendering
// Material
// Shader
// Image assets
// position must be before camer screen (close to the camera)

//Changed the UIComponent inheritance from RenderComponent2D.h to 

class UIComponent : public Component {

public:
	UIComponent();
	~UIComponent() = default;

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