#include "stdafx.h"
#include "item_potion.h"


item_potion::item_potion()
{
}


item_potion::~item_potion()
{
}

void item_potion::init(const WCHAR * folder, const WCHAR * file, D3DXVECTOR3 Position)
{
	//���� ��ġ
	_itemMesh = OBJLOADER->load(_T(".\\���ϰ��\\�����̸�.obj"));



	_itemType = POTION;

	_itemEffect = 100;
}

void item_potion::render()
{
}
