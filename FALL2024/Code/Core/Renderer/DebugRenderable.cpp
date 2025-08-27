/****************************************************************
// File Name: DebugRenderable
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Renderable object specific to Debugging
****************************************************************/

#include "precompiled.h"
#include "DebugRenderable.h"
#include "Object/GameObject.h"
#include "ResourceManagement/ResourceManager.h"
#include "Physics/AABB.h"
#include "Physics/OBB.h"
#include "Physics/Circle.h"

DebugRenderable::DebugRenderable(GameObject* owner)
{
}

void DebugRenderable::Render()
{
    if (physicsComponent == nullptr)
    {
        physicsComponent = owner->FindComponent<PhysicsComponent>();
        if (physicsComponent) InitializeDebugDraw();
    }
    else
    {
        DrawDebugLines();
    }
}

void DebugRenderable::InitializeDebugDraw()
{
    this->renderer = renderer;
    debugMesh = std::make_shared<Mesh>("OBB_Debug_Mesh");

    if (debugMesh == nullptr)
    {
        std::cout << "------------fail debugMesh------------" << std::endl;
    }

    // Define vertices in normalized coordinates
    std::vector<float> vertices = {
        // Box corners in normalized coordinates (-0.5 to 0.5)
        -0.5f, -0.5f, 0.0f,     // Bottom-left
         0.5f, -0.5f, 0.0f,  // Bottom-right
         0.5f,  0.5f, 0.0f,     // Top-right
        -0.5f,  0.5f, 0.0f,     // Top-left
        // Center point
        0.0f,  0.0f, 0.0f,
        // Right axis endpoint (unit vector)
        1.0f,  0.0f, 0.0f,
        // Up axis endpoint (unit vector)
        0.0f,  1.0f, 0.0f,
    };

    std::vector<float> texCoords = {
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f
    };

    std::vector<unsigned int> indices = {
        0, 1,  // Bottom edge
        1, 2,  // Right edge
        2, 3,  // Top edge
        3, 0,  // Left edge
        4, 5,  // Right vector
        4, 6   // Up vector
    };

    debugMesh->SetVertexData({
        {GeometryBuffer::Attribute::Position, vertices, 3},
        {GeometryBuffer::Attribute::TexCoord, texCoords, 2}
        }, indices);

    // Create and setup material
    auto shader = ResourceManager::Instance().LoadShader("vertex_shader.glsl\nfragment_shader.glsl");
    debugMaterial = std::make_shared<Material>(shader);
    debugMaterial->SetProperty("useTexture", 0);
    debugMaterial->SetProperty("isTransparent", 0);

    if (debugMaterial != nullptr)
    {
        std::cout << "init debugMaterial" << std::endl;
    }
}

void DebugRenderable::DrawDebugLines()
{
    if (!debugMesh || !debugMaterial) return;

    // Create model matrix that will transform our normalized box to the OBB's position and orientation

    if (physicsComponent == nullptr)
    {
        return;
    }

    Shape* shape = physicsComponent->GetBody()->GetShape();
    if (!shape) return;

    switch (shape->GetType()) {
    case Shape::Type::OBB:
    {
        OBB* obb = static_cast<OBB*>(shape);
        DrawOBB(obb);
        break;
    }

    case Shape::Type::AABB:
    {
        AABB* aabb = static_cast<AABB*>(shape);
        DrawAABB(aabb);
        break;
    }

    case Shape::Type::CIRCLE:
    {
        Circle* circle = static_cast<Circle*>(shape);
        DrawCircle(circle);
        break;
    }
    }

    Vector3 velocity = physicsComponent->GetBody()->GetVelocity();
    DrawVelocity(velocity);
}

void DebugRenderable::DrawOBB(const OBB* obb) const
{
    Matrix4 scale = Matrix4::Scale(obb->GetHalfExtents().x * 2, obb->GetHalfExtents().y * 2, 1.0f);
    Matrix4 rotation = Matrix4::RotationZ(std::atan2(obb->GetRight().y, obb->GetRight().x));
    Matrix4 translation = Matrix4::Translation(obb->GetCenter().x, obb->GetCenter().y, obb->GetCenter().z);
    Matrix4 model = translation * rotation * scale;

    // Draw box outline in green
    debugMaterial->SetProperty("Color", Vector3(0.0f, 1.0f, 0.0f));
    debugMaterial->SetProperty("ModelMatrix", model);
    debugMaterial->SetProperty("ViewMatrix", camera->GetViewMatrix());
    debugMaterial->SetProperty("ProjectionMatrix", camera->GetProjectionMatrix());

    debugMaterial->Apply();
    auto geomBuffer = debugMesh->GetGeometryBuffer();
    if (geomBuffer) {
        geomBuffer->Bind();

        // Draw box outline
        glLineWidth(5.0f);
        renderer->Draw(8, GL_LINES, true);  // First 8 indices for box

        //// Draw direction vectors
        //// For these, we use a different scale matrix that keeps them unit length
        //Matrix4 vectorScale = Matrix4::Scale(obb->GetHalfExtents().x, obb->GetHalfExtents().y, 1.0f);
        //Matrix4 vectorModel = model;// translation* rotation* vectorScale;

        //// Draw right vector in red
        //debugMaterial->SetProperty("Color", Vector3(1.0f, 0.0f, 0.0f));
        //debugMaterial->SetProperty("ModelMatrix", vectorModel);
        //debugMaterial->Apply();
        //glLineWidth(2.0f);
        //glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(8 * sizeof(unsigned int)));

        //// Draw up vector in blue
        //debugMaterial->SetProperty("Color", Vector3(0.0f, 0.0f, 1.0f));
        //debugMaterial->Apply();
        //glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));

        glLineWidth(1.0f);
        geomBuffer->Unbind();
    }
}

void DebugRenderable::DrawAABB(const AABB* aabb) const
{
    Vector3 min = aabb->GetMin();
    Vector3 max = aabb->GetMax();

    Matrix4 scale = Matrix4::Scale(max.x - min.x, max.y - min.y, 1.0f);
    Matrix4 translation = Matrix4::Translation((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f, 0.0f);
    Matrix4 model = translation * scale;

    debugMaterial->SetProperty("Color", Vector3(1.0f, 1.0f, 0.0f));  // Yellow for AABB
    debugMaterial->SetProperty("ModelMatrix", model);
    debugMaterial->SetProperty("ViewMatrix", camera->GetViewMatrix());
    debugMaterial->SetProperty("ProjectionMatrix", camera->GetProjectionMatrix());

    debugMaterial->Apply();
    auto geomBuffer = debugMesh->GetGeometryBuffer();
    if (geomBuffer) {
        geomBuffer->Bind();
        glLineWidth(5.0f);
        renderer->Draw(8, GL_LINES, true);
        glLineWidth(1.0f);
        geomBuffer->Unbind();
    }
}

void DebugRenderable::DrawCircle(const Circle* circle) const
{
    const int vertexCount = 36;
    std::vector<Vector3> circleVertices(vertexCount);

    // Generate vertices for the circle outline
    for (int i = 0; i < vertexCount; ++i)
    {
        float angle = (float(i) / vertexCount) * 2.0f * 3.14f;
        circleVertices[i] = Vector3(std::cos(angle), std::sin(angle), 0.0f) * circle->GetRadius();
    }

    Matrix4 translation = Matrix4::Translation(circle->GetCenter().x, circle->GetCenter().y, 0.0f);
    Matrix4 model = translation;

    debugMaterial->SetProperty("Color", Vector3(0.0f, 0.0f, 1.0f));  // Blue for Circle
    debugMaterial->SetProperty("ModelMatrix", model);
    debugMaterial->SetProperty("ViewMatrix", camera->GetViewMatrix());
    debugMaterial->SetProperty("ProjectionMatrix", camera->GetProjectionMatrix());
    debugMaterial->Apply();

    // Draw the circle using GL_LINE_LOOP
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (const Vector3& vertex : circleVertices)
    {
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();
    glLineWidth(1.0f);
}

void DebugRenderable::DrawVelocity(const Vector3 velocity) const
{
    Vector3 start = owner->GetLocalPosition();
    Vector3 end = start + velocity * 0.1f;  // Scale down for visualization
    Matrix4 identity;
    debugMaterial->SetProperty("Color", Vector3(1.0f, 0.0f, 1.0f));
    debugMaterial->SetProperty("ModelMatrix", identity);
    debugMaterial->SetProperty("ViewMatrix", camera->GetViewMatrix());
    debugMaterial->SetProperty("ProjectionMatrix", camera->GetProjectionMatrix());
    debugMaterial->Apply();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
    glLineWidth(1.0f);
}
