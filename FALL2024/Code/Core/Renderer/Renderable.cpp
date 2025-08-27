/****************************************************************
// File Name: Renderable
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Renderable object specific for all non-debug objects.
// Works hand-in-hand with the RenderManager to render each object in the game
****************************************************************/


#include "precompiled.h"
#include "Renderable.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Object/Components/CameraComponent.h"
#include "Object/GameObject.h"

Renderable::Renderable(GameObject* owner)
	: owner(owner), isVisible(true) {}

void Renderable::Render()
{
    if (!isVisible || !mesh || !material || !camera || owner->GetShouldDelete())
        return;

    // Set properties in the material ProjectionMatrix * ViewMatrix * ModelMatrix 
    material->SetProperty("ModelMatrix", owner->GetTransformMatrix());
    material->SetProperty("ViewMatrix", camera->GetViewMatrix());
    material->SetProperty("ProjectionMatrix", camera->GetProjectionMatrix());
    material->SetProperty("Opacity", opacity);
    material->SetProperty("special_color", special_color);
    // Apply the material (this will set uniforms and bind textures)
    material->Apply();

    // Bind the mesh's geometry buffer
    std::shared_ptr<GeometryBuffer> geomBuffer = mesh->GetGeometryBuffer();
    if (!geomBuffer) return;
    geomBuffer->Bind();

    // Draw the mesh
    if (mesh->HasAttribute(GeometryBuffer::Attribute::Position))
    {
        if (geomBuffer->GetIndexCount() > 0)
        {
            renderer->Draw(geomBuffer->GetIndexCount(), GL_TRIANGLES, true);
        }
        else
        {
            renderer->Draw(geomBuffer->GetVertexCount(), GL_TRIANGLES, false);
        }
    }

    // Unbind geometry buffer
    geomBuffer->Unbind();
}
