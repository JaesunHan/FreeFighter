#include "stdafx.h"
#include "playerManager.h"
#include "playableCharacter.h"
#include "camera.h"


playerManager::playerManager()
{
}

playerManager::~playerManager()
{
}

HRESULT playerManager::init(GAME_MODE gameMode, PLAYER_MODE playerMode, vector<PLAYABLE_CHARACTER> vPlayerSelected, PxControllerManager** cm, PxMaterial* m)
{
	// �Ѿ�� ���� ���� �÷��̾� ���� ���� �÷��̾� ����
	_vPlayers.resize(playerMode + 1);
	for (int i = 0; i < _vPlayers.size(); ++i)
	{
		_vPlayers[i] = new tagPlayer;

		switch (vPlayerSelected[i])
		{
			case CHAR_ZEALOT:
				_vPlayers[i]->p = new zealot;
				_vPlayers[i]->p->Init((PLAYERS)i, CHAR_ZEALOT, _T(".\\xFile\\zealot"), _T("zealot.X"));
			break;

			case CHAR_REAPER:
				_vPlayers[i]->p = new reaper;
				_vPlayers[i]->p->Init((PLAYERS)i, CHAR_REAPER, _T(".\\xFile\\reaper"), _T("reaper.X"));
			break;

			case CHAR_WOODGIANT:
				_vPlayers[i]->p = new woodGiantPlayer;
				_vPlayers[i]->p->Init((PLAYERS)i, CHAR_WOODGIANT, _T(".\\xFile\\woodGiant"), _T("woodGiant.X"));
			break;

			case CHAR_FEPEE:
				_vPlayers[i]->p = new fepee;
				_vPlayers[i]->p->Init((PLAYERS)i, CHAR_FEPEE, _T(".\\xFile\\fepee"), _T("fepee.X"));
			break;
		}

		_vPlayers[i]->p->statusInit(gameMode);
		_vPlayers[i]->p->createContoller(cm, m, 0.5f, 0.5f);

		_vPlayers[i]->cam = new camera;
		_vPlayers[i]->cam->init();
	}

	// ����Ʈ ������
	if (playerMode == PMODE_PLAYER1)
		D3DDEVICE->GetViewport(&_vPlayers[0]->vp);
	else if (playerMode == PMODE_PLAYER2)
	{
		D3DVIEWPORT9 origin;
		D3DDEVICE->GetViewport(&origin);

		// player1�� ����Ʈ
		_vPlayers[0]->vp = origin;
		_vPlayers[0]->vp.X = origin.X;
		_vPlayers[0]->vp.Y = origin.Y;
		_vPlayers[0]->vp.Width = origin.Width / 2;
		_vPlayers[0]->vp.Height = origin.Height;

		// player2�� ����Ʈ
		_vPlayers[1]->vp = origin;
		_vPlayers[1]->vp.X = origin.X + origin.Width / 2;
		_vPlayers[1]->vp.Y = origin.Y;
		_vPlayers[1]->vp.Width = origin.Width / 2;
		_vPlayers[1]->vp.Height = origin.Height;
	}

	// �ʱ� ��ġ ����ֱ�
	this->playerPositionInit(gameMode, playerMode);

	return S_OK;
}

void playerManager::playerPositionInit(GAME_MODE gameMode, PLAYER_MODE playerMode)
{
	float startY = 3.1f;
	if (playerMode == PMODE_PLAYER1)
		_vPlayers[0]->p->SetPosition(D3DXVECTOR3(0.0f, startY, -2.0f));
	else if (playerMode == PMODE_PLAYER2)
	{
		if (gameMode == GAME_STORY)
		{
			for (int i = 0; i < _vPlayers.size(); ++i)
				_vPlayers[i]->p->SetPosition(D3DXVECTOR3(-1.0f + 2.0f * i, startY, -2.0f));
		}
		else if (gameMode == GAME_FIGHT)
		{
			for (int i = 0; i < _vPlayers.size(); ++i)
			{
				_vPlayers[i]->p->SetPosition(D3DXVECTOR3(0.0f, startY, -2.0f + 4.0f * i));
				_vPlayers[i]->p->SetDir(D3DXVECTOR3(0.0f, startY, 1.0f - 2.0f * i));
			}
		}
	}
}

void playerManager::release()
{
	for (int i = 0; i < _vPlayers.size(); ++i)
	{
		SAFE_OBJRELEASE(_vPlayers[i]->p);
		SAFE_OBJRELEASE(_vPlayers[i]->cam);
		SAFE_DELETE(_vPlayers[i]);
	}
	_vPlayers.clear();
}

void playerManager::update()
{
	for (int i = 0; i < _vPlayers.size(); ++i)
		_vPlayers[i]->p->Update();
}

void playerManager::render(int index)
{
	this->setViewPort(index);
	// �������� ��Ʈ������ ���⼭ ����� ������ �������� ��Ʈ������ ����Ʈ�� ������ �ޱ� ����
	// �������� ��Ʈ���� ����
	float width = _vPlayers[index]->vp.Width;
	float height = _vPlayers[index]->vp.Height;
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection,
		D3DX_PI / 4.0f,					// �þ� ��
		width / height,					// ȭ�� ����(���� / ����)
		0.1f,							// ȭ�鿡 ���� ����� z��
		1000.0f);						// ȭ�鿡 ���� �� z��

	// ���� ��Ʈ������ ����̽��� ����
	D3DDEVICE->SetTransform(D3DTS_PROJECTION, &projection);

	// ī�޶� ������Ʈ�� ����� ����
	if (!_isDebug)
	{
		if (_vPlayers[index]->cam)
			_vPlayers[index]->cam->update(&_vPlayers[index]->p->GetPosition(), &_vPlayers[index]->p->GetDir());
	}
	
	float t = TIMEMANAGER->getElapsedTime() / _vPlayers.size();
	for (int i = 0; i < _vPlayers.size(); ++i)
		_vPlayers[i]->p->Render(t);
}

void playerManager::renderParticle()
{
	float t = TIMEMANAGER->getElapsedTime() / _vPlayers.size();
	for (int i = 0; i < _vPlayers.size(); ++i)
		_vPlayers[i]->p->RenderParticle();
}

void playerManager::renderUi(int index)
{
	for (int i = 0; i < _vPlayers.size(); ++i)
		_vPlayers[i]->p->RenderUi(_vPlayers[i]->vp, (index == i));
}

void playerManager::setEMMemory(enemyManager * em)
{
	for (auto i : _vPlayers)
		i->p->setEMMemory(em);
}
