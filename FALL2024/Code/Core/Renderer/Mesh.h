/****************************************************************
// File Name: Mesh
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Describes the content of a mesh, a collection of vertices, edges and faces
// that make up an entity in 3D.
****************************************************************/

#pragma once

#include "GeometryBuffer.h"
#include <vector>
#include <unordered_map>
#include <string>

struct VertexData
{
	GeometryBuffer::Attribute attribute;
	std::vector<float> data;
	int componentsPerVertex;
};
/* Gives a 3D object a set of points in space to be drawn.
   the "3D" part of a 3D object
*/
class Mesh
{
public:
	Mesh(const std::string& name);
	~Mesh() = default;

	std::shared_ptr<GeometryBuffer> GetGeometryBuffer() const;
	//std::string GetType() const;
	//std::unique_ptr<Mesh> Clone() const;

	
	/* Set Mesh Data */
	void SetVertexData(
		const std::vector<VertexData>& vertexData,
		const std::vector<unsigned int>& indices);

	/*void SetAttributeData(
		GeometryBuffer::Attribute attr,
		const std::vector<float>& data,
		int componentsPerVertex);
	void SetIndices(const std::vector<unsigned int>& newIndices);*/

	/* Get Mesh data*/
	size_t GetVertexCount() const;
	size_t GetIndexCount() const;
	const std::string& GetName() const { return name; };
	bool HasAttribute(GeometryBuffer::Attribute attr) const;
	
private:
	void PrepareAttributeData(std::unordered_map<GeometryBuffer::Attribute, std::pair<std::vector<float>, GeometryBuffer::AttributeInfo>>& attributeMap,
		const std::vector<VertexData>& vertexData);
	std::shared_ptr<GeometryBuffer> geometryBuffer;
	std::string name;
	std::vector<unsigned int> indices;
};