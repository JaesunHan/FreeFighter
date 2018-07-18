#pragma once

#include "sceneInterface.h"

#include "gameMode.h"
#include "playerKeySet.h"

//보스인이 준보스 인지
enum EnemyKind
{
	EK_NONE,
	EK_middle_boss,			//준보스
	EK_final_bose,			//최종 보스
	EK_END
};

class playerManager;
class enemyManager;
class gameObject;
class background;
//class camera;
class cameraWalk;
class appearEnemyScene : public _scene
{
private:
	EnemyKind				_BossMode;				//준보스가 나타났는지 보스가 나타났는지


	//스토리씬에서 받아올 정보들
	//D3DVIEWPORT9			_originViewport;

	//playerManager*			_pm;		//얘는 안쓸지도...
	enemyManager*			_em;

	// 게임 모드 설정
	//GAME_MODE						_gameMode;
	//PLAYER_MODE						_playerMode;
	//vector<PLAYABLE_CHARACTER>		_vPlayerSelect;

	//// 물리엔진용
	//PxScene*						_physXScene;
	//PxMaterial*						_material;
	//PxControllerManager*			_cm;

	// 백그라운드용
	D3DXMATRIX						_mapMatWorld;
	//LPD3DXMESH						_testGround;
	background*						_pBG;


	////에너미 비출 카메라
	//camera*							_camera;
	cameraWalk*						_pCW;

public:
	appearEnemyScene();
	~appearEnemyScene();

	// _scene을(를) 통해 상속됨
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

public:
	//
	inline void setEnemyManager(enemyManager* em)
	{
		_em = em;
	}
	
	inline void setMapMatWorld(D3DXMATRIX mat)
	{
		_mapMatWorld = mat;
	}

	inline void setBackground(background* bg)
	{
		_pBG = bg;
	}
	void setCamWalkStartKeyFrame();

};

