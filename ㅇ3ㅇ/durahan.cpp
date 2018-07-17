#include "stdafx.h"
#include "durahan.h"


durahan::durahan()
{
}


durahan::~durahan()
{
}

void durahan::Init(wstring keyPath, wstring keyName, int stage)
{
	enemy::Init(keyPath, keyName, stage);
	
	_kinds = ENEMY_DURAHAN;
}
