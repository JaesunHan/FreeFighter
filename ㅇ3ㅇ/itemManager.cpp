//�Ŵ������� ������Ű�°� ��´�

#include "stdafx.h"
#include "itemManager.h"
#include "item.h"

//������ ���� �׳��� ���ؼ�...
#include "playerManager.h"
#include "player.h"

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
	CreateItem();
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

void itemManager::CreateItem()
{
	item*potion = new item_potion;
	potion->init(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	_vItem.push_back(potion);
}
