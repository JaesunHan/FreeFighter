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
	// 넘어온 게임 모드와 플레이어 수에 따라 플레이어 생성
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
				_vPlayers[i]->p->Init((PLAYERS)i, CHAR_REAPER, _T(".\\xFile\\reaper"), _T("reaper.X"));
			break;

			case CHAR_WOODGIANT:
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

	// 뷰포트 나누기
	if (playerMode == PMODE_PLAYER1)
		D3DDEVICE->GetViewport(&_vPlayers[0]->vp);
	else if (playerMode == PMODE_PLAYER2)
	{
		D3DVIEWPORT9 origin;
		D3DDEVICE->GetViewport(&origin);

		// player1의 뷰포트
		_vPlayers[0]->vp = origin;
		_vPlayers[0]->vp.X = origin.X;
		_vPlayers[0]->vp.Y = origin.Y;
		_vPlayers[0]->vp.Width = origin.Width / 2;
		_vPlayers[0]->vp.Height = origin.Height;

		// player2의 뷰포트
		_vPlayers[1]->vp = origin;
		_vPlayers[1]->vp.X = origin.X + origin.Width / 2;
		_vPlayers[1]->vp.Y = origin.Y;
		_vPlayers[1]->vp.Width = origin.Width / 2;
		_vPlayers[1]->vp.Height = origin.Height;
	}

	// 초기 위치 잡아주기
	this->playerPositionInit(gameMode, playerMode);

	return S_OK;
}

void playerManager::playerPositionInit(GAME_MODE gameMode, PLAYER_MODE playerMode)
{
	float startY = 3.0f;
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
	// 프로젝션 매트릭스를 여기서 만드는 이유는 프로젝션 매트릭스가 뷰포트에 영향을 받기 때문
	// 프로젝션 매트릭스 만듦
	float width = _vPlayers[index]->vp.Width;
	float height = _vPlayers[index]->vp.Height;
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection,
		D3DX_PI / 4.0f,					// 시야 각
		width / height,					// 화면 비율(가로 / 세로)
		0.1f,							// 화면에 나올 가까운 z값
		1000.0f);						// 화면에 나올 먼 z값

	// 만든 매트릭스를 디바이스에 적용
	D3DDEVICE->SetTransform(D3DTS_PROJECTION, &projection);

	// 카메라 업데이트로 뷰행렬 설정
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

void playerManager::renderUi()
{
	for (int i = 0; i < _vPlayers.size(); ++i)
		_vPlayers[i]->p->RenderUi();
}

void playerManager::setEMMemory(enemyManager * em)
{
	for (auto i : _vPlayers)
		i->p->setEMMemory(em);
}
