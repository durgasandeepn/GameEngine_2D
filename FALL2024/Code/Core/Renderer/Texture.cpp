/****************************************************************
// File Name: Texture
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Describes the concept of a "Texture"
// a 2D image that can be applied to 3D objects when rendering.
****************************************************************/

#include "precompiled.h"
#include "Texture.h"
#include <iostream>


Texture::Texture(unsigned char* data, int width, int height, int channels, TextureType type)
	: textureID(0), width(width), height(height), channels(channels), format(GL_RGB), type(type)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Determine the texture format
	if (channels == 3) {
		format = GL_RGB;
	}
	else if (channels == 4) {
		format = GL_RGBA;
	}

	// Upload the data to the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	// Set default texture parameters
	SetupTextureParameters();

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	Unbind();
}

void Texture::Bind(unsigned int unit) const
{
	// Tell GPU a specific texture is active
	glActiveTexture(GL_TEXTURE0 + unit);
	// Bind texture
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetFilterMode(FilterMode mode)
{
	// Bind our textureID so we can modify the reference
	glBindTexture(GL_TEXTURE_2D, textureID);
	switch (mode)
	{
	case FilterMode::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case FilterMode::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case FilterMode::MipmapNearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case FilterMode::MipmapLinear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
	// Remove binding
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetWrapMode(WrapMode mode)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	GLint glMode;
	switch (mode)
	{
	case WrapMode::Repeat:
		glMode = GL_REPEAT;
		break;
	case WrapMode::MirroredRepeat:
		glMode = GL_MIRRORED_REPEAT;
		break;
	case WrapMode::ClampToEdge:
		glMode = GL_CLAMP_TO_EDGE;
		break;
	case WrapMode::ClampToBorder:
		glMode = GL_CLAMP_TO_BORDER;
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glMode);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::GenerateMipmaps()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetupTextureParameters()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

}