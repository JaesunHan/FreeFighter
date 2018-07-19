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
}

void itemManager::Render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}

//����~
void itemManager::CreateItem(D3DXVECTOR3 tra)
{
	//������ġ�� ����������!!
	//0�̸� �����̰�, 1�̸� ���ֿ�
	//2�� ������  ���������ֿ�
	//3�� ������ �̼ӹ����̿���
	//4�� ������ ���̿���!

	int itemRandom;
	itemRandom = rand() % 4;

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
		item*damage = new item_damage;
		damage->init(D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0, 0), tra);

		_vItem.push_back(damage);
	}

	else if (itemRandom == 3)
	{
		item*speed = new item_speed;
		speed->init(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0, 0, 0), tra);

		_vItem.push_back(speed);
	}

	else if (itemRandom == 4)
	{

	}
}
