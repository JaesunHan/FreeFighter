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
	_itemMesh = OBJLOADER->load(_T(".\\파일경로\\파일이름.obj"));


	_itemType = GOLD;

	_itemEffect = gold;


	
}

void item_gold::render()
{

}
