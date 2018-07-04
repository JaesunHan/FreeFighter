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
	D3DXMATRIX		matS, matR, matT;				//스케일,로테이션,트랜스레이션
	
	//D3DXMatrixScaling(&matS, _worldScale.x, _worldScale.y, _worldScale.z);	//크기 정해줄때 _worldScale만 바꿔주면됨
	//D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);		//위의 주석과 마찬가지

	//_worldTM = matS * matR * matT;
}

