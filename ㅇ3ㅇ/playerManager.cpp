#include "stdafx.h"
#include "playerManager.h"
#include "player.h"

//Á¾·ù
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

