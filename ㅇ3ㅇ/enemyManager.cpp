#include "stdafx.h"
#include "enemyManager.h"
#include "enemy.h"

//플레이어 매니저
#include "playerManager.h"
#include "player.h"

//아이템 매니저
#include "itemManager.h"
#include "item.h"

//자식들
#include "darkWolf.h"		//어두운늑대
#include "orcforeMan.h"		//오크_십장
#include "woodGiant.h"		//나무거인
#include "bloodyQueen.h"	//피의여왕
#include "durahan.h"		//머리가 목위에 없는 애
#include "darkLord.h"		//다크로드 얘 보스임
#include "anubis.h"			//아누비스

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
	//CreateMiddleBoss();
	_strongMobAppearCount = 0;
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
	if (KEYMANAGER->isOnceKeyDown('Q')) CreateMiddleBoss();

	for (int i = 0; i < _pm->getVPlayers().size(); i++)
		CreateEnemy(&_pm->getVPlayers()[i]->p->GetPosition());
	
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->SetTarget(_pm);
		_vEnemy[i]->AttackMotionEnd(_pm->getVPlayers()[0]->p, 10.0f, 1.0f, 1.0f);
		_vEnemy[i]->Update();

		if (_vEnemy[i]->GetIsDeadAnimationEnd())
		{
			_vEnemy[i]->SetDisappearCount();

			if (_vEnemy[i]->GetDisappearCount() > 100.0f)
			{
				_strongMobAppearCount++;
				_im->CreateItem(D3DXVECTOR3(_vEnemy[i]->GetPosition().x, _vEnemy[i]->GetPosition().y + 2.0f, _vEnemy[i]->GetPosition().z));
				SAFE_DELETE(_vEnemy[i]);
				_vEnemy.erase(_vEnemy.begin() + i);
				
			}
		}
	}

}

void enemyManager::Render(int size)
{
	float t = TIMEMANAGER->getElapsedTime() / size;

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->Render(t);
	}
}

void enemyManager::ChangeStage(int num)
{
	Release();
	_stage = num;
}

void enemyManager::CreateEnemy(D3DXVECTOR3* target)
{
	D3DXVECTOR3 DarkWolfAreaCenter(40.0f, 3.0f, 40.0f);
	D3DXVECTOR3 BloodyQueenAreaCenter(40.0f, 3.0f, -40.0f);
	D3DXVECTOR3 WoodGiantAreaCenter(-40.0f, 3.0f, 40.0f);
	D3DXVECTOR3 DurahanAreaCenter(-40.0f, 3.0f, -40.0f);


	if (_strongMobAppearCount >= 3)
	{
		int randNum = RND->getFromIntTo(0, 3);
		D3DXVECTOR3 AnubisAreaCenter;

		if (randNum == 0)
			AnubisAreaCenter = D3DXVECTOR3(-40.0f, 3.0f, 0.0f);
		else if (randNum == 1)
			AnubisAreaCenter = D3DXVECTOR3(40.0f, 3.0f, 0.0f);
		else if (randNum == 2)
			AnubisAreaCenter = D3DXVECTOR3(0.0f, 3.0f, 40.0f);
		else
			AnubisAreaCenter = D3DXVECTOR3(0.0f, 3.0f, -40.0f);
		
		D3DXVECTOR3 temp = MakePos(AnubisAreaCenter);
		enemy* anu = new anubis;
		anu->Init(_T(".\\xFile\\enemy\\anubis"), _T("anubis.X"), _stage);
		anu->createContoller(&_cm, _material, 0.5f, 0.5f);
		anu->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), temp);
		anu->SetRespawnPos(AnubisAreaCenter);
		anu->setEmMemory(this);
		_vEnemy.push_back(anu);
			
		_strongMobAppearCount = 0;
	}

	//생성조건
	if (_timer > 100)
	{
		if (target)
		{
			if (WithinArea(DarkWolfAreaCenter, *target, 5.0f))
			{
				D3DXVECTOR3 temp = MakePos(DarkWolfAreaCenter);

				enemy* dw = new darkWolf;
				dw->Init(_T(".\\xFile\\enemy\\DarkWolf"), _T("DarkWolf.X"), _stage);
				dw->createContoller(&_cm, _material, 0.5f, 0.5f);
				dw->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), temp);
				dw->SetRespawnPos(DarkWolfAreaCenter);
				dw->setEmMemory(this);
				_vEnemy.push_back(dw);
			}
			if (WithinArea(BloodyQueenAreaCenter, *target, 5.0f))
			{
				D3DXVECTOR3 temp = MakePos(BloodyQueenAreaCenter);

				enemy* bq = new bloodyQueen;
				bq->Init(_T(".\\xFile\\enemy\\bloodyQueen"), _T("bloodyQueen.X"), _stage);
				bq->createContoller(&_cm, _material, 0.5f, 0.5f);
				bq->SetSRT(D3DXVECTOR3(0.02f, 0.02f, 0.02f), D3DXVECTOR3(0, 0, 1), temp);
				bq->SetRespawnPos(BloodyQueenAreaCenter);
				bq->setEmMemory(this);
				_vEnemy.push_back(bq);
			}
			if (WithinArea(WoodGiantAreaCenter, *target, 5.0f))
			{
				D3DXVECTOR3 temp = MakePos(WoodGiantAreaCenter);

				enemy* wood = new woodGiant;
				wood->Init(_T(".\\xFile\\enemy\\WoodGiant01"), _T("WoodGiant.X"), _stage);
				wood->createContoller(&_cm, _material, 0.5f, 0.5f);
				wood->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), temp);
				wood->SetRespawnPos(WoodGiantAreaCenter);
				wood->setEmMemory(this);
				_vEnemy.push_back(wood);
			}
			if (WithinArea(DurahanAreaCenter, *target, 5.0f))
			{
				D3DXVECTOR3 temp = MakePos(DurahanAreaCenter);

				enemy* dura = new durahan;
				dura->Init(_T(".\\xFile\\enemy\\durahan"), _T("durahan.X"), _stage);
				dura->createContoller(&_cm, _material, 0.5f, 0.5f);
				dura->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), temp);
				dura->SetRespawnPos(DurahanAreaCenter);
				dura->setEmMemory(this);
				_vEnemy.push_back(dura);
			}
		}
		_timer = 0;
		return;
	}

	if (WithinArea(DarkWolfAreaCenter, *target, 10.0f)) _timer++;
	else if (WithinArea(BloodyQueenAreaCenter, *target, 10.0f)) _timer++;
	else if (WithinArea(WoodGiantAreaCenter, *target, 10.0f)) _timer++;
	else if (WithinArea(DurahanAreaCenter, *target, 10.0f)) _timer++;
}

D3DXVECTOR3 enemyManager::MakePos(D3DXVECTOR3 areaCenterPos)
{
	float rndX, rndZ;
	D3DXVECTOR3 answer(0, 0, 0);

	if (_vEnemy.empty())
		return areaCenterPos;

	int loop = 0;

	while (true)
	{
		rndX = RND->getFromFloatTo(-6.0f, 6.0f);
		rndZ = RND->getFromFloatTo(-6.0f, 6.0f);
		D3DXVECTOR3 temp = areaCenterPos + D3DXVECTOR3(rndX, 0, rndZ);

		loop++;
		if (loop > 20)
		{
			return temp;
		}

		int checkNum = 0;

		for (int i = 0; i < _vEnemy.size(); i++)
		{
			if (_vEnemy[i]->WithinEnemyRange(_vEnemy[i]->GetPosition(), temp, 2.0f)) checkNum++;
		}

		if (checkNum == 0)	
			return temp;
	}

	return answer;
}

bool enemyManager::WithinArea(D3DXVECTOR3 areaCenterPos, D3DXVECTOR3 playerPos, float radius)
{
	return ((areaCenterPos.x - radius < playerPos.x && playerPos.x < areaCenterPos.x + radius) && 
			(areaCenterPos.y - radius < playerPos.y && playerPos.y < areaCenterPos.y + radius) &&
			(areaCenterPos.z - radius < playerPos.z && playerPos.z < areaCenterPos.z + radius));
}

void enemyManager::CreateMiddleBoss()
{
	enemy* dakLo = new darkLord;
	dakLo->Init(_T(".\\xFile\\enemy\\darkLord"), _T("darkLord.X"), _stage);
	dakLo->createContoller(&_cm, _material, 0.5f, 0.5f);
	dakLo->SetSRT(D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 3.0f, 0.0f));
	dakLo->SetRespawnPos(dakLo->GetPosition());
	dakLo->setEmMemory(this);
	_vEnemy.push_back(dakLo);
}

bool enemyManager::GetMiddleBoss()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if ((_vEnemy[i]->GetKind() == ENEMY_DARKLORD && _vEnemy[i]->GetIsAppear()))
			return true;
	}

	return false;
}
