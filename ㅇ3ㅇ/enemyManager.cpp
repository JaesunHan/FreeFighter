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
#include "woodGiant.h"		//나무거인
#include "bloodyQueen.h"	//피의여왕
#include "durahan.h"		//머리가 목위에 없는 애
#include "darkLord.h"		//다크로드 얘 중간보스임
#include "anubis.h"			//아누비스
#include "mudGolem.h"		//진흙골렘
#include "zaken.h"			//자켄
#include "kerberos.h"		//수문장
#include "gargoyle.h"		//가고일 (보스)

//fight
#include "fightFepee.h"
#include "fightReper.h"
#include "fightWoodGiant.h"
#include "fightZealot.h"

enemyManager::enemyManager()
	: _stage(0)
	, _timer(0)
{
}


enemyManager::~enemyManager()
{
	Release();
}

void enemyManager::Init(int Mode , int size)
{
	_strongMobAppearCount = 0;
	_middleBossAppearCount = 0;

	if (Mode == 0)
		_gm = EM_GAME_STORY;
	else
		_gm = EM_GAME_BATTLE;

	if (_gm == EM_GAME_BATTLE && size == 1)
		CreateFightEnemy();
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
	//스토리
	if (_gm == EM_GAME_STORY)
	{
		for (int i = 0; i < _pm->getVPlayers().size(); i++)
		{
			CreateEnemy(&_pm->getVPlayers()[i]->p->GetPosition());
		}

		for (int i = 0; i < _vEnemy.size(); i++)
		{
			_vEnemy[i]->SetTarget(_pm);

			//데미지 체크
			for (int j = 0; j < _pm->getVPlayers().size(); j++)
			{
				_vEnemy[i]->HitCheck(_pm->getVPlayers()[j]->p,
					_vEnemy[i]->GetStatus().atkDmg,
					_vEnemy[i]->GetAtkDistance(),
					_vEnemy[i]->GetHitRange(),
					_vEnemy[i]->GetAttackAniRate());
			}
			_vEnemy[i]->SetOneHit();

			_vEnemy[i]->Update();

			//죽는 부분
			if (_vEnemy[i]->GetIsDeadAnimationEnd())
			{
				_vEnemy[i]->SetDisappearCount();

				if (_vEnemy[i]->GetDisappearCount() > 100.0f)
				{
					_strongMobAppearCount++;
					_middleBossAppearCount++;

					int rnd = RND->getFromIntTo(1, 100);
					int rndNum;

					if (rnd < 50)
						rndNum = 1;
					else
						rndNum = 5;			

					if (_vEnemy[i]->GetKind() == ENEMY_ANUBIS ||
						_vEnemy[i]->GetKind() == ENEMY_MUDGOLEM ||
						_vEnemy[i]->GetKind() == ENEMY_MUDGOLEM)
					{
						rnd = RND->getFromIntTo(1, 90);
						if (rnd < 40)
							rndNum = 5;		//꽝
						else if (rnd < 50)
							rndNum = 4;		//방어력증가
						else if (rnd < 60)
							rndNum = 3;		//이속증가
						else if (rnd < 70)
							rndNum = 2;		//데미지증가
						else if (rnd < 80)
							rndNum = 1;		//골드
						else
							rndNum = 0;		//꽝
					}
						
					_im->CreateItem(D3DXVECTOR3(_vEnemy[i]->GetPosition().x, _vEnemy[i]->GetPosition().y + 1.5f, _vEnemy[i]->GetPosition().z), rndNum);
					SAFE_DELETE(_vEnemy[i]);
					_vEnemy.erase(_vEnemy.begin() + i);

				}
			}
		}
	}
	//배틀
	else if (_gm == EM_GAME_BATTLE)
	{
		for (int i = 0; i < _vEnemy.size(); i++)
		{
			_vEnemy[i]->SetTarget(_pm);

			//데미지 체크
			for (int j = 0; j < _pm->getVPlayers().size(); j++)
			{
				_vEnemy[i]->HitCheck(_pm->getVPlayers()[j]->p,
					_vEnemy[i]->GetStatus().atkDmg,
					_vEnemy[i]->GetAtkDistance(),
					_vEnemy[i]->GetHitRange(),
					_vEnemy[i]->GetAttackAniRate());
			}
			_vEnemy[i]->SetOneHit();

			_vEnemy[i]->Update();

			if (_vEnemy[i]->GetIsDeadAnimationEnd())
			{
				_vEnemy[i]->SetDisappearCount();

				if (_vEnemy[i]->GetDisappearCount() > 100.0f)
				{
					SAFE_DELETE(_vEnemy[i]);
					_vEnemy.erase(_vEnemy.begin() + i);
				}
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

void enemyManager::CreateFightEnemy()
{
	int rndNum = 1;

	if (rndNum == 0)
	{
		enemy* zealot = new fightZealot;
		zealot->Init(_T(".\\xFile\\zealot"), _T(".\\zealot.X"), 0);
		zealot->createContoller(&_cm, _material, 1.0f, 1.0f);
		zealot->SetSRT(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 0.01f, 0));

		_vEnemy.push_back(zealot);
	}
	if (rndNum == 1)
	{
		enemy* reper = new fightReper;
		reper->Init(_T(".\\xFile\\reaper"), _T(".\\reaper.X"), 0);
		reper->createContoller(&_cm, _material, 1.0f, 1.0f);
		reper->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 0.01f, 0));

		_vEnemy.push_back(reper);
	}
	if (rndNum == 2)
	{
		enemy* fepee = new fightFepee;
		fepee->Init(_T(".\\xFile\\fepee"), _T(".\\fepee.X"), 0);
		fepee->createContoller(&_cm, _material, 1.0f, 1.0f);
		fepee->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 0.01f, 0));

		_vEnemy.push_back(fepee);
	}
	if (rndNum == 3)
	{
		enemy* wg = new fightWoodGiant;
		wg->Init(_T(".\\xFile\\woodGiant"), _T(".\\woodGiant.X"), 0);
		wg->createContoller(&_cm, _material, 1.0f, 1.0f);
		wg->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 0.01f, 0));

		_vEnemy.push_back(wg);
	}
}

void enemyManager::CreateEnemy(D3DXVECTOR3* target)
{
	D3DXVECTOR3 DarkWolfAreaCenter(40.0f, 3.0f, 40.0f);
	D3DXVECTOR3 BloodyQueenAreaCenter(40.0f, 3.0f, -40.0f);
	D3DXVECTOR3 WoodGiantAreaCenter(-40.0f, 3.0f, 40.0f);
	D3DXVECTOR3 DurahanAreaCenter(-40.0f, 3.0f, -40.0f);

	int dwNum = 0;
	int bqNum = 0;
	int wgNum = 0;
	int duraNum = 0;
	int strongMob = 0;

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (_vEnemy[i]->GetKind() == ENEMY_DARKWOLF)			dwNum++;
		if (_vEnemy[i]->GetKind() == ENEMY_BLOODYQUEEN)			bqNum++;
		if (_vEnemy[i]->GetKind() == ENEMY_WOODGIANT)			wgNum++;
		if (_vEnemy[i]->GetKind() == ENEMY_DURAHAN)				duraNum++;

		if (_vEnemy[i]->GetKind() == ENEMY_ANUBIS)				strongMob++;
		if (_vEnemy[i]->GetKind() == ENEMY_MUDGOLEM)			strongMob++;
		if (_vEnemy[i]->GetKind() == ENEMY_ZAKEN)				strongMob++;
	}

	static bool oneAppear = false;

	if (_middleBossAppearCount >= 10 && !oneAppear)
	{
		CreateMiddleBoss();
		_middleBossAppearCount = 0;
		oneAppear = true;
	}
	
	//쌘몹
	if (_strongMobAppearCount >= 8 && strongMob <= ENEMY_FULL + 5)
	{
		int randPlace = RND->getFromIntTo(0, 3);
		D3DXVECTOR3 RandomAreaCenter;

		if (randPlace == 0)
			RandomAreaCenter = D3DXVECTOR3(-40.0f, 3.0f, 0.0f);
		else if (randPlace == 1)
			RandomAreaCenter = D3DXVECTOR3(40.0f, 3.0f, 0.0f);
		else if (randPlace == 2)
			RandomAreaCenter = D3DXVECTOR3(0.0f, 3.0f, 40.0f);
		else
			RandomAreaCenter = D3DXVECTOR3(0.0f, 3.0f, -40.0f);

		int randMob = RND->getFromIntTo(0, 2);

		D3DXVECTOR3 randPos = MakePos(RandomAreaCenter);
		
		if (randMob == 0)
		{	
			enemy* anu = new anubis;
			anu->Init(_T(".\\xFile\\enemy\\anubis"), _T("anubis.X"), _stage);
			anu->createContoller(&_cm, _material, 1.0f, 1.0f);
			anu->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), randPos);
			anu->SetRespawnPos(RandomAreaCenter);
			anu->setEmMemory(this);
			_vEnemy.push_back(anu);
		}
		else if (randMob == 1)
		{
			enemy* golem = new mudGolem;
			golem->Init(_T(".\\xFile\\enemy\\mudGolem"), _T("mudGolem.X"), _stage);
			golem->createContoller(&_cm, _material, 1.0f, 1.0f);
			golem->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), randPos);
			golem->SetRespawnPos(RandomAreaCenter);
			golem->setEmMemory(this);
			_vEnemy.push_back(golem);
		}
		else if (randMob == 2)
		{
			enemy* zak = new zaken;
			zak->Init(_T(".\\xFile\\enemy\\zaken"), _T("zaken.X"), _stage);
			zak->createContoller(&_cm, _material, 1.0f, 1.0f);
			zak->SetSRT(D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(0, 0, 1), randPos);
			zak->SetRespawnPos(RandomAreaCenter);
			zak->setEmMemory(this);
			_vEnemy.push_back(zak);
		}
		_strongMobAppearCount = 0;
	}

	//생성조건
	if (_timer > 100)
	{
		if (target)
		{
			if (WithinArea(DarkWolfAreaCenter, *target, 10.0f) && dwNum <= ENEMY_FULL)
			{
				D3DXVECTOR3 temp = MakePos(DarkWolfAreaCenter);

				enemy* dw = new darkWolf;
				dw->Init(_T(".\\xFile\\enemy\\darkWolf"), _T("darkWolf.X"), _stage);
				dw->createContoller(&_cm, _material, 0.7f, 0.7f);
				dw->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), temp);
				dw->SetRespawnPos(DarkWolfAreaCenter);
				dw->setEmMemory(this);
				_vEnemy.push_back(dw);
			}
			if (WithinArea(BloodyQueenAreaCenter, *target, 10.0f) && bqNum <= ENEMY_FULL)
			{
				D3DXVECTOR3 temp = MakePos(BloodyQueenAreaCenter);

				enemy* bq = new bloodyQueen;
				bq->Init(_T(".\\xFile\\enemy\\bloodyQueen"), _T("bloodyQueen.X"), _stage);
				bq->createContoller(&_cm, _material, 0.6f, 0.6f);
				bq->SetSRT(D3DXVECTOR3(0.02f, 0.02f, 0.02f), D3DXVECTOR3(0, 0, 1), temp);
				bq->SetRespawnPos(BloodyQueenAreaCenter);
				bq->setEmMemory(this);
				_vEnemy.push_back(bq);
			}
			if (WithinArea(WoodGiantAreaCenter, *target, 10.0f) && wgNum <= ENEMY_FULL)
			{
				D3DXVECTOR3 temp = MakePos(WoodGiantAreaCenter);

				enemy* wood = new woodGiant;
				wood->Init(_T(".\\xFile\\enemy\\woodGiant"), _T("woodGiant.X"), _stage);
				wood->createContoller(&_cm, _material, 1.0f, 1.0f);
				wood->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), temp);
				wood->SetRespawnPos(WoodGiantAreaCenter);
				wood->setEmMemory(this);
				_vEnemy.push_back(wood);
			}
			if (WithinArea(DurahanAreaCenter, *target, 10.0f) && duraNum <= ENEMY_FULL)
			{
				D3DXVECTOR3 temp = MakePos(DurahanAreaCenter);

				enemy* dura = new durahan;
				dura->Init(_T(".\\xFile\\enemy\\durahan"), _T("durahan.X"), _stage);
				dura->createContoller(&_cm, _material, 1.0f, 1.0f);
				dura->SetSRT(D3DXVECTOR3(0.015f, 0.015f, 0.015f), D3DXVECTOR3(0, 0, 1), temp);
				dura->SetRespawnPos(DurahanAreaCenter);
				dura->setEmMemory(this);
				_vEnemy.push_back(dura);
			}
		}

		_timer = 0;
	}

	if (WithinArea(DarkWolfAreaCenter, *target, 15.0f)) _timer++;
	else if (WithinArea(BloodyQueenAreaCenter, *target, 15.0f)) _timer++;
	else if (WithinArea(WoodGiantAreaCenter, *target, 15.0f)) _timer++;
	else if (WithinArea(DurahanAreaCenter, *target, 15.0f)) _timer++;
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
			if (_vEnemy[i]->BetweenEnemyDistance(_vEnemy[i]->GetPosition(), temp, 2.0f)) checkNum++;
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

void enemyManager::CreatKerberos()
{
	enemy* ker = new kerberos;
	ker->Init(_T(".\\xFile\\enemy\\kerberos"), _T("kerberos.X"), _stage);
	ker->createContoller(&_cm, _material, 1.0f, 1.0f);
	ker->SetSRT(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 3.0f, 0.0f));
	ker->SetRespawnPos(ker->GetPosition());
	ker->setEmMemory(this);
	_vEnemy.push_back(ker);
}

void enemyManager::CreateMiddleBoss()
{
	enemy* dakLo = new darkLord;
	dakLo->Init(_T(".\\xFile\\enemy\\darkLord"), _T("darkLord.X"), _stage);
	dakLo->createContoller(&_cm, _material, 1.0f, 1.0f);
	dakLo->SetSRT(D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 3.0f, 0.0f));
	dakLo->SetRespawnPos(dakLo->GetPosition());
	dakLo->setEmMemory(this);
	_vEnemy.push_back(dakLo);
}

void enemyManager::CreateBoss()
{
	enemy* gargo = new gargoyle;
	gargo->Init(_T(".\\xFile\\enemy\\gargoyle"), _T("gargoyle.X"), _stage);
	gargo->createContoller(&_cm, _material, 1.0f, 1.0f);
	gargo->SetSRT(D3DXVECTOR3(0.025f, 0.025f, 0.025f), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 3.0f, 0.0f));
	gargo->SetRespawnPos(gargo->GetPosition());
	gargo->setEmMemory(this);
	_vEnemy.push_back(gargo);
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
