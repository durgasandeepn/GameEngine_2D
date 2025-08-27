/****************************************************************
// File Name: Transform
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: A basic Transform class. Holds a position, rotation, and scale.
// Has utility methods such as getting and setting the above, as well as
// Getting the model matrix of the transform.
****************************************************************/

#pragma once
#include "Vector3.h"
#include "Matrix4.h"

class Transform
{
public:
    Transform();
	Transform(Vector3 pos, Vector3 rotation, Vector3 scale);

    // Position methods
    void SetPosition(const Vector3& newPosition);
    const Vector3& GetPosition() const { return position; };

    // Rotation methods (using Euler angles in radians)
    void SetRotation(const Vector3& newRotation);
    const Vector3& GetRotation() const { return rotation; };

    // Scale methods
    void SetScale(const Vector3& newScale);
    const Vector3& GetScale() const { return scale; }

    // Get the model matrix
    Matrix4 GetLocalMatrix();
    Matrix4 GetInverseLocalMatrix();

    // Get the forward, right, and up vectors of the transform
    Vector3 Forward();
    Vector3 Right();
    Vector3 Up();

    // Utility methods
    void Translate(const Vector3& translation);
    void Rotate(const Vector3& rotationDelta);
    void Scale(const Vector3& scaling);


private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};