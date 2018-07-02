#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

enemyManager::enemyManager()
	: _player(NULL)
	, _stage(0)
	
{
}


enemyManager::~enemyManager()
{
}

void enemyManager::Init()
{
}

void enemyManager::Update()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->Update();
		_vEnemy[i]->SetTarget(NULL);
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
	if (!_vEnemy.empty()) _vEnemy.clear();

	_stage = num;

	switch (_stage)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

