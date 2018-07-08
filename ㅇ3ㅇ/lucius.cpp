#include "stdafx.h"
#include "lucius.h"
#include "skinnedMesh.h"



lucius::lucius()
{
}


lucius::~lucius()
{
}

void lucius::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_LUCIUS;

	_skinnedMesh->setAnimationIndexBlend(5);

}
