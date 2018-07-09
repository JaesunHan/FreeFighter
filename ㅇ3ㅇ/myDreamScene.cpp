#include "stdafx.h"
#include "myDreamScene.h"

//카메라
#include "camera.h"
//에너미매니저
#include "enemyManager.h"
//테스트용 큐브맨
#include "testCube.h"

myDreamScene::myDreamScene()
	: _testTarget(10.0f, 0.0f, 5.0f)
	, _testStage(0)
	, _em(NULL)
	, _camera(NULL)
	, _cube(NULL)
	, _physXScene(NULL)
	, _material(NULL)
	, _cm(NULL)
{
}


myDreamScene::~myDreamScene()
{
	SAFE_DELETE(_em);
	SAFE_DELETE(_camera);
	SAFE_DELETE(_cube);
}

HRESULT myDreamScene::init()
{
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);

	_em = new enemyManager;
	_em->ChangeStage(0);
	_em->Init();
	_em->setPhysX(_cm, _material);
	
	_camera = new camera;
	_camera->init();

	_cube = new testCube;
	_cube->Setup();

	_em->SetTestCubeAdressLink(_cube);

	return S_OK;
}

void myDreamScene::release()
{

}

void myDreamScene::update()
{
	_cube->Update();
	_em->Update();

	_camera->update(&_cube->GetPos());

}

void myDreamScene::render()
{
	_cube->Render();
	_em->Render();
}
