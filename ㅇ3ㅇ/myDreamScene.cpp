#include "stdafx.h"
#include "myDreamScene.h"

//카메라
#include "camera.h"
//에너미매니저
#include "enemyManager.h"

myDreamScene::myDreamScene()
	: _testTarget(10.0f, 0.0f, 5.0f)
	, _testStage(0)
{
}


myDreamScene::~myDreamScene()
{
	SAFE_DELETE(_em);
	SAFE_DELETE(_camera);
}

HRESULT myDreamScene::init()
{
	_em = new enemyManager;
	_em->ChangeStage(0);
	_em->Init();
	
	_camera = new camera;
	_camera->init();


	return S_OK;
}

void myDreamScene::release()
{
	SAFE_DELETE(_em);
}

void myDreamScene::update()
{
	_camera->update();
	_em->Update();

	if (KEYMANAGER->isOnceKeyDown('Q')) _em->ChangeStage(++_testStage);

	_em->SetTarget(&_testTarget);
	if (KEYMANAGER->isOnceKeyDown(VK_F6)) _em->SetTarget(NULL);

	
}

void myDreamScene::render()
{
	_em->Render();
}
