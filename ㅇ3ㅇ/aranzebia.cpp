#include "stdafx.h"
#include "aranzebia.h"
#include "skinnedMesh.h"


aranzebia::aranzebia()
{
}

aranzebia::~aranzebia()
{
}

void aranzebia::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_ARANZEBIA;

	_skinnedMesh->setAnimationIndexBlend(5);

	_keySet = _playerKeySet[p];



}
void aranzebia::movement()
{

	if (_skinnedMesh->IsAnimationEnd())
	{
		_skinnedMesh->setAnimationIndexBlend(5);

	}

	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
	{
		_skinnedMesh->setAnimationIndexBlend(8);
	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
	{

		_skinnedMesh->setAnimationIndexBlend(2);
	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
	{

		_skinnedMesh->setAnimationIndexBlend(2);
	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_UP]))
	{
		_skinnedMesh->setAnimationIndexBlend(2);
	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_DOWN]))
	{

		_skinnedMesh->setAnimationIndexBlend(2);

	}

	if (KEYMANAGER->isOnceKeyUp(_keySet[KEY_LEFT]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_RIGHT]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_UP]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_DOWN]))
	{
		_skinnedMesh->setAnimationIndexBlend(5);
	}




}