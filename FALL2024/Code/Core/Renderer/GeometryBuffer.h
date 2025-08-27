/****************************************************************
// File Name: GeometryBuffer
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Geometry Buffer for OpenGL, handles VAO, VBO,
// EBO, vertices, indices, etc. for the Renderer
****************************************************************/
#pragma once
#include <vector>
#include <glew.h>
#include <unordered_map>
#include <memory>
#include <string>

class GeometryBuffer
{
public:
	enum class Attribute
	{
		Position,
		Normal,
		TexCoord,
		Color,
		Tangent,
		Bitangent
	};

	struct AttributeInfo
	{
		GLint       size;
		GLenum      type;
		GLboolean   normalized;
		GLsizei     stride;
	};

	static std::shared_ptr<GeometryBuffer> Create
	(
		const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attributeData,
		const std::vector<unsigned int>& indices,
		const std::string& name
	);

	~GeometryBuffer();

	// Prevent copying
	GeometryBuffer(const GeometryBuffer&) = delete;
	GeometryBuffer& operator=(const GeometryBuffer&) = delete;

	void Bind();
	void Unbind();

	/* Getters */
	GLsizei GetVertexCount() const { return vertexCount; }
	GLsizei GetIndexCount() const { return indexCount; }
	GLuint  GetVAO() const { return VAO; }
	GLuint  GetVBO() const { return VBO; }
	GLuint  getEBO() const { return EBO; }

	bool    HasAttribute(Attribute attr) const;

private:
	GLuint VAO, VBO, EBO;
	GLsizei vertexCount;
	GLsizei indexCount;
	std::unordered_map<Attribute, GLuint> attributeOffsets; // To track when each attribute starts
	std::unordered_map<Attribute, AttributeInfo> attributeInfos;

	GeometryBuffer();

	void InitializeBuffers(
		const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attributeData,
		const std::vector<unsigned int>& indices
		);
	void CleanupBuffers();

};