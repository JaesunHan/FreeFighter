#include "stdafx.h"
#include "d3dMainGame.h"


d3dMainGame::d3dMainGame()
{
}


d3dMainGame::~d3dMainGame()
{
	SCENEMANAGER->release();
	TEXTUREMANAGER->release();
	TIMEMANAGER->release();
	FONTMANAGER->release();
	DEVICEMANAGER->destroy();
}

void d3dMainGame::init()
{
}

void d3dMainGame::release()
{
}

void d3dMainGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);

	if (KEYMANAGER->isOnceKeyDown(VK_DELETE))
		_isDebug = !_isDebug;

	SCENEMANAGER->update();
}

void d3dMainGame::render()
{
	// 도화지 미리 깔아두기
	D3DDEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		BLACK,						// 깔아둘 도화지 색
		1.0f,						// z버퍼 비율
		0);							// 스텐실 버퍼

	D3DDEVICE->BeginScene();
	// ========================== 랜더링 ==========================

	SCENEMANAGER->render();

	// ========================== 랜더링 ==========================
	D3DDEVICE->EndScene();

	D3DDEVICE->Present(NULL, NULL, NULL, NULL);
}