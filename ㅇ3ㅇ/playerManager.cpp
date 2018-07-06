#include "stdafx.h"
#include "playerManager.h"
#include "player.h"




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
	player*	temp;
	temp = new knight;


}

void playerManager::setGigas(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	player*	temp;
	temp = new lucius;
}

void playerManager::setAranzebia(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	player*	temp;
	temp = new gigas;
}

void playerManager::setKnight(D3DXVECTOR3 scale, D3DXVECTOR3 position)
{
	player*	temp;
	temp = new aranzebia;
}

