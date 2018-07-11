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
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);
	_kinds = ENEMY_ORCFOREMAN;
	_distance = 2.0f;
}

void orcforeMan::EnemyAI()
{
}

