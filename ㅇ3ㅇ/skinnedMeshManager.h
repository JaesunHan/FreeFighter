#pragma once

#include <map>
using namespace std;

#define SKINNEDMESHMANAGER skinnedMeshManager::GetInstance()

class skinnedMesh;

class skinnedMeshManager
{
	SINGLETONE(skinnedMeshManager)

private:
	map<wstring, skinnedMesh*>	_mMeshList;

public:
	skinnedMesh* addSkinnedMesh(wstring keyName, const WCHAR* folder, const WCHAR* fileName);

	void release();

	skinnedMesh* findMesh(wstring keyName);

	BOOL deleteMesh(wstring keyName);
	BOOL deleteAll();
};

