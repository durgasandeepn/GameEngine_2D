/****************************************************************
// File Name: Material
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Gives a 3D object Textures, Colors, Shaders, Visual Effects, etc.
****************************************************************/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <optional>
#include <vector>
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Shader.h"

class Shader;
class Texture;

class Material
{
public:

	Material(std::shared_ptr<Shader> shader);
	Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture>);
	virtual ~Material() = default;

	// Shader management
	void SetShader(std::shared_ptr<Shader> newShader);
	std::shared_ptr<Shader> GetShader() const;

	// Property setters
	void SetProperty(const std::string& name, unsigned int value);
	void SetProperty(const std::string& name, int value);
	void SetProperty(const std::string& name, float value);
	void SetProperty(const std::string& name, const Vector3& value);
	void SetProperty(const std::string& name, const Matrix4& value);

	void SetModelMatrix(const Matrix4& value);
	void SetViewMatrix(const Matrix4& value);
	void SetProjectionMatrix(const Matrix4& value);
	void SetTextureOffset(const Vector3& value);
	void SetOpacity(float newOpacity);
	void SetFrameSize(const Vector3& value);

	// Texture setter
	void SetTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit);

	// Apply the material (to be called before rendering an object)
	virtual void Apply() const;
private:
	std::shared_ptr<Shader> shader;

	// A mapping of a name of a property to a value that can be any of uInt, int, float, vec3, or mat4
	std::unordered_map<std::string, std::variant<unsigned int, int, float, Vector3, Matrix4 >> properties;


	// Texture info data struct to handle texture unit mapped to a texture
	struct TextureInfo
	{
		std::shared_ptr<Texture> texture;
		unsigned int unit;
	};

	// Optional texture data so if we decide to have materials without textures
	std::optional<std::unordered_map<std::string, TextureInfo>> textureData;
};