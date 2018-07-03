#pragma once
#include "sceneInterface.h"

class enemyManager;
class camera;

class battleScene : public iScene
{
private:
	enemyManager*	_em;
	camera*			_camera;

	D3DXVECTOR3		_test01;

public:
	battleScene();
	~battleScene();

	// _scene을(를) 통해 상속됨
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	void SetLight();
};

