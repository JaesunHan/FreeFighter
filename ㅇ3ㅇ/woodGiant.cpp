#include "stdafx.h"
#include "woodGiant.h"
#include "skinnedMesh.h"


woodGiant::woodGiant()
{
}


woodGiant::~woodGiant()
{
}

void woodGiant::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);
	_kinds = ENEMY_WOODGIANT;
	_distance = 2.0f;
}

void woodGiant::EnemyAI()
{
}