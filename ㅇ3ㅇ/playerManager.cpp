#include "stdafx.h"
#include "playerManager.h"
#include "player.h"


#include "gigas.h"
#include "knight.h"
#include "aranzebia.h"
#include "lucius.h"

playerManager::playerManager()
	:_enemy(NULL)
{
}


playerManager::~playerManager()
{
	for (auto p : _vPlayer)
	{
		SAFE_DELETE(p);
	}

	_vPlayer.clear();
}

void playerManager::Init()
{

}

void playerManager::Update()
{
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		setGigas(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0));
	}


	for (int i = 0; i < _vPlayer.size(); i++)
	{
		_vPlayer[i]->Update();
	}


}

void playerManager::Render()
{
	for (int i = 0; i < _vPlayer.size(); i++)
	{
		_vPlayer[i]->Render();
	}
}

void playerManager::setLucius(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	lucius* _lucius = new lucius;
	_lucius->Init(_T(".\\xFile\\lucius"), _T("lucius.X"));

	_vPlayer.push_back(_lucius);

}

void playerManager::setGigas(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	gigas* _gigas = new gigas;
	_gigas->Init(_T(".\\xFile\\gigas"), _T("gigas.X"));
	_gigas->movement();

	_vPlayer.push_back(_gigas);

}

void playerManager::setAranzebia(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	aranzebia* _aranzebia = new aranzebia;
	_aranzebia->Init(_T(".\\xFile\\_aranzebia"), _T("_aranzebia.X"));

	_vPlayer.push_back(_aranzebia);

}

void playerManager::setKnight(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	knight* _knight = new knight;
	_knight->Init(_T(".\\xFile\\knight"), _T("knight.X"));


	_vPlayer.push_back(_knight);

}
