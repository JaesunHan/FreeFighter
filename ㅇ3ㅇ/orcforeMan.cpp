#include "stdafx.h"
#include "orcforeMan.h"
#include "skinnedMesh.h"


orcforeMan::orcforeMan()
{
	
}


orcforeMan::~orcforeMan()
{
}

void orcforeMan::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_kinds = ENEMY_ORCFOREMAN;
}
