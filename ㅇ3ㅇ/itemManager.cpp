//매니저에선 생성시키는걸 삼는다

#include "stdafx.h"
#include "itemManager.h"
#include "item.h"

//언젠가 쓰일 그날을 위해서...
#include "playerManager.h"
#include "player.h"
//언젠가...
#include "enemyManager.h"
#include "enemy.h"

//아이템 종류
#include "item_gold.h"
#include "item_potion.h"
#include "item_damage.h"
#include "item_speed.h"
#include "item_defence.h"

itemManager::itemManager()
{
}


itemManager::~itemManager()
{
	for (auto p : _vItem)
	{
		SAFE_DELETE(p);
	}
	_vItem.clear();
}

void itemManager::Init()
{
}

void itemManager::Update()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();
	}

	TestCreate();
}

void itemManager::Render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}


//예이~
void itemManager::CreateItem(D3DXVECTOR3 pos, int itemNum)
{
	//0 =포션
	//1 =골드
	//2 =뎀증
	//3 =이속증
	//4 =방어증
	//5 =리턴증

	//int itemRandom;
	//itemRandom = rand() % 4;

	if (itemNum == 0)
	{
		item*potion = new item_potion;
		potion->init(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(potion);
	}

	else if (itemNum == 1)
	{
		item*gold = new item_gold;
		gold->init(D3DXVECTOR3(0.02f, 0.02f, 0.02f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(gold);
	}

	else if (itemNum == 2)
	{
		item*damage = new item_damage;
		damage->init(D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(damage);
	}

	else if (itemNum == 3)
	{
		item*speed = new item_speed;
		speed->init(D3DXVECTOR3(0.02f, 0.02f, 0.02f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(speed);
	}

	else if (itemNum == 4)
	{
		item*defence = new item_defence;
		defence->init(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(defence);
	}

	else if (itemNum == 5) return;

}

void itemManager::TestCreate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
	{
		item*potion = new item_potion;
		potion->init(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 0));

		_vItem.push_back(potion);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		item*gold = new item_gold;
		gold->init(D3DXVECTOR3(0.02f, 0.02f, 0.02f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 0));

		_vItem.push_back(gold);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		item*damage = new item_damage;
		damage->init(D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 0));

		_vItem.push_back(damage);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		item*speed = new item_speed;
		speed->init(D3DXVECTOR3(0.02f, 0.02f, 0.02f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 0));

		_vItem.push_back(speed);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		item*defence = new item_defence;
		defence->init(D3DXVECTOR3(0.008f, 0.008f, 0.008f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 0));

		_vItem.push_back(defence);
	}
}
