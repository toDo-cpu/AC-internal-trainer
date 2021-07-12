#pragma once

#include <Windows.h>
#include <math.h>

struct Vector3 { float x, y, z; };

Vector3 Vec3Substract(Vector3* a, Vector3* b);
Vector3 Vec3Substract(Vector3 a, Vector3 b);
Vector3 Vec3Summ(Vector3* a, Vector3* b);
Vector3 Vec3Summ(Vector3 a, Vector3 b);
Vector3 Vec3CalcAngle(Vector3* src, Vector3* dst);

float Vec3CalcDistance(Vector3* src, Vector3* dst);
float Vec3Magnitude(Vector3 vector);