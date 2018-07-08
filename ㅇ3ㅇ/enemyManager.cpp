#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

//�ڽĵ�
#include "darkWolf.h"		//��ο����
#include "orcforeMan.h"		//��ũ_����
#include "woodGiant.h"		//��������


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
	
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->SetTarget(&_tc->GetPos());
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
