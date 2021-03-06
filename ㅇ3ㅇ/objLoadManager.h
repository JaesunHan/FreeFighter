#pragma once

#include <fstream>
#include <strstream>
#include <vector>
#include <map>
using namespace std;

#include "mtlTexData.h"

#define OBJLOADER	objLoadManager::GetInstance()

class gameObject;

class objLoadManager
{
	SINGLETONE(objLoadManager)

public:
#ifdef UNICODE
	vector<gameObject> load(const WCHAR* fileName = L"", D3DXVECTOR3* half = NULL);
	vector<gameObject> load(const WCHAR* folder, const WCHAR* fileName, D3DXVECTOR3* half = NULL);
	LPD3DXMESH loadMesh(OUT vector<tagObjectMtlData>& mtlTex, IN const WCHAR* fileName = L"");
#else
	vector<gameObject> load(const char* fileName = "");
	LPD3DXMESH loadMesh(OUT vector<tagObjectMtlData>& mtlTex, IN const char* fileName = "");
#endif
	map<string, tagObjectMtlData> loadMtlLib(const char* fileName = "");
	map<string, tagObjectMtlData> loadMtlLib(const WCHAR* folder, const WCHAR* fileName);
};

