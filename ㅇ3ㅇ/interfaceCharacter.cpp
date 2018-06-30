#include "stdafx.h"
#include "interfaceCharacter.h"
#include "skinnedMesh.h"


interfaceCharacter::interfaceCharacter()
{
}


interfaceCharacter::~interfaceCharacter()
{
}

void interfaceCharacter::Setup(wstring keyPath, wstring keyName)
{
	_skinnedMesh = new skinnedMesh;
	_skinnedMesh->init(keyPath.c_str(), keyName.c_str());
	_skinnedMesh->setParentMatrix(&_worldTM);
}
