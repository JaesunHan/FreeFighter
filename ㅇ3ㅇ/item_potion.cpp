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
	//파일 위치
	WCHAR strFileName[1024];
	swprintf(strFileName, _T(".\\%obj\\%box.obj"), folder, file);

	_itemMesh = OBJLOADER->loadMesh(_vecItemMtlData, strFileName);

	_itemType = POTION;

	_itemEffect = 50;
}

void item_potion::render()
{
}
