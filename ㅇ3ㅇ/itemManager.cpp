#include "stdafx.h"
#include "itemManager.h"
#include "item.h"


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
