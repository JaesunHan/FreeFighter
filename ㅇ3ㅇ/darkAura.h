#pragma once

#include <vector>
using namespace std;

#include "particle.h"

class player;

class darkAura : public particleSystem
{
private:
	float			_radius;
	vector<float>	_angleSpeed;
	vector<float>	_maxHeight;
	float			_lifeTime;
	int				_attackCount;

	player*			_player;

public:
	darkAura();
	virtual ~darkAura();

	HRESULT init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos);

	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;

	inline void setPlayer(player* p) { _player = p; }
};

