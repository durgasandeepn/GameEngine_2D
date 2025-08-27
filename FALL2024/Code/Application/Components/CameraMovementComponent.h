/****************************************************************
// File Name: CameraMovementComponent
// Authors: Alex Humphries
// Description: Component for the camera, allows for movement of the camera
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/InputComponent.h"
#include "Object/Components/CameraComponent.h"

class CameraMovementComponent : public Component {
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

private:
	float cameraMoveSpeed;

	std::shared_ptr<InputComponent> inputComponent;
	std::shared_ptr<CameraComponent> cameraComponent;
};