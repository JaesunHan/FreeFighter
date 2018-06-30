#include "stdafx.h"
#include "materialManager.h"


materialManager::materialManager()
{
}


materialManager::~materialManager()
{
	this->deleteAll();
}

#ifdef UNICODE
D3DMATERIAL9 materialManager::addMaterial(wstring keyName, D3DMATERIAL9 mtl)
{
	map<wstring, D3DMATERIAL9>::iterator iter = _mtls.find(keyName);

	if (iter != _mtls.end())
	{
		return iter->second;
	}

	_mtls.insert(make_pair(keyName, mtl));

	return mtl;
}

D3DMATERIAL9 materialManager::findMaterial(wstring keyName)
{
	map<wstring, D3DMATERIAL9>::iterator key = _mtls.find(keyName);

	if (key != _mtls.end())
	{
		return key->second;
	}

	D3DMATERIAL9 temp;
	ZeroMemory(&temp, sizeof(D3DMATERIAL9));
	return temp;
}

BOOL materialManager::deleteMaterial(wstring keyName)
{
	map<wstring, D3DMATERIAL9>::iterator key = _mtls.find(keyName);

	if (key != _mtls.end())
	{
		ZeroMemory(&key->second, sizeof(D3DMATERIAL9));
		_mtls.erase(key);
		return TRUE;
	}

	return FALSE;
}

BOOL materialManager::deleteAll()
{
	map<wstring, D3DMATERIAL9>::iterator key = _mtls.begin();

	for (; key != _mtls.end();)
	{
		ZeroMemory(&key->second, sizeof(D3DMATERIAL9));
		key = _mtls.erase(key);
	}

	_mtls.clear();

	return TRUE;
}
#else
D3DMATERIAL9 materialManager::addMaterial(string keyName, D3DMATERIAL9 mtl)
{
	map<string, D3DMATERIAL9>::iterator iter = _mtls.find(keyName);

	if (iter != _mtls.end())
	{
		return iter->second;
	}

	_mtls.insert(make_pair(keyName, mtl));

	return mtl;
}

D3DMATERIAL9 materialManager::findMaterial(string keyName)
{
	map<string, D3DMATERIAL9>::iterator key = _mtls.find(keyName);

	if (key != _mtls.end())
	{
		return key->second;
	}

	D3DMATERIAL9 temp;
	ZeroMemory(&temp, sizeof(D3DMATERIAL9));
	return temp;
}

BOOL materialManager::deleteMaterial(string keyName)
{
	map<string, D3DMATERIAL9>::iterator key = _mtls.find(keyName);

	if (key != _mtls.end())
	{
		ZeroMemory(&key->second, sizeof(D3DMATERIAL9));
		_mtls.erase(key);
		return TRUE;
	}

	return FALSE;
}

BOOL materialManager::deleteAll()
{
	map<string, D3DMATERIAL9>::iterator key = _mtls.begin();

	for (; key != _mtls.end();)
	{
		ZeroMemory(&key->second, sizeof(D3DMATERIAL9));
		key = _mtls.erase(key);
	}

	_mtls.clear();

	return TRUE;
}
#endif