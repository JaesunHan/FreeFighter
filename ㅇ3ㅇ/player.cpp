#include "stdafx.h"
#include "player.h"
#include "skinnedMesh.h"




player::player()
	:n(0)
	, _RotY(0.0f)
	, _speedPlayer(0.05f)
{
	D3DXMatrixIdentity(&_worldTM);
}


player::~player()
{
}

void player::Init(PLAYERS p, wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	//playerController::Init();
	_skinnedMesh->setParentMatrix(&_worldTM);


	//blend는 부드럽고, set은 뚝뚝끊김

	_keySet = _playerKeySet[p];
}

void player::Update()
{
	interfaceCharacter::Update();



	animation();

	control();

	//if (KEYMANAGER->isOnceKeyDown('Z'))
	//{
	//	_skinnedMesh->setAnimationIndexBlend(n++);
	//}
}

void player::Render()
{
	interfaceCharacter::Render();

}

void player::control()
{

	D3DXMATRIX matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);
	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_RotY -= 0.05f;
	}

	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		_RotY += 0.05f;
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_velocity.x = (_worldDir.x * _speedPlayer);
	}

	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_velocity.z += (_worldDir.z * _speedPlayer);
	}


		D3DXMatrixRotationY(&matR, _RotY);

		_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

		_worldPos = D3DXVECTOR3(_controller->getPosition().x, _controller->getPosition().y, _controller->getPosition().z);
		D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	_worldTM = matS * matR * matT;
}

void player::animation()
{
}

//void player::movement()
//{
//
//	//집에서 마자ㅓ 해봅시다.
//	//애니메이션이 가진 프레임이 다 돌면, 설정해둔 프레임을 실행
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