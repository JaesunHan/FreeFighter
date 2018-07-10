#include "stdafx.h"
#include "knight.h"
#include "skinnedMesh.h"



knight::knight()
{
}


knight::~knight()
{
}

void knight::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	//playerController::Init();
	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_KNIGHT;

	_skinnedMesh->setAnimationIndexBlend(5);

	_keySet = _playerKeySet[p];


}
void knight::animation()
{
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
	{
		_skinnedMesh->setAnimationSet(8);
	}

	else if (_skinnedMesh->IsAnimationEnd())
	{
		_skinnedMesh->setAnimationIndexBlend(5);

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
