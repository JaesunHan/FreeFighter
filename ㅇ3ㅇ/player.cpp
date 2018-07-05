#include "stdafx.h"
#include "player.h"
#include "skinnedMesh.h"


player::player()
	:n(0)
{
}


player::~player()
{
}

void player::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);
	_skinnedMesh->setAnimationIndexBlend(5);

	_keySet = _playerKeySet[p];


}

void player::Update()
{
	interfaceCharacter::Update();
	playerController::Update();

	movement();

	//if (KEYMANAGER->isOnceKeyDown('Z'))
	//{
	//	_skinnedMesh->setAnimationIndexBlend(n++);
	//}
}

void player::Render()
{
	interfaceCharacter::Render();

}

void player::movement()
{

	//집에서 마자ㅓ 해봅시다.
	//if (_skinnedMesh->IsAnimationEnd()&&KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))


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

