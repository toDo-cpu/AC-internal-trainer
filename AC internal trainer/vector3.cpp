#pragma once
#include "pch.h"
#include "vector3.h"
#include <math.h>
#include <Windows.h>
#include <iostream>

#define PI 3.1415926535897

#define DEBUG

Vector3 Vec3Substract(Vector3* a, Vector3* b)
{
	Vector3 sub;
	ZeroMemory(&sub, sizeof(sub));

	sub.x = a->x - b->x;
	sub.y = a->y - b->y;
	sub.z = a->z - b->z;

#ifdef DEBUG

	std::cout << "Vec3sub : " << std::endl;
	std::cout << "		- x : " << sub.x << std::endl;
	std::cout << "		- y : " << sub.y << std::endl;
	std::cout << "		- z : " << sub.z << std::endl;

#endif

	return sub;
}
Vector3 Vec3Substract(Vector3 a, Vector3 b)
{
	Vector3 sub;
	ZeroMemory(&sub, sizeof(sub));

	sub.x = a.x - b.x;
	sub.y = a.y - b.y;
	sub.z = a.z - b.z;

#ifdef DEBUG

	std::cout << "Vec3sub : " << std::endl;
	std::cout << "		- x : " << sub.x << std::endl;
	std::cout << "		- y : " << sub.y << std::endl;
	std::cout << "		- z : " << sub.z << std::endl;

#endif

	return sub;
}

Vector3 Vec3Summ(Vector3* a, Vector3* b)
{
	Vector3 sub;
	ZeroMemory(&sub, sizeof(sub));

	sub.x = a->x + b->x;
	sub.y = a->y + b->y;
	sub.z = a->z + b->z;

#ifdef DEBUG

	std::cout << "Vec3summ : " << std::endl;
	std::cout << "		- x : " << sub.x << std::endl;
	std::cout << "		- y : " << sub.y << std::endl;
	std::cout << "		- z : " << sub.z << std::endl;

#endif 

	return sub;
}

Vector3 Vec3Summ(Vector3 a, Vector3 b)
{
	Vector3 sub;
	ZeroMemory(&sub, sizeof(sub));

	sub.x = a.x + b.x;
	sub.y = a.y + b.y;
	sub.z = a.z + b.z;

#ifdef DEBUG

	std::cout << "Vec3summ : " << std::endl;
	std::cout << "		- x : " << sub.x << std::endl;
	std::cout << "		- y : " << sub.y << std::endl;
	std::cout << "		- z : " << sub.z << std::endl;

#endif 

	return sub;
}
Vector3 Vec3CalcAngle(Vector3* src, Vector3* dst)
{
	Vector3 angle;
	angle.x = -atan2f(dst->x - src->x, dst->y - src->y) / PI * 180.0f + 180.0f;
	angle.y = asinf((float)(dst->z - src->z) / (float)Vec3CalcDistance(src, dst)) * 180.0f / PI;
	angle.z = 0.0f;

#ifdef DEBUG

	std::cout << "Vec3CalcAngle : " << std::endl;
	std::cout << "		- x : " << angle.x << std::endl;
	std::cout << "		- y : " << angle.y << std::endl;
	std::cout << "		- z : " << angle.z << std::endl;

#endif 

	return angle;
}

/*Vector3 Vec3CalcAngle(Vector3 src, Vector3 dst)
{
	Vector3 angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / PI * 180.0f + 180.0f;
	angle.y = asinf((dst.z - src.z) / Vec3CalcDistance(src, dst)) * 180.0f / PI;
	angle.z = 0.0f;

#ifdef DEBUG

	std::cout << "Vec3CalcAngle : " << std::endl;
	std::cout << "		- x : " << angle.x << std::endl;
	std::cout << "		- y : " << angle.y << std::endl;
	std::cout << "		- z : " << angle.z << std::endl;

#endif

	return angle;
}*/

float Vec3CalcDistance(Vector3* src, Vector3* dst)
{
	float distance = Vec3Magnitude(Vec3Substract(dst, src));
#ifdef DEBUG

	std::cout << "Vec3CalcDistance : " << std::endl;
	std::cout << "		 float :  " << distance << std::endl;

#endif
	return distance;
}
float Vec3CalcDistance(Vector3 src, Vector3 dst)
{
	float distance = Vec3Magnitude(Vec3Substract(dst, src));
#ifdef DEBUG

	std::cout << "Vec3CalcDistance : " << std::endl;
	std::cout << "		 float :  " << distance << std::endl;

#endif 

	return distance;
}

float Vec3Magnitude(Vector3 vector)
{
#ifdef DEBUG

	std::cout << "Vec3Magnitude :" << std::endl;
	std::cout << "	-	x = " << vector.x * vector.x << std::endl;
	std::cout << "	-	y = " << vector.y * vector.y << std::endl;
	std::cout << "	-	z = " << vector.z * vector.z << std::endl;

#endif 

	return sqrtf((vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}
float Vec3Magnitude(Vector3* vector)
{
#ifdef DEBUG

	std::cout << "Vec3Magnitude :" << std::endl;
	std::cout << "	-	x = " << vector->x * vector->x << std::endl;
	std::cout << "	-	y = " << vector->y * vector->y << std::endl;
	std::cout << "	-	z = " << vector->z * vector->z << std::endl;

#endif 

	return sqrtf((vector->x * vector->x + vector->y * vector->y + vector->z * vector->z));
}