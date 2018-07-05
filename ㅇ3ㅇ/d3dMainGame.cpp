#include "stdafx.h"
#include "d3dMainGame.h"
#include "mainScene.h"
#include "storeScene.h"
#include "storyScene.h"
#include "selectScene.h"
#include "battleScene.h"

//ºûÁ¤¹Î²¨
#include "myDreamScene.h"

//±è¼öºó¿¹¾Æ
#include "playGround.h"

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


	SCENEMANAGER->changeScene(_T("playGround"));
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
	// µµÈ­Áö ¹Ì¸® ±ò¾ÆµÎ±â
	D3DDEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		WHITE,						// ±ò¾ÆµÑ µµÈ­Áö »ö
		1.0f,						// z¹öÆÛ ºñÀ²
		0);							// ½ºÅÙ½Ç ¹öÆÛ

	D3DDEVICE->BeginScene();
	// ========================== ·£´õ¸µ ==========================

	SCENEMANAGER->render();

	// ========================== ·£´õ¸µ ==========================
	D3DDEVICE->EndScene();

	D3DDEVICE->Present(NULL, NULL, NULL, NULL);
}