#include "stdafx.h"
#include "playerController.h"
#include "playerKeySet.h"



playerController::playerController()
	:_worldPos(0, 0, 0)
	, _worldDir(0, 0, 0)
	, _localPos(0, 0, 0)
	, _speedPlayer(0.05f)
	, _worldScale(0.005f, 0.005f, 0.005f)
	, _worldRotation(0, 0, 0)//���� �Ⱦ��Ű���
	, _RotY(0.0f)
	, _RotX(0.0f)
	, _RotZ(0.0f)
{
	D3DXMatrixIdentity(&_worldTM);
}


playerController::~playerController()
{

}

void playerController::Setup()
{

}

void playerController::Update()
{
	moving();
}

void playerController::moving()
{

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
		_worldPos -= (_worldDir * _speedPlayer);
	}

	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_worldPos += (_worldDir * _speedPlayer);
	}



	D3DXMATRIX		matS, matR, matT;				//������,�����̼�,Ʈ�������̼�

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, _worldScale.x, _worldScale.y, _worldScale.z);			//ũ�� �����ٶ� _worldScale�� �ٲ��ָ��


	D3DXMatrixRotationY(&matR, _RotY);
	D3DXVec3TransformNormal(&_worldDir, &D3DXVECTOR3(0, 0, 1), &matR);


	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);		//���� �ּ��� ��������

	_worldTM = matS * matR * matT;
}

