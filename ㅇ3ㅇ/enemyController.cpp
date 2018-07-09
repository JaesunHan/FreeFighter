#include "stdafx.h"
#include "enemyController.h"


enemyController::enemyController()
	: _worldSca(1, 1, 1)
	, _worldRot(0, 0, 0)
	, _worldPos(0, 0, 0)
	, _worldDir(0, 0, 1)
	, _targetPos(NULL)
	, _speed(0.01f)
{
	D3DXMatrixIdentity(&_worldTM);
}


enemyController::~enemyController()
{

}

void enemyController::Init()
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);
	D3DXMatrixRotationYawPitchRoll(&matR, _worldRot.y, _worldRot.x, _worldRot.z);

	if (_targetPos)
	{
		_worldDir = (*_targetPos) - _worldPos;
		D3DXVec3Normalize(&_worldDir, &_worldDir);

		float angle = getAngle(0, 0, _worldDir.x, _worldDir.z) - D3DX_PI / 2;

		//D3DXMatrixRotationY(&matR, angle);
		D3DXMatrixRotationYawPitchRoll(&matR, angle, 0.0f, 0.0f);
	}
	
	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	_worldTM = matS * matR * matT;
}

void enemyController::Moving()
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	
	D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);
	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);
	
	if (_targetPos)
	{
		_worldDir = (*_targetPos) - _worldPos;
		D3DXVec3Normalize(&_worldDir, &_worldDir);
	
		_worldPos += _worldDir * _speed;
	
		float angle = getAngle(0, 0, _worldDir.x, _worldDir.z) - D3DX_PI / 2;
	
		//D3DXMatrixRotationY(&matR, angle);
		D3DXMatrixRotationYawPitchRoll(&matR, angle, 0.0f, 0.0f);
	
		D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);
	}
	
	_worldTM = matS * matR * matT;
}