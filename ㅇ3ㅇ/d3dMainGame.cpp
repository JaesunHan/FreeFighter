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
	// ��ȭ�� �̸� ��Ƶα�
	D3DDEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		BLACK,						// ��Ƶ� ��ȭ�� ��
		1.0f,						// z���� ����
		0);							// ���ٽ� ����

	D3DDEVICE->BeginScene();
	// ========================== ������ ==========================

	SCENEMANAGER->render();

	// ========================== ������ ==========================
	D3DDEVICE->EndScene();

	D3DDEVICE->Present(NULL, NULL, NULL, NULL);
}