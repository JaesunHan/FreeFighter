#include "stdafx.h"
#include "gigas.h"
#include "skinnedMesh.h"

gigas::gigas()
{
}

gigas::~gigas()
{
}

void gigas::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_GIGAS;

	_skinnedMesh->setAnimationIndexBlend(5);

}

void gigas::movement()
{

	//		else if (_skinnedMesh->IsAnimationEnd())

	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
	{
		_skinnedMesh->setAnimationSet(8);
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
