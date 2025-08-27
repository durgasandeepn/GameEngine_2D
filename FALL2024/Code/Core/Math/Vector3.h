/****************************************************************
// File Name: Vector3
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: A primitive Vector3 class.
// Contains an x, y, and z float value to represent a point in 3D space.
****************************************************************/

#pragma once

#include <cmath>
#include <array>
#include <stdexcept>

class Vector3 {
public:
    float x, y, z;

    // Default Constructor
    Vector3() : x(0), y(0), z(0) {}
    // Parameterized Constructor with Initialization List
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Operator overloads
    Vector3 operator+(const Vector3& other) const;
    Vector3& operator+=(const Vector3& other);
    Vector3 operator-(const Vector3& other) const;
    Vector3& operator-=(const Vector3& other);
    Vector3 operator*(float scalar) const;
    Vector3 operator*(const Vector3& other) const;
    float& operator[](std::size_t index);
    Vector3 operator-() const;

    // Main mathematical operations
    float Dot(const Vector3& other) const;
    float Magnitude() const;
    float MagnitudeSquared() const;
    Vector3 Normalized() const;
    Vector3 Cross(const Vector3& other) const;
    Vector3 Reciprocal() const;
    Vector3 Lerp(const Vector3& end, float t) const;

    // Printing
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};
