#pragma once
#include "sceneInterface.h"
//#include "player.h"

class camera;
class playerManager;


class playGround : public _scene
{
public:
	playGround();
	~playGround();

	//player* _player;
	camera* _camera;
	playerManager*	_PM;

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	void SetLight();
};

