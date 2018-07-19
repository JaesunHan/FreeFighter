#include "stdafx.h"
#include "appearEnemyScene.h"
#include "enemyManager.h"
#include "background.h"
//#include "camera.h"
#include "cameraWalk.h"
#include "enemy.h"

appearEnemyScene::appearEnemyScene()
	: _em(NULL)
	, _pBG(NULL)
	, _pCW(NULL)
	, _cnt(0)
{
}


appearEnemyScene::~appearEnemyScene()
{
}

HRESULT appearEnemyScene::init()
{
	_pCW = new cameraWalk;
	_pCW->init();
	_cnt = 0;

	D3DDEVICE->GetViewport(&_originViewPort);

	return S_OK;
}

void appearEnemyScene::release()
{
	if (_pCW)
		SAFE_OBJRELEASE(_pCW);
}

void appearEnemyScene::update()
{
	_cnt++;
	if (_em)
	{
		_em->Update();
		
		//for (int i = 0; i < _em->GetEnemy().size(); ++i)
		//{
		//	_em->GetEnemy()[i]->EnemyStoryAI();
		//}
	}
	

	if (_cnt >= 0 && _cnt < 350)
	{
		_pCW->shakeCamera(_pCW->getKeyFrame());
	}
	else
	{
		_cnt = 0;
		SCENEMANAGER->changeParent();
	}
	//if (_pCW)
	//{
	//	
	//	if (_cnt >= 0 && _cnt < 200)
	//	{
	//	//	
	//	//}
	//	//else if (_cnt >= 100 && _cnt < 170)
	//	//{
	//		//_pCW->InitShakeTrack();
	//		//_pCW->shakeCamera(_pCW->getKeyFrame());
	//	}
	//	else
	//	{
	//		_cnt = 0;
	//		SCENEMANAGER->changeParent();
	//	}
	//	//_pCW->update();
	//	//_pCW->setCamLookAt(_em->getBossPosition());
	//}
	
}

void appearEnemyScene::render()
{
	D3DDEVICE->SetViewport(&_originViewPort);
	
	float width = _originViewPort.Width;
	float height = _originViewPort.Height;
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection,
		D3DX_PI / 4.0f,					// 시야 각
		width / height,					// 화면 비율(가로 / 세로)
		0.1f,							// 화면에 나올 가까운 z값
		1000.0f);						// 화면에 나올 먼 z값

										// 만든 매트릭스를 디바이스에 적용
	D3DDEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_mapMatWorld);

	if (_pBG)
		_pBG->render();
	if (_em)
		_em->Render();

}

void appearEnemyScene::setCamWalkStartKeyFrame()
{
	_pCW->setStartKeyFrame();
}
