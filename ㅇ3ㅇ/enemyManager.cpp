#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

//플레이어 매니저
#include "playerManager.h"
#include "player.h"

//자식들
#include "darkWolf.h"		//어두운늑대
#include "orcforeMan.h"		//오크_십장
#include "woodGiant.h"		//나무거인



enemyManager::enemyManager()
	: 
	_stage(0)
	, _timer(0)
{
}


enemyManager::~enemyManager()
{
	Release();
}

void enemyManager::Init()
{
	//CreateEnemy();
}

void enemyManager::Release()
{
	for (auto p : _vEnemy)
	{
		SAFE_DELETE(p);
	}
	_vEnemy.clear();
}

void enemyManager::Update()
{
	//_timer++;
	//
	//if (_timer % 100 == 0)
	//{
	//	_timer = 0;
	//	CreateEnemy();
	//}

	if (KEYMANAGER->isOnceKeyDown('H')) CreateEnemy();

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->SetTarget(&_pm->getVPlayers()[0]->p->GetPosition());

		_vEnemy[i]->AttackMotionEnd(_pm->getVPlayers()[0]->p, 10.0f, 1.5f, 1.5f);
		
		_vEnemy[i]->Update();

		if (_vEnemy[i]->GetIsDeadAnimationEnd())
		{
			_vEnemy[i]->SetDisappearCount();

			if (_vEnemy[i]->GetDisappearCount() > 100.0f)
				_vEnemy.erase(_vEnemy.begin() + i);
		}
	}

}

void enemyManager::Render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->Render();
	}
}

void enemyManager::ChangeStage(int num)
{
	Release();
	_stage = num;
}

void enemyManager::CreateEnemy()
{
	switch (_stage)
	{
	case 0:
	{
		for (int i = -5; i <= 5; i++)
		{
			enemy* dw = new darkWolf;
			dw->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"));
			dw->createContoller(&_cm, _material , 0.5f , 0.5f);
			dw->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(i * 3, 0, -5));
			dw->setEmMemory(this);
			_vEnemy.push_back(dw);
			break;
		}
	}
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void enemyManager::Attack()
{
	
}
