#include "stdafx.h"
#include "d3dMainGame.h"
#include "mainScene.h"
#include "storeScene.h"
#include "storyScene.h"
#include "selectScene.h"
#include "battleScene.h"
#include "fightScene.h"

//�����β�
#include "myDreamScene.h"

//����󿹾�
#include "playGround.h"

d3dMainGame::d3dMainGame()
{
	PHYSX->init();
}


d3dMainGame::~d3dMainGame()
{
	PHYSX->release();
	SCENEMANAGER->release();
	IMAGEMANAGER->release();
	TEXTUREMANAGER->release();
	TIMEMANAGER->release();
	FONTMANAGER->release();
	SKINNEDMESHMANAGER->release();
	DEVICEMANAGER->destroy();
}

void d3dMainGame::init()
{
	SCENEMANAGER->addScene(_T("mainScene"), new mainScene);
	SCENEMANAGER->addScene(_T("storeScene"), new storeScene);
	SCENEMANAGER->addScene(_T("storyScene"), new storyScene);
	SCENEMANAGER->addScene(_T("selectScene"), new selectScene);
	SCENEMANAGER->addScene(_T("battleScene"), new battleScene);
	SCENEMANAGER->addScene(_T("myDreamScene"), new myDreamScene);
	SCENEMANAGER->addScene(_T("playGround"), new playGround);


	SCENEMANAGER->changeScene(_T("mainScene"));
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

	//�� ������ �Ѿ�� ��ư

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene(_T("mainScene"));
		SCENEMANAGER->sceneInit();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene(_T("storeScene"));
		SCENEMANAGER->sceneInit();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene(_T("myDreamScene"));
		SCENEMANAGER->sceneInit();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene(_T("playGround"));
		SCENEMANAGER->sceneInit();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene(_T("storyScene"));
		SCENEMANAGER->sceneInit();
	}


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