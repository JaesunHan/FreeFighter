#pragma once
#include "sceneInterface.h"

//#include "player.h"

class camera;
class playerManager;
class grid;

class playGround : public iScene
{
private:
	camera * _camera;
	playerManager*	_PM;
	grid*					_grid;

	PxScene*				_physXScene;
	PxMaterial*				_material;
	PxControllerManager*	_cm;

public:
	playGround();
	~playGround();

	//player* _player;


	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	void SetLight();
	void createTestCube();

};

