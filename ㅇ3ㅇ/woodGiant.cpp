#include "stdafx.h"
#include "woodGiant.h"
#include "skinnedMesh.h"


woodGiant::woodGiant()
{
}


woodGiant::~woodGiant()
{
}

void woodGiant::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);

	_kinds = ENEMY_WOODGIANT;
}
