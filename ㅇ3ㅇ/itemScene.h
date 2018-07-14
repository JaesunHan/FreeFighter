#pragma once
#include "sceneInterface.h"



class camera;
class grid;
class cube;

class itemScene : public iScene
{
private:
	camera *				_camera;
	grid*					_grid;
	cube*					_cube;

	PxScene*				_physXScene;
	PxMaterial*				_material;
	PxControllerManager*	_cm;

public:
	itemScene();
	~itemScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	void SetLight();

};

