#include "precompiled.h"
#include "Matrix4.h"
#include <iostream>
#include <iomanip>

Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data[i][j] = 0.0f;
        }
    }
    data[0][0] = 1.0f;
    data[1][1] = 1.0f;
    data[2][2] = 1.0f;
    data[3][3] = 1.0f;
}

void Matrix4::UpdateElement(int row, int col, float value)
{
    if (row > 3 || row < 0 || col > 3 || row < 0)
    {
        throw std::invalid_argument("Matrix index is invalid.");
    }
    data[row][col] = value;
}

float Matrix4::GetElement(int row, int col) const
{
    if (row > 3 || row < 0 || col > 3 || row < 0)
    {
        throw std::invalid_argument("Matrix index is invalid.");
    }
    return data[row][col];
}

const float* Matrix4::GetData() const
{
    return &data[0][0];
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
    Matrix4 result;

    for (int i=0; i < 4; i++)
    {
        for (int j=0; j < 4; j++)
        {
            result.data[j][i] = 0;
            for (int k = 0; k < 4; k++)
            {
                result.data[j][i] += data[k][i] * other.data[j][k];
            }
        }
    }
	
    return result;
}

Vector3 Matrix4::operator*(const Vector3& vec) const
{
    float x, y, z, w;
    x = vec.x * data[0][0] + vec.y * data[1][0] + vec.z * data[2][0] + data[3][0];
    y = vec.x * data[0][1] + vec.y * data[1][1] + vec.z * data[2][1] + data[3][1];
    z = vec.x * data[0][2] + vec.y * data[1][2] + vec.z * data[2][2] + data[3][2];
    w = vec.x * data[0][3] + vec.y * data[1][3] + vec.z * data[2][3] + data[3][3];

    if (w != 0)
    {
        x /= w;
        y /= w;
        z /= w;
    }

    return Vector3(x, y, z);
}

Matrix4 Matrix4::Translation(float tx, float ty, float tz)
{
    Matrix4 result;
    result.data[3][0] = tx;
    result.data[3][1] = ty;
    result.data[3][2] = tz;
	
    return result;
}

Matrix4 Matrix4::Scale(float sx, float sy, float sz)
{
    Matrix4 result;
    result.data[0][0] = sx;
    result.data[1][1] = sy;
    result.data[2][2] = sz;

    return result;
}

Matrix4 Matrix4::RotationX(float angle_rad)
{
    Matrix4 result;
    result.data[1][1] =  cos(angle_rad);
    result.data[2][1] =  -sin(angle_rad);
    result.data[1][2] =  sin(angle_rad);
    result.data[2][2] =  cos(angle_rad);

    return result;
}

Matrix4 Matrix4::RotationY(float angle_rad)
{
    Matrix4 result;
    result.data[0][0] =  cos(angle_rad);
    result.data[2][0] =  sin(angle_rad);
    result.data[0][2] = -sin(angle_rad);
    result.data[2][2] =  cos(angle_rad);

    return result;
}

Matrix4 Matrix4::RotationZ(float angle_rad)
{
    Matrix4 result;
    result.data[0][0] = cos(angle_rad);
    result.data[1][0] = -sin(angle_rad);
    result.data[0][1] = sin(angle_rad);
    result.data[1][1] = cos(angle_rad);
	
    return result;
}

Matrix4 Matrix4::RotationXYZ(float angle_x, float angle_y, float angle_z)
{
    return RotationZ(angle_z) * RotationY(angle_y) * RotationX(angle_x);
}

Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
    Matrix4 result;
    result.data[0][0] = 2.0f / (right - left);
    result.data[1][1] = 2.0f / (top - bottom);
    result.data[2][2] = -2.0f / (far - near);

    result.data[3][0] = -(right + left) / (right - left);
    result.data[3][1] = -(top + bottom) / (top - bottom);
    result.data[3][2] = -(far + near) / (far - near);
    result.data[3][3] = 1.0f;
    return result;
}

Matrix4 Matrix4::Perspective(float fov, float aspectRatio, float near, float far)
{
    Matrix4 result;
    float tanHalfFov = std::tan(fov / 2.0f);
    result.data[0][0] = 1.0f / (aspectRatio * tanHalfFov);
    result.data[1][1] = 1.0f / tanHalfFov;
    result.data[2][2] = -(far + near) / (far - near);
    result.data[2][3] = -1.0f;
    result.data[3][2] = -(2.0f * far * near) / (far - near);
    result.data[3][3] = 0.0f;
    return result;
}

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
{
    Vector3 f = (center - eye).Normalized();
    Vector3 s = f.Cross(up.Normalized());
    Vector3 u = s.Cross(f);

    Matrix4 result;
    result.data[0][0] = s.x;
    result.data[0][1] = u.x;
    result.data[0][2] = -f.x;
    result.data[0][3] = 0.0f;

    result.data[1][0] = s.y;
    result.data[1][1] = u.y;
    result.data[1][2] = -f.y;
    result.data[1][3] = 0.0f;

    result.data[2][0] = s.z;
    result.data[2][1] = u.z;
    result.data[2][2] = -f.z;
    result.data[2][3] = 0.0f;

    result.data[3][0] = -s.Dot(eye);
    result.data[3][1] = -u.Dot(eye);
    result.data[3][2] = f.Dot(eye);
    result.data[3][3] = 1.0f;
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& m)
{
    std::cout << "Matrix4 Data:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << std::setw(8) << m.data[i][j] << " "; // Format for readability
        }
        std::cout << std::endl;
    }
    return os;
}
