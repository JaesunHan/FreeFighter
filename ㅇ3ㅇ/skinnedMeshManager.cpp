#include "stdafx.h"
#include "skinnedMeshManager.h"
#include "skinnedMesh.h"

skinnedMeshManager::skinnedMeshManager()
{
}


skinnedMeshManager::~skinnedMeshManager()
{
}

skinnedMesh* skinnedMeshManager::addSkinnedMesh(wstring keyName, const WCHAR* folder, const WCHAR* fileName)
{
	skinnedMesh* newMesh = this->findMesh(keyName);

	if (newMesh) return newMesh;

	newMesh = new skinnedMesh;
	newMesh->init(folder, fileName);

	_mMeshList.insert(make_pair(keyName, newMesh));

	return NULL;
}

void skinnedMeshManager::release()
{
	this->deleteAll();
}

skinnedMesh* skinnedMeshManager::findMesh(wstring keyName)
{
	map<wstring, skinnedMesh*>::iterator key = _mMeshList.find(keyName);

	if (key != _mMeshList.end())
		return key->second;

	return NULL;
}

BOOL skinnedMeshManager::deleteMesh(wstring keyName)
{
	map<wstring, skinnedMesh*>::iterator key = _mMeshList.find(keyName);

	if (key != _mMeshList.end())
	{
		SAFE_OBJRELEASE(key->second);
		_mMeshList.erase(key);

		return TRUE;
	}

	return FALSE;
}

BOOL skinnedMeshManager::deleteAll()
{
	map<wstring, skinnedMesh*>::iterator key = _mMeshList.begin();

	for (;key != _mMeshList.end();)
	{
		if (key->second)
		{
			SAFE_OBJRELEASE(key->second);
			key = _mMeshList.erase(key);
		}
		else ++key;
	}

	return TRUE;
}
