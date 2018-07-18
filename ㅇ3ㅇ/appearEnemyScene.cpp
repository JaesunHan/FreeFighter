#include "stdafx.h"
#include "appearEnemyScene.h"
#include "enemyManager.h"
#include "background.h"
//#include "camera.h"
#include "cameraWalk.h"

appearEnemyScene::appearEnemyScene()
	: _em(NULL)
	, _pBG(NULL)
	, _pCW(NULL)
{
}


appearEnemyScene::~appearEnemyScene()
{
}

HRESULT appearEnemyScene::init()
{
	_pCW = new cameraWalk;
	_pCW->init();
	return S_OK;
}

void appearEnemyScene::release()
{
	if (_em)
		SAFE_RELEASE(_em);
	if (_pBG)
		SAFE_OBJRELEASE(_pBG);
	if (_pCW)
		SAFE_DELETE(_pCW);
}

void appearEnemyScene::update()
{
	if (_pCW)
	{
		_pCW->update();
		//_pCW->setCamLookAt(_em->getBossPosition());
	}
}

void appearEnemyScene::render()
{
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);

	if (_pBG)
		_pBG->render();

}

void appearEnemyScene::setCamWalkStartKeyFrame()
{
	_pCW->setStartKeyFrame();
}
