#pragma once

#include <string>
using namespace std;

#ifdef UNICODE
struct tagObjectMtlData
{
	wstring			mtlName;
	wstring			textureName;
};
#else
struct tagObjectMtlData
{
	string			mtlName;
	string			textureName;
};
#endif
