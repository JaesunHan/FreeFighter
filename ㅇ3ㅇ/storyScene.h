#pragma once
#include "sceneInterface.h"

#include "gameMode.h"
#include "playerKeySet.h"

class playerManager;
class enemyManager;
class gameObject;
class background;

class storyScene : public _scene
{
private:
	D3DVIEWPORT9			_originViewport;

	playerManager*			_pm;
	enemyManager*			_em;

	// ���� ��� ����
	GAME_MODE						_gameMode;
	PLAYER_MODE						_playerMode;
	vector<PLAYABLE_CHARACTER>		_vPlayerSelect;

	// ����������
	PxScene*						_physXScene;
	PxMaterial*						_material;
	PxControllerManager*			_cm;

	// ��׶����
	D3DXMATRIX						_mapMatWorld;
	LPD3DXMESH						_testGround;
	background*						_pBG;

public:
	storyScene();
	~storyScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	void setLight();

	inline void setMode(GAME_MODE g, PLAYER_MODE p) { _gameMode = g; _playerMode = p; }
	inline void setSelectedPlayer(vector<PLAYABLE_CHARACTER> p) { _vPlayerSelect = p; }
};

