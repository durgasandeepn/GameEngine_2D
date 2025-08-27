/****************************************************************
// File Name: Shader
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Describes the concept of a Shader, a piece of code that modifies
// how objects are drawn in 3D spaces.
****************************************************************/

#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include <glew.h>

class Shader
{
public:
	Shader(const std::unordered_map<GLenum, std::string>& shaderSources);
	~Shader();

	void Enable() const;
	void Disable() const;

	/* API for setting uniform values */
	void SetUnsignedInt(const std::string& name, unsigned int value) const;
	void SetInt(const std::string& name, int value) const;
	void SetTwoInts(const std::string& name, int v0, int v1);
	void SetFloat(const std::string& name, float value) const;
	void SetVec2(const std::string& name, float x, float y) const;
	void SetVec3(const std::string& name, const Vector3& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w) const;
	void SetMat4(const std::string& name, const Matrix4& value) const;

	unsigned int GetID() const { return programID; }

private:
	unsigned int programID;
	mutable std::unordered_map<std::string, int> uniformLocationCache;
	std::unordered_map<GLenum, unsigned int> shaderIDs;

	unsigned int LoadShader(const std::string& shaderCode, GLenum shaderType);
	void LinkShaders();
	int GetUniformLocation(const std::string& name) const;
};