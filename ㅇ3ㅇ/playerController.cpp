#include "stdafx.h"
#include "playerController.h"



playerController::playerController()
	:_worldPos(0, 0, 0)
	, _worldDir(1, 0, 0)
	, _localPos(0, 0, 0)
	, _speedPlayer(0.05f)
	, _worldScale(1, 1, 1)
	, _worldRotation(0,0,0)
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
	
}

void playerController::moving()
{
	D3DXMATRIX		matS, matR, matT;				//������,�����̼�,Ʈ�������̼�
	
	//D3DXMatrixScaling(&matS, _worldScale.x, _worldScale.y, _worldScale.z);	//ũ�� �����ٶ� _worldScale�� �ٲ��ָ��
	//D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);		//���� �ּ��� ��������

	//_worldTM = matS * matR * matT;
}

