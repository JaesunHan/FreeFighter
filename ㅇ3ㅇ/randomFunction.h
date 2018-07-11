#pragma once
#include <time.h>

#define RND randomFunction::GetInstance()

class randomFunction
{
	SINGLETONE(randomFunction)

public:
	int getInt(int num);
	int getFromIntTo(int from, int to);

	float getFloat(float num);
	float getFromFloatTo(float from, float to);

	D3DXVECTOR3 getVec3(D3DXVECTOR3 num);
	D3DXVECTOR3 getFromVec3To(D3DXVECTOR3 from, D3DXVECTOR3 to);
};