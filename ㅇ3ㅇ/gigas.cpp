#include "stdafx.h"
#include "gigas.h"
#include "skinnedMesh.h"

gigas::gigas()
{
}

gigas::~gigas()
{
}

void gigas::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
//	playerController::Init();

	_skinnedMesh->setParentMatrix(&_worldTM);
	_Charactor = CHARACTOR_GIGAS;

	//지우지말기 ★★★★★★★

	_skinnedMesh->setAnimationIndexBlend(gigasIndex[_act]);

	_skinnedMesh->setAnimationIndexBlend(ACT_IDLE);

	_keySet = _playerKeySet[p];

}


void gigas::animation()
{
	//	_skinnedMesh->setAnimationIndexBlend(gigasIndex[_act]);

	if (isAbsoluteMotion())
	{
		if (_skinnedMesh->IsAnimationEnd())
		{
			_act = ACT_IDLE;
		}
	}

	
	if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
	{
		_act = ACT_ATTACK00;
	}
	
	

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
	{
		_act = ACT_RUN_FRONT;
	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
	{
		_act = ACT_RUN_FRONT;
	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_UP]))
	{
		_act = ACT_RUN_FRONT;
	}

	if (KEYMANAGER->isStayKeyDown(_keySet[KEY_DOWN]))
	{
		_act = ACT_RUN_FRONT;
	}

	if (KEYMANAGER->isOnceKeyUp(_keySet[KEY_LEFT]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_RIGHT]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_UP]) ||
		KEYMANAGER->isOnceKeyUp(_keySet[KEY_DOWN]))
	{
		_act = ACT_IDLE;
	}

	_skinnedMesh->setAnimationIndexBlend(gigasIndex[_act]);

}
