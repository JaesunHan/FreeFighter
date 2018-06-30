#pragma once
#include "stdafx.h"

inline float getDistance(D3DXVECTOR3 s, D3DXVECTOR3 d)
{
	//D3DXVECTOR3 distance = d - s;
	//float x = d.x - s.x;
	//float y = d.y - s.y;
	//float z = d.z - s.z;

	return D3DXVec3Length(&(d - s));
}

inline float getAngle(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float distance = sqrtf(x * x + y * y);

	if (distance == 0)
		return 0.0f;

	float angle = acosf(x / distance);

	if (y2 > y1)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}

	return angle;
}

// angleX == yz평면상의 각도, angleY == xz평면상의 각도, angleZ == xy평면상의 각도
inline void get3DAngle(float* angleX, float* angleY, float* angleZ, D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	float x = end.x - start.x;
	float y = end.y - start.y;
	float z = end.z - start.z;

	float distance;
	float angle;

	// xy평면
	distance = sqrtf(x * x + y * y);
	angle = acosf(x / distance) * RAD2DEG;
	if (end.y > start.y)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}

	*angleZ = angle;

	// xz평면
	distance = sqrtf(x * x + z * z);
	angle = acosf(x / distance);

	if (end.z > start.z)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}

	*angleY = angle;

	// yz평면
	distance = sqrtf(y * y + z * z);
	angle = acosf(y / distance);

	if (end.z > start.z)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}

	*angleX = angle;
}