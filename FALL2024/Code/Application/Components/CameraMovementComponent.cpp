/****************************************************************
// File Name: CameraMovementComponent
// Authors: Alex Humphries
// Description: Component for the camera, allows for movement of the camera
****************************************************************/

#include "precompiled.h"
#include "CameraMovementComponent.h"
#include "Object/GameObject.h"

void CameraMovementComponent::Initialize()
{
	inputComponent = owner->FindComponent<InputComponent>();
	cameraComponent = owner->FindComponent<CameraComponent>();
}

void CameraMovementComponent::Update(float deltaTime)
{
	Vector3 currentPosition = owner->GetLocalPosition();
	if (inputComponent->IsActionHeld("Right")) {
		currentPosition.x += cameraMoveSpeed * deltaTime;
	}
	if (inputComponent->IsActionHeld("Left")) {
		currentPosition.x -= cameraMoveSpeed * deltaTime;
	}
	if (inputComponent->IsActionHeld("Up")) {
		currentPosition.y += cameraMoveSpeed * deltaTime;
	}
	if (inputComponent->IsActionHeld("Down")) {
		currentPosition.y -= cameraMoveSpeed * deltaTime;
	}

	owner->SetLocalPosition(currentPosition);
}

void CameraMovementComponent::Shutdown()
{
}

void CameraMovementComponent::Serialize()
{
}

void CameraMovementComponent::Deserialize(const rapidjson::Value& json)
{
	try {
		// Validate the JSON structure
		if (!json.IsObject()) {
			throw std::invalid_argument("Invalid JSON for CameraMovementComponent: Expected an object.");
		}

		if (json.HasMember("moveSpeed") && json["moveSpeed"].IsFloat()) {
			cameraMoveSpeed = json["moveSpeed"].GetFloat();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing CameraMovementComponent: " << e.what() << std::endl;
		throw; // Re-throw the exception after logging
	}
}

void CameraMovementComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}
