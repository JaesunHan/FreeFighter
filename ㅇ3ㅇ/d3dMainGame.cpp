#include "stdafx.h"
#include "d3dMainGame.h"
#include "MainScene.h"
#include "storeScene.h"
#include "storyScene.h"
#include "selectScene.h"
#include "battleScene.h"

d3dMainGame::d3dMainGame()
{
}


d3dMainGame::~d3dMainGame()
{
	SCENEMANAGER->release();
	IMAGEMANAGER->release();
	TEXTUREMANAGER->release();
	TIMEMANAGER->release();
	FONTMANAGER->release();
	DEVICEMANAGER->destroy();
}

void d3dMainGame::init()
{
	SCENEMANAGER->addScene(_T("MainScene"), new MainScene);
	SCENEMANAGER->addScene(_T("storeScene"), new storeScene);
	SCENEMANAGER->addScene(_T("storyScene"), new storyScene);
	SCENEMANAGER->addScene(_T("selectScene"), new selectScene);
	SCENEMANAGER->addScene(_T("battleScene"), new battleScene);

	SCENEMANAGER->changeScene(_T("MainScene"));
	SCENEMANAGER->sceneInit();
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
		WHITE,						// ��Ƶ� ��ȭ�� ��
		1.0f,						// z���� ����
		0);							// ���ٽ� ����

	D3DDEVICE->BeginScene();
	// ========================== ������ ==========================

	SCENEMANAGER->render();

	// ========================== ������ ==========================
	D3DDEVICE->EndScene();

	D3DDEVICE->Present(NULL, NULL, NULL, NULL);
}