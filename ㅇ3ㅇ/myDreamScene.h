#pragma once
#include "sceneInterface.h"

class enemyManager;
class camera;

class myDreamScene : public iScene
{
private:
	enemyManager*	_em;
	camera*			_camera;

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

