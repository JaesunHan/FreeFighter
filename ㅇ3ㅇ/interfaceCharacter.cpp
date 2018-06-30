#include "stdafx.h"
#include "interfaceCharacter.h"
#include "skinnedMesh.h"

interfaceCharacter::interfaceCharacter()
{
}


interfaceCharacter::~interfaceCharacter()
{
}

void interfaceCharacter::Init(wstring keyPath, wstring keyName)
{
	_skinnedMesh = new skinnedMesh;
	_skinnedMesh->init(keyPath.c_str(), keyName.c_str());
}
