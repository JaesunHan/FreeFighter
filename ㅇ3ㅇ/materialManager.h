#pragma once

#include <map>
#include <string>
using namespace std;

#define MATERIALMANAGER materialManager::GetInstance()

class materialManager
{
	SINGLETONE(materialManager)

#ifdef UNICODE
private:
	map<wstring, D3DMATERIAL9>		_mtls;

public:

	D3DMATERIAL9 addMaterial(wstring keyName, D3DMATERIAL9 mtl);

	D3DMATERIAL9 findMaterial(wstring keyName);

	BOOL deleteMaterial(wstring keyName);
	BOOL deleteAll();
#else
private:
	map<string, D3DMATERIAL9>		_mtls;

public:
	D3DMATERIAL9 addMaterial(string keyName, D3DMATERIAL9 mtl);

	D3DMATERIAL9 findMaterial(string keyName);

	BOOL deleteMaterial(string keyName);
	BOOL deleteAll();
#endif
};

