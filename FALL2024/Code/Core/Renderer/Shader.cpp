/****************************************************************
// File Name: Shader
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Describes the concept of a Shader, a piece of code that modifies
// how objects are drawn in 3D spaces.
****************************************************************/

#include "precompiled.h"
#include "Shader.h"
#include <iostream>
#include <algorithm>


// Retrieves a mapping of shaderTypes to the string formatted code of the shader from
// resource manager.
Shader::Shader(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	for (const auto& [shaderType, shaderCode] : shaderSources)
	{
		unsigned int shaderID = LoadShader(shaderCode, shaderType);
		shaderIDs[shaderType] = shaderID;
	}

	LinkShaders();
}

Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::Enable() const
{
	glUseProgram(programID);
}

void Shader::Disable() const
{
	glUseProgram(0);
}

void Shader::SetUnsignedInt(const std::string& name, unsigned int value) const
{
	glUniform1ui(GetUniformLocation(name), value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetTwoInts(const std::string& name, int v0, int v1)
{
	glUniform2i(GetUniformLocation(name), v0, v1);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(GetUniformLocation(name), x, y);
}

void Shader::SetVec3(const std::string& name, const Vector3& value) const
{
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetMat4(const std::string& name, const Matrix4& value) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value.GetData());
}

unsigned int Shader::LoadShader(const std::string& shaderCode, GLenum shaderType)
{
	unsigned int shaderID = glCreateShader(shaderType);
	const char* code = shaderCode.c_str();
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cerr << "Shader compilation error: " << infoLog << std::endl;
	}
	return shaderID;
}

void Shader::LinkShaders()
{
	programID = glCreateProgram();

	for (const auto& [type, id] : shaderIDs)
	{
		glAttachShader(programID, id);
	}

	glLinkProgram(programID);
	
	int success;
	char infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		std::cerr << "Shader program linking error: " << infoLog << std::endl;
	}

	for (const auto& [type, id] : shaderIDs)
	{
		glDeleteShader(id);
	}
}

int Shader::GetUniformLocation(const std::string& name) const
{
	// If the name of the uniform is cached already, supply the location
	auto it = uniformLocationCache.find(name);
	if (it != uniformLocationCache.end())
	{
		return it->second;
	}

	// Else query OpenGL to find the uniform location
	int location = glGetUniformLocation(programID, name.c_str());
	uniformLocationCache[name] = location;

	if (location == -1)
	{
		std::cerr << "Warning: Uniform '" << name << "' doesn't exist!" << std::endl;
	}

	return location;
}
