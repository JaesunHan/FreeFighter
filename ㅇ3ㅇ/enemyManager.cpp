#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

//자식들
#include "darkWolf.h"		//어두운늑대
#include "orcforeMan.h"		//오크_십장
#include "woodGiant.h"		//나무거인


#include "testCube.h"

enemyManager::enemyManager()
	: 
	_stage(0)
	, _timer(0)
	, _testTarget(15.0f, 0.0f, 0.0f)
	
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
	CreateEnemy();
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

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->SetIsCollisionCheak(false);
		_vEnemy[i]->SetTarget(&_tc->GetPos());
	}

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->Update();
		
		for (int j = 0; j < _vEnemy.size(); j++)
		{
			if (_vEnemy[i] == _vEnemy[j]) continue;

			//충돌했다
			if (enemy::YouAndIDistance(_vEnemy[i]->GetPosition(), _vEnemy[j]->GetPosition()) <= 1.5f)
			{
				enemy* temp = enemy::Collision(&_tc->GetPos(), _vEnemy[i], _vEnemy[j]);

				if (!temp) continue;

				if (temp == _vEnemy[i])
				{
					temp->SetIsCollisionCheak(true);
					break;
				}
			}
		}

		if (!_vEnemy[i]->GetIsCollision())
			_vEnemy[i]->Moving();
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
	{
		for (int i = -5; i <= 5; i++)
		{
			enemy* dw = new darkWolf;
			dw->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"));
			dw->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(i, 0, 5));
			dw->SetSpeed(0.05f);
			dw->createContoller(&_cm, _material);
			_vEnemy.push_back(dw);
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
