#pragma once
#include "sceneInterface.h"

#include "gameMode.h"
#include "playerKeySet.h"

class playerManager;
class enemyManager;
class camera;
class grid;
class cube;

class fightScene : public _scene
{
private:
	D3DVIEWPORT9			_originViewport;

	playerManager*			_pm;
	enemyManager*			_em;

	// 게임 모드 설정
	GAME_MODE						_gameMode;
	PLAYER_MODE						_playerMode;
	vector<PLAYABLE_CHARACTER>		_vPlayerSelect;

	// 물리엔진용
	PxScene*						_physXScene;
	PxMaterial*						_material;
	PxControllerManager*			_cm;

	camera*							_camera;

	cube*							_backGround;
	grid*							_grid;

	int								_gameoverAlpha;
	bool							_isGameOver;
	float							_gameoverTime;

public:
	fightScene();
	~fightScene();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	inline void setMode(GAME_MODE g, PLAYER_MODE p) { _gameMode = g; _playerMode = p; }
	inline void setSelectedPlayer(vector<PLAYABLE_CHARACTER> p) { _vPlayerSelect = p; }

	void cameraZoom(float zoom);
};

