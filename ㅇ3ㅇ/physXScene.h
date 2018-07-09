#pragma once
#include "sceneInterface.h"

class grid;
class camera;
class testPlayer;

class physXScene : public _scene
{
private:
	testPlayer*				_player;

	grid*					_grid;
	camera*					_camera;

	PxScene*				_physXScene;
	PxMaterial*				_material;
	PxControllerManager*	_cm;

public:
	physXScene();
	~physXScene();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	void cameraZoom(float zoom);
};

