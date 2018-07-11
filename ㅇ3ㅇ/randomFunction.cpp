#include "stdafx.h"
#include "randomFunction.h"

randomFunction::randomFunction()
{
	srand(GetTickCount());
}

randomFunction::~randomFunction()
{
}


int randomFunction::getInt(int num)
{
	return rand() % num;
}

int randomFunction::getFromIntTo(int from, int to)
{
	return rand() % (to - from + 1) + from;
}

float randomFunction::getFloat(float num)
{
	return (float)rand() / (float)((float)RAND_MAX / num);
}

float randomFunction::getFromFloatTo(float from, float to)
{
	float rnd = (float)rand() / (float)RAND_MAX;

	return rnd * (to - from) + from;
}

D3DXVECTOR3 randomFunction::getVec3(D3DXVECTOR3 num)
{
	float rx = this->getFloat(num.x);
	float ry = this->getFloat(num.y);
	float rz = this->getFloat(num.z);

	return D3DXVECTOR3(rx, ry, rz);
}

D3DXVECTOR3 randomFunction::getFromVec3To(D3DXVECTOR3 from, D3DXVECTOR3 to)
{
	float rx = this->getFromFloatTo(from.x, to.x);
	float ry = this->getFromFloatTo(from.y, to.y);
	float rz = this->getFromFloatTo(from.z, to.z);

	return D3DXVECTOR3(rx, ry, rz);
}
