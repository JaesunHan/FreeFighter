#include "stdafx.h"
#include "player.h"
#include "skinnedMesh.h"


player::player()
{
}


player::~player()
{
}

void player::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);

}

void player::Update()
{
	interfaceCharacter::Update();

	
}

void player::Render()
{
	interfaceCharacter::Render();

}

