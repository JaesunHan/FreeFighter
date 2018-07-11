#include "stdafx.h"
#include "playerManager.h"
#include "player.h"

//����
#include "gigas.h"
#include "knight.h"
#include "aranzebia.h"
#include "lucius.h"
#include "balkiri.h"

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
		setBalkiri();
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

void playerManager::setLucius()
{
	player* _lucius = new lucius;
	_lucius->Init(PLAYER_1P, _T(".\\xFile\\lucius"), _T("lucius.X"));
	_lucius->createContoller(&_cm, _material);
	_lucius->SetSRT(D3DXVECTOR3(0.005f, 0.005f, 0.005f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));


	_vPlayer.push_back(_lucius);

}

void playerManager::setGigas()
{
	player* _gigas = new gigas;
	_gigas->Init(PLAYER_1P, _T(".\\xFile\\gigas"), _T("gigas.X"));
	_gigas->createContoller(&_cm, _material);
	_gigas->SetSRT(D3DXVECTOR3(0.005f, 0.005f, 0.005f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));

	_vPlayer.push_back(_gigas);

}

void playerManager::setAranzebia()
{
	aranzebia* _aranzebia = new aranzebia;
	_aranzebia->Init(PLAYER_1P, _T(".\\xFile\\aranzebia"), _T("aranzebia.X"));
	_aranzebia->createContoller(&_cm, _material);
	_aranzebia->SetSRT(D3DXVECTOR3(0.005f, 0.005f, 0.005f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));


	_vPlayer.push_back(_aranzebia);

}

void playerManager::setKnight()
{
	knight* _knight = new knight;
	_knight->Init(PLAYER_1P, _T(".\\xFile\\knight"), _T("knight.X"));
	_knight->createContoller(&_cm, _material);
	_knight->SetSRT(D3DXVECTOR3(0.005f, 0.005f, 0.005f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));



	_vPlayer.push_back(_knight);

}

void playerManager::setBalkiri()
{
	player* _balkiri = new gigas;
	_balkiri->Init(PLAYER_1P, _T(".\\xFile\\balkiri"), _T("balkiri.X"));
	_balkiri->createContoller(&_cm, _material);
	_balkiri->SetSRT(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));

	_vPlayer.push_back(_balkiri);
}
