#pragma once
#include "sceneInterface.h"

class enemyManager;
class playerManager;
class camera;
class grid;

class myDreamScene : public iScene
{
private:
	playerManager*  _pm;
	enemyManager*	_em;
	camera*			_camera;
	grid*			_grid;

	//물리엔진
	PxScene*				_physXScene;
	PxMaterial*				_material;
	PxControllerManager*	_cm;

private:
	D3DXVECTOR3		_testTarget;
	int				_testStage;

public:
	myDreamScene();
	~myDreamScene();

	// _scene을(를) 통해 상속됨
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
};

