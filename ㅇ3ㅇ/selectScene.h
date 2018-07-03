#pragma once
#include "sceneInterface.h"

enum GAME_MODE
{
	GAME_NONE = -1,
	GAME_STORY,
	GAME_FIGHT,
	GAME_END
};

class selectScene : public _scene
{
public:
	selectScene();
	~selectScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;
};

