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
	return (float)rand() / (float)num;
}

float randomFunction::getFromFloatTo(float from, float to)
{
	float rnd = (float)rand() / (float)RAND_MAX;

	return rnd * (to - from) + from;
}
