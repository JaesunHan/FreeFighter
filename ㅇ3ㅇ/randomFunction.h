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
};