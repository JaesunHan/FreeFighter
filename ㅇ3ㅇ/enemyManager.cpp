#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

//자식들
#include "darkWolf.h"		//어두운늑대
#include "orcforeMan.h"		//오크_십장
#include "woodGiant01.h"	//나무거인01

enemyManager::enemyManager()
	: _player(NULL)
	, _stage(0)
	
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
	if (!_vEnemy.empty()) _vEnemy.clear();

	_stage = num;

	switch (_stage)
	{
	case 0:
		for (int i = -3 ; i <= 3; i += 3)
		{
			enemy* wolf = new darkWolf(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(i, 0, 5));
			wolf->Init(_T(".\\xFiles\\enemy\\darkWolf"), _T("darkWolf.X"));
			_vEnemy.push_back(wolf);
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