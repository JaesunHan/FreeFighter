#pragma once
#include "sceneInterface.h"

#include "gameMode.h"

class camera;
class gameObject;
class background;

class storyScene : public _scene
{
private:
	//LPD3DXMESH						_meshMap;			//¸Ê ¸Þ½Ã
	//vector<tagObjectMtlData>		_vecMapMtlData;		
	//
	//LPD3DXMESH						_meshSurface;			//surface ¸Þ½Ã
	//vector<tagObjectMtlData>		_vecSurfaceMtlData;

	D3DXMATRIX						_mapMatWorld;

	//Ä·
	camera*							_camera;

	//vector<gameObject>				_vecMap;
	//vector<gameObject>				_vecMapSurface;
	background*						_pBG;

	GAME_MODE						_gameMode;
	PLAYER_MODE						_playerMode;

	LPD3DXMESH						_testGround;

	PxScene*						_physXScene;
	PxMaterial*						_material;
	PxControllerManager*			_cm;

	
public:
	storyScene();
	~storyScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;
	void cameraZoom(float zoom);

	void setLight();

	inline void setMode(GAME_MODE g, PLAYER_MODE p) { _gameMode = g; _playerMode = p; }
};

