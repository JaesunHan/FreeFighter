#pragma once
#include "particle.h"

#include <vector>
using namespace std;

class player;

class itemEffect : public particleSystem
{
private:
	D3DXCOLOR		_color;

	player*		_player;

	float			_buffTime;
	float			_currentTime;
	float			_particleCount;

public:
	itemEffect();
	~itemEffect();
	
	HRESULT init(int numParticles, const WCHAR* filePath, D3DXCOLOR color, float buffTime);
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;

	inline void setPlayer(player* p) { _player = p; }
};

