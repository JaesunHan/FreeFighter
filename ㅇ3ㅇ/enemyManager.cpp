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
	: _stage(0)
	, _timer(0)
{
}


enemyManager::~enemyManager()
{
	Release();
}

void enemyManager::Init()
{
	CreateEnemyInit();
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
	//if (KEYMANAGER->isOnceKeyDown('A')) CreateEnemyInit();

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->SetTarget(&_pm->getVPlayers()[0]->p->GetPosition());

		_vEnemy[i]->AttackMotionEnd(_pm->getVPlayers()[0]->p, 10.0f, 1.5f, 1.5f);
		
		_vEnemy[i]->Update();

		if (_vEnemy[i]->GetIsDead())
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

void enemyManager::CreateEnemyInit()
{
	for (int i = 0; i < 5; i++)
	{
		enemy* dw = new darkWolf;
		dw->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"), _stage);
		dw->createContoller(&_cm, _material, 0.5f, 0.5f);
		dw->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 3.0f, 0));
		dw->SetRespawnPos(dw->GetPosition());
		dw->setEmMemory(this);
		_vEnemy.push_back(dw);

		break;

		enemy* orc = new orcforeMan;
		orc->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"), _stage);
		orc->createContoller(&_cm, _material, 0.5f, 0.5f);
		orc->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		orc->SetRespawnPos(orc->GetPosition());
		orc->setEmMemory(this);
		_vEnemy.push_back(orc);

		enemy* wood = new woodGiant;
		wood->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"), _stage);
		wood->createContoller(&_cm, _material, 0.5f, 0.5f);
		wood->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		wood->SetRespawnPos(wood->GetPosition());
		wood->setEmMemory(this);
		_vEnemy.push_back(wood);
	}
	
}

void enemyManager::CreateEnemyUpdate()
{
	int dwSize = 0;
	int orcSize = 0;
	int woodSize = 0;

	// 일단 종류마다 몇마리있나
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (_vEnemy[i]->GetKind() == (Kinds)ENEMY_DARKWOLF) dwSize++;
		if (_vEnemy[i]->GetKind() == (Kinds)ENEMY_ORCFOREMAN) orcSize++;
		if (_vEnemy[i]->GetKind() == (Kinds)ENEMY_WOODGIANT) woodSize++;
	}

	// 없어지자마자 생기면 좀 그러니까
	if (_timer > 100)
	{
		for (int i = 0; i < 5; i++)
		{
			//늑대 소환
			if (i < 5 - dwSize)
			{
				//포지션 안곂치게 할거임
				float rndPosX, rndPosY, rndPosZ = 0;

				enemy* dw = new darkWolf;
				dw->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"), _stage);
				dw->createContoller(&_cm, _material, 0.5f, 0.5f);
				dw->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
				dw->SetRespawnPos(dw->GetPosition());
				dw->setEmMemory(this);
				_vEnemy.push_back(dw);
			}
			//오크 소환
			if (i < 5 - orcSize)
			{
				float rndPosX, rndPosY, rndPosZ = 0;

				enemy* orc = new orcforeMan;
				orc->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"), _stage);
				orc->createContoller(&_cm, _material, 0.5f, 0.5f);
				orc->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
				orc->SetRespawnPos(orc->GetPosition());
				orc->setEmMemory(this);
				_vEnemy.push_back(orc);
			}
			//나무 소환
			if (i < 5 - woodSize)
			{
				float rndPosX, rndPosY, rndPosZ = 0;

				enemy* wood = new woodGiant;
				wood->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"), _stage);
				wood->createContoller(&_cm, _material, 0.5f, 0.5f);
				wood->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
				wood->SetRespawnPos(wood->GetPosition());
				wood->setEmMemory(this);
				_vEnemy.push_back(wood);
			}
		}

		_timer = 0;
		return;
	}

	// "일단" 개채수가 두마리밑으로 떨어지면
	if (dwSize <= 2) _timer++;
	else if (orcSize <= 2) _timer++;
	else if (woodSize <= 2) _timer++;
}

