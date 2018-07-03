#pragma once
#include "sceneInterface.h"
#include "uiButton.h"

#include "gameMode.h"

#include <vector>
using namespace std;

class uiImageView;
class skinnedMesh;
class playerSelector;
class camera;

class selectScene : public _scene, public _buttonDelegate
{
private:
	uiButton*				_buttons;

	GAME_MODE				_gameMode;
	PLAYER_MODE				_playerMode;

	uiImageView*			_portrait;

	vector<skinnedMesh*>	_vMesh;
	vector<playerSelector*>	_selectors;

	camera*					_camera;

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

