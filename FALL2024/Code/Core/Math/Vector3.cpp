/****************************************************************
// File Name: Vector3
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: A primitive Vector3 class.
// Contains an x, y, and z float value to represent a point in 3D space.
****************************************************************/

#include "precompiled.h"
#include "Vector3.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    *this = *this + other;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    *this = *this - other;
    return *this;
}

Vector3 Vector3::operator*(float scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator*(const Vector3& other) const
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

float& Vector3::operator[](std::size_t index)
{
    switch (index) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("Index out of range. Valid indices are 0, 1, 2.");
    }
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

float Vector3::Dot(const Vector3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

float Vector3::Magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::MagnitudeSquared() const
{
    return Dot(*this);
}

Vector3 Vector3::Normalized() const
{
    Vector3 result;
    float mag = Magnitude();
    if (mag != 0)
    {
        result.x = x / mag;
        result.y = y / mag;
        result.z = z / mag;
    }
    return result;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
    Vector3 result;
    result.x = (y * other.z) - (z * other.y);
    result.y = (z * other.x) - (x * other.z);
    result.z = (x * other.y) - (y * other.x);
    return result;
}

Vector3 Vector3::Reciprocal() const
{
    return Vector3(
        x != 0.0f ? 1.0f / x : std::numeric_limits<float>::infinity(),
        y != 0.0f ? 1.0f / y : std::numeric_limits<float>::infinity(),
        z != 0.0f ? 1.0f / z : std::numeric_limits<float>::infinity()
    );
}

Vector3 Vector3::Lerp(const Vector3& end, float t) const
{
    t = std::clamp(t, 0.0f, 1.0f);
    return *this + (end - *this) * t;
}

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << std::fixed << std::setprecision(2) << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}