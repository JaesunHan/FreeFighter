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
	enemy::Init(keyPath, keyName);

	_kinds = ENEMY_WOODGIANT;
	_distance = 2.0f;
}