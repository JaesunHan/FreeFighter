#include "stdafx.h"
#include "orcforeMan.h"
#include "skinnedMesh.h"


orcforeMan::orcforeMan()
{
	
}


orcforeMan::~orcforeMan()
{
}

void orcforeMan::Init(wstring keyPath, wstring keyName)
{
	enemy::Init(keyPath, keyName);

	_kinds = ENEMY_ORCFOREMAN;
	_distance = 2.0f;
}

