/****************************************************************
// File Name: GeometryBuffer
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Geometry Buffer for OpenGL, handles VAO, VBO,
// EBO, vertices, indices, etc. for the Renderer
****************************************************************/

#include "precompiled.h"
#include "GeometryBuffer.h"
#include <stdexcept>

GeometryBuffer::GeometryBuffer() :
    VAO(0), VBO(0), EBO(0), vertexCount(0), indexCount(0)
{
}

GeometryBuffer::~GeometryBuffer()
{
    CleanupBuffers();
}

std::shared_ptr<GeometryBuffer> GeometryBuffer::Create(const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attributeData, const std::vector<unsigned int>& indices, const std::string& name)
{
    auto buffer = std::shared_ptr<GeometryBuffer>(new GeometryBuffer());
    buffer->InitializeBuffers(attributeData, indices);
    return buffer;
}

void GeometryBuffer::Bind()
{
    glBindVertexArray(VAO);
}

void GeometryBuffer::Unbind()
{
    glBindVertexArray(0);
}

bool GeometryBuffer::HasAttribute(Attribute attr) const
{
    return attributeOffsets.find(attr) != attributeOffsets.end();
}

void GeometryBuffer::InitializeBuffers(const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attributeData, const std::vector<unsigned int>& indices)
{
    // 0. Pre-requisite: 
    // Since we don't know how many attributes, we have to calculate 
    // the total buffer size and attribute offsets
    GLsizeiptr totalSize = 0;
    for (const auto& [attr, data] : attributeData)
    {
        attributeOffsets[attr] = unsigned int(totalSize);
        totalSize += data.first.size() * sizeof(float);
        attributeInfos[attr] = data.second;
    }
    // We also initialize the vertex count from attributeData and index count from indices vector size
    auto it = attributeData.begin();
    vertexCount = GLsizei(it->second.first.size() / it->second.second.size);
    indexCount = GLsizei(indices.size());

    // 1. Create the buffer and get the pointers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 2. Bind the VAO. All setup below will be stored in the VAO
    glBindVertexArray(VAO);

    // 4. Allocate the VBO. All setup below will be store in this VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);

    // 5. Filling out the VBO. Each attribute at a time
    GLuint attrLocation = 0;
    for (const auto& [attr, data] : attributeData)
    {
        const auto& [attrData, attrInfo] = data;
        // subdata because we have sections of data (for positions, colors, etc)
        glBufferSubData(GL_ARRAY_BUFFER, attributeOffsets[attr],
            attrData.size() * sizeof(float), attrData.data());
        glVertexAttribPointer(attrLocation, attrInfo.size, attrInfo.type,
            attrInfo.normalized, attrInfo.stride, (void*)attributeOffsets[attr]); // NOTE: This cast to void* is extremely suspicious
        glEnableVertexAttribArray(attrLocation);
        attrLocation++;
    }

    // 6. Setup EBO (index or element buffer)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // 7. UnBind everything
    glBindVertexArray(0);
}

void GeometryBuffer::CleanupBuffers()
{
    if (VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO != 0)
    {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
}