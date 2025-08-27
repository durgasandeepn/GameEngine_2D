/****************************************************************
// File Name: Mesh
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Describes the content of a mesh, a collection of vertices, edges and faces
// that make up an entity in 3D.
****************************************************************/

#include "precompiled.h"
#include "Mesh.h"

Mesh::Mesh(const std::string& name) : name(name) {}

std::shared_ptr<GeometryBuffer> Mesh::GetGeometryBuffer() const
{
	return geometryBuffer;
}

void Mesh::SetVertexData(const std::vector<VertexData>& vertexData, const std::vector<unsigned int>& indices)
{
	std::unordered_map<GeometryBuffer::Attribute, std::pair<std::vector<float>, GeometryBuffer::AttributeInfo>> attributeMap;
	PrepareAttributeData(attributeMap, vertexData);
	geometryBuffer = GeometryBuffer::Create(attributeMap, indices, name);
	this->indices = indices;
}

size_t Mesh::GetVertexCount() const
{
	return geometryBuffer ? geometryBuffer->GetVertexCount() : 0;
}

size_t Mesh::GetIndexCount() const
{
	return geometryBuffer ? geometryBuffer->GetIndexCount() : 0;
}

bool Mesh::HasAttribute(GeometryBuffer::Attribute attr) const
{
	return geometryBuffer && geometryBuffer->HasAttribute(attr);
}

void Mesh::PrepareAttributeData(std::unordered_map<GeometryBuffer::Attribute, std::pair<std::vector<float>, GeometryBuffer::AttributeInfo>>& attributeMap, const std::vector<VertexData>& vertexData)
{
	for (const auto& vda : vertexData)
	{
		attributeMap[vda.attribute] = {
			vda.data,
			{vda.componentsPerVertex, GL_FLOAT, GL_FALSE, 0}
		};
	}
}
