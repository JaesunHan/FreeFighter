#pragma once

#include <vector>
using namespace std;

#include "gameMode.h"
#include "playerKeySet.h"

class player;
class camera;
class enemyManager;
class itemManager;

struct tagPlayer
{
	D3DVIEWPORT9 vp;
	camera*	cam;
	player* p;

	tagPlayer()
		: vp()
		, cam(NULL)
		, p(NULL)
	{ }
};

class playerManager
{
private:
	vector<tagPlayer*> _vPlayers;

public:
	playerManager();
	~playerManager();

	HRESULT	init(GAME_MODE gameMode, PLAYER_MODE playerMode, vector<PLAYABLE_CHARACTER> vPlayerSelected, PxControllerManager** cm, PxMaterial* m);

	void playerPositionInit(GAME_MODE gameMode, PLAYER_MODE playerMode);
	void release();
	void update();
	void render(int index);
	void renderParticle();
	void renderUi(int index);

	inline vector<tagPlayer*> getVPlayers() { return _vPlayers; }
	inline int getPlayersNum() { return _vPlayers.size(); }
	inline void setViewPort(int index) { D3DDEVICE->SetViewport(&_vPlayers[index]->vp); }
	void setEMMemory(enemyManager* em);
	void setIMMemory(itemManager* im);
};