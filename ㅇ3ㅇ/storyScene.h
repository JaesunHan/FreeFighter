#pragma once
#include "sceneInterface.h"

#include "gameMode.h"
#include "playerKeySet.h"

class playerManager;
class enemyManager;
class itemManager;
class gameObject;
class background;
class camera;
class appearEnemyScene;


class storyScene : public _scene
{
private:
	D3DVIEWPORT9			_originViewport;

	playerManager*			_pm;
	enemyManager*			_em;
	itemManager*			_im;

	// 게임 모드 설정
	GAME_MODE						_gameMode;
	PLAYER_MODE						_playerMode;
	vector<PLAYABLE_CHARACTER>		_vPlayerSelect;

	// 물리엔진용
	PxScene*						_physXScene;
	PxMaterial*						_material;
	PxControllerManager*			_cm;

	// 백그라운드용
	D3DXMATRIX						_mapMatWorld;
	LPD3DXMESH						_testGround;
	background*						_pBG;

	camera*							_camera;

	appearEnemyScene*				_appearScene;

	bool							_isBossAppear;

	int								_gameoverAlpha;
	bool							_isGameOver;
	float							_gameoverTime;

	float							_victoryTime;
	int								_victoryAlpha;

public:
	storyScene();
	~storyScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;
	
	void getGold();

	void setLight();

	inline void setMode(GAME_MODE g, PLAYER_MODE p) { _gameMode = g; _playerMode = p; }
	inline void setSelectedPlayer(vector<PLAYABLE_CHARACTER> p) { _vPlayerSelect = p; }

	void cameraZoom(float zoom);
};

