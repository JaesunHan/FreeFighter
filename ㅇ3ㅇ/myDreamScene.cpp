#include "stdafx.h"
#include "myDreamScene.h"

//카메라
#include "camera.h"
//에너미매니저
#include "enemyManager.h"
#include "enemy.h"
//플레이어매니저
#include "playerManager.h"
#include "player.h"
//그리드
#include "grid.h"

myDreamScene::myDreamScene()
	: _testTarget(10.0f, 0.0f, 5.0f)
	, _testStage(0)
	, _em(NULL)
	, _camera(NULL)
	, _grid(NULL)
	, _physXScene(NULL)
	, _material(NULL)
	, _cm(NULL)
	, _pm(NULL)
{
}


myDreamScene::~myDreamScene()
{
	SAFE_DELETE(_em);
	SAFE_DELETE(_camera);
	SAFE_DELETE(_grid);
	SAFE_DELETE(_pm);
}

HRESULT myDreamScene::init()
{
	//물리엔진
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);
	_cm->setOverlapRecoveryModule(true);

	vector<PLAYABLE_CHARACTER> temp;
	temp.push_back(CHAR_ZEALOT);
	_pm = new playerManager;
	_pm->init(GAME_FIGHT, PMODE_PLAYER1, temp, &_cm, _material);

	_grid = new grid;
	_grid->init(BLACK);

	_em = new enemyManager;
	_em->ChangeStage(0);
	_em->setPhysX(_cm, _material);
	_em->Init();
	
	_camera = new camera;
	_camera->init();

	_em->SetPlayerAdressLink(_pm);

	return S_OK;
}

void myDreamScene::release()
{

}

void myDreamScene::update()
{
	if (_pm)
		_pm->update();
	
	if (_em)
		_em->Update();

	if (_camera)
		_camera->update();

}

void myDreamScene::render()
{
	if (_grid)
		_grid->render();

	if (_pm)
		_pm->render(0);

	if (_em)
		_em->Render();


}
