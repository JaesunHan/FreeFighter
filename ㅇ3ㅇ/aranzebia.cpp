#include "stdafx.h"
#include "aranzebia.h"
#include "skinnedMesh.h"


aranzebia::aranzebia()
{
}

aranzebia::~aranzebia()
{
}

void aranzebia::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_ARANZEBIA;

	_skinnedMesh->setAnimationIndexBlend(5);


}
