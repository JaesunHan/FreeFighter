#include "stdafx.h"
#include "item_gold.h"


item_gold::item_gold()
{
}


item_gold::~item_gold()
{
}

void item_gold::init(const WCHAR * folder, const WCHAR * file, D3DXVECTOR3 Position, float gold)
{
	//파일 위치
	WCHAR strFileName[1024];
	swprintf(strFileName, _T(".\\%obj\\%box.obj"), folder, file);

	_itemMesh = OBJLOADER->loadMesh(_vecItemMtlData, strFileName);

	_itemType = GOLD;

	_itemEffect = gold;

	
}

void item_gold::render()
{

}
