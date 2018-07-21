//�Ŵ������� ������Ű�°� ��´�

#include "stdafx.h"
#include "itemManager.h"
#include "item.h"

//������ ���� �׳��� ���ؼ�...
#include "playerManager.h"
#include "player.h"
//������...
#include "enemyManager.h"
#include "enemy.h"

//������ ����
#include "item_gold.h"
#include "item_potion.h"
#include "item_damage.h"
#include "item_speed.h"

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


//����~
void itemManager::CreateItem(D3DXVECTOR3 pos, int itemNum)
{
	//������ġ�� ����������!!
	//0�̸� �����̰�, 1�̸� ���ֿ�
	//2�� ������  ���������ֿ�
	//3�� ������ �̼ӹ����̿���
	//4�� ������ ���̿���!

	//int itemRandom;
	//itemRandom = rand() % 4;

	if (itemNum == 0)
	{
		item*potion = new item_potion;
		potion->init(D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(potion);
	}

	else if (itemNum == 1)
	{
		item*gold = new item_gold;
		gold->init(D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(gold);
	}

	else if (itemNum == 2)
	{
		item*damage = new item_damage;
		damage->init(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(damage);
	}

	else if (itemNum == 3)
	{
		item*speed = new item_speed;
		speed->init(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0, 0, 0), pos);

		_vItem.push_back(speed);
	}

	else if (itemNum == 4) return;

}

void itemManager::TestCreate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
	{
		item*potion = new item_potion;
		potion->init(D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 0));

		_vItem.push_back(potion);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		item*gold = new item_gold;
		gold->init(D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 2));

		_vItem.push_back(gold);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		item*damage = new item_damage;
		damage->init(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 4));

		_vItem.push_back(damage);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		item*speed = new item_speed;
		speed->init(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 5, 6));

		_vItem.push_back(speed);
	}
}
