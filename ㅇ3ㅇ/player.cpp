#include "stdafx.h"
#include "player.h"
#include "skinnedMesh.h"

player::player()
	:n(0)
	, _RotY(0.0f)
	, _speedPlayer(0.0f)
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


	//blend´Â ºÎµå·´°í, setÀº ¶Ò¶Ò²÷±è

	_keySet = _playerKeySet[p];

	_worldDir = D3DXVECTOR3(0, 0, 1);



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
		_speedPlayer = -0.03f;
	}

	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_speedPlayer = 0.03f;
	}
	else
		_speedPlayer = 0.0f;


	_velocity.x = (_worldDir.x * _speedPlayer);
	_velocity.z  = (_worldDir.z * _speedPlayer);

		D3DXMatrixRotationY(&matR, _RotY);
		D3DXVec3TransformNormal(&_worldDir, &D3DXVECTOR3(0, 0, 1), &matR);


		_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

		_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
		D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	_worldTM = matS * matR * matT;
}

void player::animation()
{
}

void player::circleHitEnemy()
{
}

