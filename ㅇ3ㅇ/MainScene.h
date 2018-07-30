#pragma once
#include "sceneInterface.h"
#include "uiButton.h"

#include "gameMode.h"

class cube;
class mainSceneTrailer;

class mainScene : public _scene, public _buttonDelegate
{
private:
	uiButton*	_modeButtons;
	uiButton*	_playerButtons;

	bool		_isModeSelect;
	bool		_isPlayersSelect;

	GAME_MODE	_gameMode;
	PLAYER_MODE	_playerMode;

	D3DXVECTOR3	_titleScale;

	mainSceneTrailer*		_trailer;
	cube*					_backGround;

	int						_totalGold;

public:
	mainScene();
	~mainScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	virtual void OnClick(uiButton* d) override;

	void modeReset();
};

