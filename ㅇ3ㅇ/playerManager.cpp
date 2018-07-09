#include "stdafx.h"
#include "playerManager.h"
#include "player.h"

//Á¾·ù
#include "gigas.h"
#include "knight.h"
#include "aranzebia.h"
#include "lucius.h"

playerManager::playerManager()
//:_enemyManager(NULL)
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
		setAranzebia(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	}

	//if (KEYMANAGER->isOnceKeyDown('N'))
	//{
	//	setAranzebia(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(5, 0, 0));
	//}

	//if (KEYMANAGER->isOnceKeyDown('B'))
	//{
	//	setLucius(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(10, 0, 0));
	//}


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
	player* _lucius = new lucius;
	_lucius->Init(PLAYER_1P, _T(".\\xFile\\lucius"), _T("lucius.X"));

	_vPlayer.push_back(_lucius);

}

void playerManager::setGigas(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	player* _gigas = new gigas;
	_gigas->Init(PLAYER_1P, _T(".\\xFile\\gigas"), _T("gigas.X"));

	_vPlayer.push_back(_gigas);

}

void playerManager::setAranzebia(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	aranzebia* _aranzebia = new aranzebia;
	_aranzebia->Init(PLAYER_1P, _T(".\\xFile\\aranzebia"), _T("aranzebia.X"));

	_vPlayer.push_back(_aranzebia);

}

void playerManager::setKnight(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	knight* _knight = new knight;
	_knight->Init(PLAYER_1P, _T(".\\xFile\\knight"), _T("knight.X"));


	_vPlayer.push_back(_knight);

}
