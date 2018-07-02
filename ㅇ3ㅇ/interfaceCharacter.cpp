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

void interfaceCharacter::Update()
{
	_skinnedMesh->update();
}

void interfaceCharacter::Render()
{
	_skinnedMesh->render();
}
