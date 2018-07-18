#include "stdafx.h"
#include "d3dMainGame.h"
#include "mainScene.h"
#include "storeScene.h"
#include "storyScene.h"
#include "selectScene.h"
#include "battleScene.h"
#include "fightScene.h"

//빛정민꺼
#include "myDreamScene.h"

d3dMainGame::d3dMainGame()
{
	PHYSX->init();
}


d3dMainGame::~d3dMainGame()
{
	SCENEMANAGER->release();
	PHYSX->release();
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
	SCENEMANAGER->addScene(_T("fightScene"), new fightScene);
	SCENEMANAGER->addScene(_T("myDreamScene"), new myDreamScene);

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

	//각 씬으로 넘어가는 버튼

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
	// 도화지 미리 깔아두기
	D3DDEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		WHITE,						// 깔아둘 도화지 색
		1.0f,						// z버퍼 비율
		0);							// 스텐실 버퍼

	D3DDEVICE->BeginScene();
	// ========================== 랜더링 ==========================
	bool isParentRender;
	if (SCENEMANAGER->getCurrentScene() == SCENEMANAGER->findChild(_T("storyScene"), _T("appearScene")))
		isParentRender = false;
	else
		isParentRender = true;

	SCENEMANAGER->render(isParentRender);

	// ========================== 랜더링 ==========================
	D3DDEVICE->EndScene();

	D3DDEVICE->Present(NULL, NULL, NULL, NULL);
}