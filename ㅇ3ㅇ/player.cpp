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

}

void player::Update()
{
	interfaceCharacter::Update();
}

void player::Render()
{
	interfaceCharacter::Render();

	D3DXMATRIX		matS;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);

	_worldTM = matS;
}

