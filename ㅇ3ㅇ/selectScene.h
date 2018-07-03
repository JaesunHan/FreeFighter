#pragma once
#include "sceneInterface.h"
#include "uiButton.h"

#include "gameMode.h"

class selectScene : public _scene, public _buttonDelegate
{
private:
	uiButton*	_buttons;

	GAME_MODE	_gameMode;
	PLAYER_MODE	_playerMode;

public:
	selectScene();
	~selectScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	virtual void OnClick(uiButton* d) override;

	inline void setMode(GAME_MODE g, PLAYER_MODE p) { _gameMode = g; _playerMode = p; }
};

