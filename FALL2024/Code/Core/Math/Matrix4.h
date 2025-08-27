/****************************************************************
// File Name: Matrix4
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors,
// Ju-ve Chankasemporn - key bug fixes
// Description: A primitive Matrix class of static size 4.
// handles transformation / viewport logic as well.
****************************************************************/

#pragma once

#include <cmath>
#include <array>
#include <stdexcept>

#include "Vector3.h"

class Matrix4 {
private:
    float data[4][4];

public:
    Matrix4();

    // Multiplication: * Operator Overloads
    Matrix4 operator*(const Matrix4& other);
    Vector3 operator*(const Vector3& vec) const;

    // Matrix-specific functions
    void UpdateElement(int row, int col, float value);
    float GetElement(int row, int col) const;
    const float* GetData() const;

    // Transformation utilities based on matrix
    static Matrix4 Translation(float tx, float ty, float tz);
    static Matrix4 Scale(float sx, float sy, float sz);
    static Matrix4 RotationX(float angle_rad);
    static Matrix4 RotationY(float angle_rad);
    static Matrix4 RotationZ(float angle_rad);
    static Matrix4 RotationXYZ(float angle_x, float angle_y, float angle_z);
    static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
    /*
    * Used to create a perspective matrix
    * :param: fov - sets the Field of View for the matrix (how large the view space is).
                   45 degrees is normal, but can be tweaked. Units are radians
      :param: aspectRatio - Calculated by dividing the viewport width by height.
      :param: near - sets the near distance of the plane
      :param: far - sets the far distance of the plane
    */
    static Matrix4 Perspective(float fov, float aspectRatio, float near, float far);
    static Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

   friend std::ostream& operator<<(std::ostream& os, const Matrix4& m);
};