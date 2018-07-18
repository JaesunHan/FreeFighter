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
}

void itemManager::Render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}

//예이~
void itemManager::CreateItem(D3DXVECTOR3 tra)
{
	//랜덤수치를 돌릴꺼에요!!
	//0이면 포션이고, 1이면 골드애오
	//2가 나오면 꽝이에오!
	int itemRandom;
	itemRandom = rand() % 2;

	if (itemRandom == 0)
	{
		item*potion = new item_potion;
		potion->init(D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(0, 0, 0), tra);

		_vItem.push_back(potion);
	}

	else if (itemRandom == 1)
	{
		item*gold = new item_gold;
		gold->init(D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(0, 0, 0), tra);

		_vItem.push_back(gold);
	}

	else if (itemRandom == 2)
	{
		
	}
}
