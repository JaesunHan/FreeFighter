#include "stdafx.h"
#include "jmAstar.h"
#include "enemy.h"


jmAstar::jmAstar()
{
}


jmAstar::~jmAstar()
{
}

float jmAstar::WhereGoing(D3DXVECTOR3 target, D3DXVECTOR3 currentPos)
{
	// ���� -> Ÿ�� ���⺤��
	D3DXVECTOR3 oriToTargetVec = target - D3DXVECTOR3(0, 0, 0);
	D3DXVec3Normalize(&oriToTargetVec, &oriToTargetVec);
	// ���� -> Ÿ�� ����
	float oriToTarget = getAngle(1, 1, oriToTargetVec.x, oriToTargetVec.z);

	// ������ġ -> Ÿ�� ���⺤��
	D3DXVECTOR3 curToTargetVec = target - currentPos;
	D3DXVec3Normalize(&curToTargetVec, &curToTargetVec);
	// ������ġ -> Ÿ�� ����
	float curToTarget = getAngle(1, 1, curToTargetVec.x, curToTargetVec.z);

	if (oriToTarget > curToTarget) return D3DX_PI / 2;
	else return -D3DX_PI / 2;

	return D3DX_PI * 2;
}
