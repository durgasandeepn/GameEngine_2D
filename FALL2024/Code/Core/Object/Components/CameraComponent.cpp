/****************************************************************
// File Name: CameraComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component that creates a viewport to be used by the renderer.
// Can only have one in a level.
****************************************************************/

#include "precompiled.h"
#include "CameraComponent.h"
#include "Object/GameObject.h"
#include "Event/Events/ObjectCreatedEvent.h"
#include "Object/Components/RenderComponent2D.h"
#include "Object/Components/DebugRenderComponent.h"
#include "Object/Components/UIComponent.h"

CameraComponent::CameraComponent() : aspectRatio(0.0f), isOrthographic(true),
nearPlane(0.1f), farPlane(1000.0f), size(0.0f)
{
    // When a different object is created, set this object as it's camera
    eventID = EventManager::Instance().AddListener<ObjectCreatedEvent>(
        [this](const ObjectCreatedEvent& event) {
            if (!event.objectToCreate) return;
            if (event.objectToCreate->FindComponent<RenderComponent2D>()) {
                event.objectToCreate->FindComponent<RenderComponent2D>()->GetRenderable()->SetCamera(this);
            }
            if (event.objectToCreate->FindComponent<DebugRenderComponent>()) {
                event.objectToCreate->FindComponent<DebugRenderComponent>()->GetRenderable()->SetCamera(this);
            }
            if (event.objectToCreate->FindComponent<UIComponent>()) {
                event.objectToCreate->FindComponent<UIComponent>()->GetRenderable()->SetCamera(this);
            }
        }
    );
}

void CameraComponent::Initialize()
{
    std::cout << "Camera initialize" << std::endl;
}

void CameraComponent::Update(float deltaTime)
{
	Vector3 cameraTarget = owner->GetLocalPosition() + viewTarget;
	viewMatrix = Matrix4::LookAt(owner->GetLocalPosition(), cameraTarget, upVector);

	// Orthographic
	if (isOrthographic) {
        float halfHeight = (baseHeight * size);

        // Use the actual window's aspect ratio for the horizontal span
        float aspectRatio = static_cast<float>(pWindow->GetWidth()) / pWindow->GetHeight();
        float halfWidth = halfHeight * aspectRatio;

        // Define orthographic bounds
        float left = -halfWidth;
        float right = halfWidth;
        float bottom = -halfHeight;
        float top = halfHeight;
		projectionMatrix = Matrix4::Orthographic(left, right, bottom, top, nearPlane, farPlane);
	}
	// Perspective
	else {
		projectionMatrix = Matrix4::Perspective(45.0f * 3.14159f / 180.0f, aspectRatio, nearPlane, farPlane);
	}
}

void CameraComponent::Shutdown()
{
    EventManager::Instance().RemoveListener<ObjectCreatedEvent>(eventID);
}

void CameraComponent::Serialize()
{
}

void CameraComponent::Deserialize(const rapidjson::Value& json)
{
    try {
        // Validate the JSON structure
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for CameraComponent: Expected an object.");
        }

        if (json.HasMember("isOrthographic") && json["isOrthographic"].IsBool()) {
            isOrthographic = json["isOrthographic"].GetBool();
        }
        else {
            throw std::invalid_argument("CameraComponent: Missing or invalid 'isOrthographic' property.");
        }

        if (json.HasMember("nearPlane") && json["nearPlane"].IsFloat()) {
            nearPlane = json["nearPlane"].GetFloat();
        }
        else {
            throw std::invalid_argument("CameraComponent: Missing or invalid 'nearPlane' property.");
        }

        if (json.HasMember("farPlane") && json["farPlane"].IsFloat()) {
            farPlane = json["farPlane"].GetFloat();
        }
        else {
            throw std::invalid_argument("CameraComponent: Missing or invalid 'nearPlane' property.");
        }

        if (json.HasMember("size") && json["size"].IsFloat()) {
            size = json["size"].GetFloat();
        }
        else {
            throw std::invalid_argument("CameraComponent: Missing or invalid 'size' property.");
        }

        if (json.HasMember("upVector") && json["upVector"].IsObject()) {
            const auto& up = json["upVector"];
            if (up.HasMember("x") && up["x"].IsNumber() &&
                up.HasMember("y") && up["y"].IsNumber() &&
                up.HasMember("z") && up["z"].IsNumber()) {
                upVector = Vector3(
                    up["x"].GetFloat(),
                    up["y"].GetFloat(),
                    up["z"].GetFloat()
                );
            }
            else {
                throw std::invalid_argument("CameraComponent::Deserialize - Invalid 'upVector'");
            }
        }

        if (json.HasMember("viewTarget") && json["viewTarget"].IsObject()) {
            const auto& view = json["viewTarget"];
            if (view.HasMember("x") && view["x"].IsNumber() &&
                view.HasMember("y") && view["y"].IsNumber() &&
                view.HasMember("z") && view["z"].IsNumber()) {
                viewTarget = Vector3(
                    view["x"].GetFloat(),
                    view["y"].GetFloat(),
                    view["z"].GetFloat()
                );
            }
            else {
                throw std::invalid_argument("CameraComponent::Deserialize - Invalid 'viewTarget'");
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing CameraComponent: " << e.what() << std::endl;
        throw; // Re-throw the exception after logging
    }
}

void CameraComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void CameraComponent::SetWindow(GameWindow* window)
{
    pWindow = window;
    aspectRatio = static_cast<float>(pWindow->GetWidth()) / pWindow->GetHeight();
}
