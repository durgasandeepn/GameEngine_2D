/****************************************************************
// File Name: CameraComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component that creates a viewport to be used by the renderer.
// Can only have one in a level.
****************************************************************/

#pragma once
#include "Component.h"
class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent() = default;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json) override;
	void Configure(const std::unordered_map<std::string, std::any>& properties) override;

	void SetWindow(GameWindow* window);

	Matrix4 GetViewMatrix() const { return viewMatrix; };
	Matrix4 GetProjectionMatrix() const { return projectionMatrix; };
private:
	GameWindow* pWindow{nullptr};
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;

	Vector3 viewTarget;
	Vector3 upVector;
	float aspectRatio;
	float nearPlane;
	float farPlane;
	float size;

	bool isOrthographic;

	float baseWidth = 1920.0f;
	float baseHeight = 1080.0f;

	uint32_t eventID;
};