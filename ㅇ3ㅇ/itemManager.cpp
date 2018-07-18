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

	CreateItem();
}

void itemManager::Render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}

//����~
void itemManager::CreateItem()
{
	for (int i = 0; i < _em->GetEnemy().size(); i++)
	{
		if (_em->GetEnemy()[i]->GetIsDead())
		{
			item*potion = new item_potion;
			potion->init(D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(0, 0, 0), _em->GetEnemy()[i]->GetPosition() + D3DXVECTOR3(0, 1, 0));

			_vItem.push_back(potion);
		}
	}
}
