#include "stdafx.h"
#include "aStar.h"
#include "naviMesh.h"


aStar::aStar()
	: _nearDis(0)
{
}


aStar::~aStar()
{
}

void aStar::MakeHeap(D3DXVECTOR3* start, D3DXVECTOR3* target)
{
	//자신이 서 있는 Cell과 상대가 서 있는 Cell을 구해야함


}

void aStar::PathFinder()
{
}

void aStar::Init()
{
	_naviMesh = new naviMesh;
}

void aStar::Release()
{
}

void aStar::Update()
{
}

void aStar::Render()
{
}
