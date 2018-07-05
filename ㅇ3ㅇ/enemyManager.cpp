#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

//자식들
#include "darkWolf.h"		//어두운늑대
#include "orcforeMan.h"		//오크_십장
#include "woodGiant.h"		//나무거인

enemyManager::enemyManager()
	: _player(NULL)
	, _stage(0)
	, _timer(9999)
	
{
}


enemyManager::~enemyManager()
{
	for (auto p : _vEnemy)
	{
		SAFE_DELETE(p);
	}

	_vEnemy.clear();
}

void enemyManager::Init()
{
	
}

void enemyManager::Update()
{
	_timer++;

	if (_timer >= 10000)
	{
		_timer = 0;
		CreateEnemy();	
	}
	
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->Update();
	}

}

void enemyManager::Render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->Render();
	}
}

void enemyManager::SetTarget(D3DXVECTOR3* playerPos)
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->SetTarget(playerPos);
	}
}

void enemyManager::ChangeStage(int num)
{
	if (!_vEnemy.empty())
	{
		for (auto p : _vEnemy)
		{
			SAFE_DELETE(p);
		}

		_vEnemy.clear();
	}

	_stage = num;
}

void enemyManager::CreateEnemy()
{
	switch (_stage)
	{
	case 0:
		for (int i = -10; i <= 10; i += 2)
		{
			darkWolf* dw = new darkWolf;
			dw->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"));
			dw->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(i, 0, 0));
			dw->SetSpeed(0.2f);
			_vEnemy.push_back(dw);
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
