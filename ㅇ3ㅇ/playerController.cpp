#include "stdafx.h"
#include "playerController.h"


playerController::playerController()
	:_worldPos(0,0,0)
	,_worldDir(1,0,0)
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

