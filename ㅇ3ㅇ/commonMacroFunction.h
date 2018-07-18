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

// angleX == yz������ ����, angleY == xz������ ����, angleZ == xy������ ����
inline void get3DAngle(float* angleX, float* angleY, float* angleZ, D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	float x = end.x - start.x;
	float y = end.y - start.y;
	float z = end.z - start.z;

	float distance;
	float angle;

	// xy���
	distance = sqrtf(x * x + y * y);
	angle = acosf(x / distance) * RAD2DEG;
	if (end.y > start.y)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}

	*angleZ = angle;

	// xz���
	distance = sqrtf(x * x + z * z);
	angle = acosf(x / distance);

	if (end.z > start.z)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}

	*angleY = angle;

	// yz���
	distance = sqrtf(y * y + z * z);
	angle = acosf(y / distance);

	if (end.z > start.z)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}

	*angleX = angle;
}

inline RECT RectMake(float x, float y, float width, float height)
{
	RECT temp = { x, y, x + width, y + height };
	return temp;
}

inline RECT RectMakeCenter(float x, float y, float width, float height)
{
	return RectMake(x - width / 2, y - height / 2, width, height);
}

inline DWORD FtoDW(float f)
{
	return *((DWORD*)(&f));
}

inline D3DXVECTOR2 get3Dto2D(D3DXVECTOR3 v)
{
	D3DXMATRIX world, view, proj;
	D3DVIEWPORT9 vp;

	D3DDEVICE->GetTransform(D3DTS_WORLD, &world);
	D3DDEVICE->GetTransform(D3DTS_VIEW, &view);
	D3DDEVICE->GetTransform(D3DTS_PROJECTION, &proj);
	D3DDEVICE->GetViewport(&vp);

	D3DXVECTOR3 temp;
	D3DXVec3TransformCoord(&temp, &v, &world);
	D3DXVec3TransformCoord(&temp, &v, &view);
	// ī�޶� �ڿ� �־�� �ϴ� ��
	// �̳��� ȭ�� ���� �׷����� �ȵǹǷ�
	if (temp.z < 0.0f)
	{
		// ����Ʈ ������ ��������
		return D3DXVECTOR2(vp.Width, vp.Height);
	}

	D3DXVECTOR3 p;
	D3DXVec3Project(&p, &v, &vp, &proj, &view, &world);

	return D3DXVECTOR2(p.x, p.y);
}