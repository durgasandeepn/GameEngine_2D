/****************************************************************
// File Name: Transform
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: A basic Transform class. Holds a position, rotation, and scale.
// Has utility methods such as getting and setting the above, as well as
// Getting the model matrix of the transform.
****************************************************************/

#include "precompiled.h"
#include "Transform.h"
#include <iostream>

Transform::Transform(): position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1){}

Transform::Transform(Vector3 pos, Vector3 rotation, Vector3 scale) : position(pos), rotation(rotation), scale(scale) {}

void Transform::SetPosition(const Vector3& newPosition)
{
	position = newPosition;
}

void Transform::SetRotation(const Vector3& newRotation)
{
	rotation = newRotation;
}

void Transform::SetScale(const Vector3& newScale)
{
	scale = newScale;
}

Matrix4 Transform::GetLocalMatrix()
{
	Matrix4 translationMatrix = Matrix4::Translation(position.x, position.y, position.z);
	Matrix4 rotationMatrix = Matrix4::RotationXYZ(rotation.x, rotation.y, rotation.z);
	Matrix4 scaleMatrix = Matrix4::Scale(scale.x, scale.y, scale.z);
	return translationMatrix * rotationMatrix * scaleMatrix;
}

Matrix4 Transform::GetInverseLocalMatrix()
{
	// Invert scale
	Vector3 invScale(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);

	// Invert rotation (negative angles)
	Vector3 invRotation(-rotation.x, -rotation.y, -rotation.z);

	// Invert translation
	Vector3 invTranslation(-position.x, -position.y, -position.z);

	// Combine in reverse order
	Matrix4 invScaleMatrix = Matrix4::Scale(invScale.x, invScale.y, invScale.z);
	Matrix4 invRotationMatrix = Matrix4::RotationXYZ(invRotation.x, invRotation.y, invRotation.z);
	Matrix4 invTranslationMatrix = Matrix4::Translation(invTranslation.x, invTranslation.y, invTranslation.z);

	return invScaleMatrix * invRotationMatrix * invTranslationMatrix;
}

Vector3 Transform::Forward()
{
	float pitchRadians = rotation.x * 3.14159f / 180.0f;
	float yawRadians = rotation.y * 3.14159f / 180.0f;
	return Vector3(
		sin(yawRadians) * cos(pitchRadians),
		sin(pitchRadians), 
		-cos(yawRadians) * cos(pitchRadians)
	).Normalized();
}

Vector3 Transform::Right()
{
	// Cross with UpVector
	return Forward().Cross(Up()).Normalized();
}

Vector3 Transform::Up()
{

	return Vector3(0.0f, 1.0f, 0.0f);
}

void Transform::Translate(const Vector3& translation)
{
	position = position + translation;
}

void Transform::Rotate(const Vector3& rotationDelta)
{
	rotation = rotation + rotationDelta;
}

void Transform::Scale(const Vector3& scaling)
{
	scale.x *= scaling.x;
	scale.y *= scaling.y;
	scale.z *= scaling.z;
}
