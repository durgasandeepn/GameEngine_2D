/****************************************************************
// File Name: Material
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Gives a 3D object Textures, Colors, Shaders, Visual Effects, etc.
****************************************************************/

#include "precompiled.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include <stdexcept>
#include <iostream>

Material::Material(std::shared_ptr<Shader> shader) : shader(shader) {}

Material::Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: shader(shader)
{
	SetTexture("Texture", texture, 0);
	SetProperty("useTexture", 1);
	SetOpacity(1.0f);
}

void Material::SetShader(std::shared_ptr<Shader> newShader)
{
	shader = newShader;
}

std::shared_ptr<Shader> Material::GetShader() const
{
	return shader;
}

void Material::SetProperty(const std::string& name, unsigned int value)
{
	properties[name] = value;
}

void Material::SetProperty(const std::string& name, int value)
{
	properties[name] = value;
}

void Material::SetProperty(const std::string& name, float value)
{
	properties[name] = value;
}

void Material::SetProperty(const std::string& name, const Vector3& value)
{
	properties[name] = value;
}

void Material::SetProperty(const std::string& name, const Matrix4& value)
{
	properties[name] = value;
}

void Material::SetModelMatrix(const Matrix4& value)
{
	if (shader)
	{
		shader->SetMat4("ModelMatrix", value);
	}
	
}

void Material::SetViewMatrix(const Matrix4& value)
{
	if (shader)
	{
		shader->SetMat4("ViewMatrix", value);
	}
	
}

void Material::SetProjectionMatrix(const Matrix4& value)
{
	if (shader)
	{
		shader->SetMat4("ProjectionMatrix", value);
	}
}

void Material::SetTextureOffset(const Vector3& value)
{
	if (shader)
	{
		shader->SetVec3("offset", value);
	}
}

void Material::SetOpacity(float newOpacity)
{
	if (shader)
	{
		shader->SetFloat("Opacity", newOpacity);
	}
}

void Material::SetFrameSize(const Vector3& value)
{
	if (shader) {
		shader->SetVec3("frameSize", value);
	}
}

void Material::SetTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit)
{
	// Creates the map the first time we set a texture
	if (!textureData)
	{
		textureData = std::unordered_map<std::string, TextureInfo>();
	}

	(*textureData)[name] = { texture, unit };
}

void Material::Apply() const
{
	if (!shader)
	{
		throw std::runtime_error("Shader not set for material, cannot apply!");
	}

	shader->Enable();

	// Generic uniforms
	// Fancy way of looking at the property map and setting the specific
	// shader values that align with the type stored in properties;
	// i.e., setting UnsignedInt vs Int
	for (const auto& [name, value] : properties)
	{
		std::visit([this, &name](auto&& arg)
			{
				using T = std::decay_t<decltype(arg)>;
				if constexpr (std::is_same_v<T, unsigned int>)
				{
					shader->SetUnsignedInt(name, arg);
				}
				else if constexpr (std::is_same_v<T, int>)
				{
					shader->SetInt(name, arg);
				}
				else if constexpr (std::is_same_v<T, float>)
				{
					shader->SetFloat(name, arg);
				}
				else if constexpr (std::is_same_v<T, Vector3>)
				{
					shader->SetVec3(name, arg);
				}
				else if constexpr (std::is_same_v<T, Matrix4>)
				{
					shader->SetMat4(name, arg);
				}
			}, value);
	}

	if (textureData)
	{
		for (const auto& [name, texInfo] : *textureData)
		{
			if (texInfo.texture)
			{
				texInfo.texture->Bind(texInfo.unit);
				shader->SetInt(name, texInfo.unit);
			}
			else
			{
				// In a case where you don't want textures for your shader
				std::cerr << "Warning: Null texture for uniform " << name << std::endl;
			}
		}
	}
}
