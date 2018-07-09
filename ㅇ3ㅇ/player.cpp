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
	playerController::Init();
	_skinnedMesh->setParentMatrix(&_worldTM);


	//blend�� �ε巴��, set�� �ҶҲ���

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
}

//void player::movement()
//{
//
//	//������ ���ڤ� �غ��ô�.
//	//�ִϸ��̼��� ���� �������� �� ����, �����ص� �������� ����
//	//if (_skinnedMesh->IsAnimationEnd()&&KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
//	//if (_skinnedMesh->IsAnimationEnd())
//
//
//
//	 if (KEYMANAGER->isOnceKeyDown(_keySet[KEY_ATTACK]))
//	{
//		_skinnedMesh->setAnimationSet(8);
//
//	}
//
//	 else if (_skinnedMesh->IsAnimationEnd())
//	 {
//		 _skinnedMesh->setAnimationIndexBlend(5);
//
//	 }
//
//		if (KEYMANAGER->isStayKeyDown(_keySet[KEY_LEFT]))
//		{
//
//			_skinnedMesh->setAnimationIndexBlend(2);
//		}
//
//		if (KEYMANAGER->isStayKeyDown(_keySet[KEY_RIGHT]))
//		{
//
//			_skinnedMesh->setAnimationIndexBlend(2);
//		}
//
//		if (KEYMANAGER->isStayKeyDown(_keySet[KEY_UP]))
//		{
//			_skinnedMesh->setAnimationIndexBlend(2);
//		}
//
//		if (KEYMANAGER->isStayKeyDown(_keySet[KEY_DOWN]))
//		{
//
//			_skinnedMesh->setAnimationIndexBlend(2);
//
//		}
//
//		if (KEYMANAGER->isOnceKeyUp(_keySet[KEY_LEFT]) ||
//			KEYMANAGER->isOnceKeyUp(_keySet[KEY_RIGHT]) ||
//			KEYMANAGER->isOnceKeyUp(_keySet[KEY_UP]) ||
//			KEYMANAGER->isOnceKeyUp(_keySet[KEY_DOWN]))
//		{
//			_skinnedMesh->setAnimationIndexBlend(5);
//		}
//	
//}