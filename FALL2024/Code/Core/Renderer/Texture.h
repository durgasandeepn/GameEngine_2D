/****************************************************************
// File Name: Texture
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Describes the concept of a "Texture"
// a 2D image that can be applied to 3D objects when rendering.
****************************************************************/

#pragma once

#include <string>
#include <memory>
#include <glew.h>

/*
* 
*/
class Texture
{
public:
	enum class FilterMode { Nearest, Linear, MipmapNearest, MipmapLinear };
	enum class WrapMode { Repeat, MirroredRepeat, ClampToEdge, ClampToBorder };
	enum class TextureType { Texture2D, Texture3D, CubeMap };

	// Public facing method to create a texture. Usage: Texture.Create({filepath}, Type::{type});

	Texture(unsigned char* data, int width, int height, int channels, TextureType type);
	~Texture();

	Texture(const Texture&) = delete; // Prevents copying textures
	Texture& operator=(const Texture& other) = delete; // Prevents assigning textures

	//Texture(Texture&& other) noexcept;
	//Texture& operator=(Texture&& other) noexcept;

	void Bind(unsigned int unit = 0) const;
	void Unbind() const;

	void SetFilterMode(FilterMode mode);
	void SetWrapMode(WrapMode mode);

	void GenerateMipmaps();
private:
	// ID of the texture you are using
	GLuint textureID;
	int width, height, channels;
	GLenum format;
	TextureType type;

	void SetupTextureParameters();

};