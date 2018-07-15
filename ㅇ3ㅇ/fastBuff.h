#pragma once
#include "particle.h"

#define FAST_MAX_TIME	5.0f

class player;

class fastBuff : public particleSystem
{
private:
	float		_radius;
	float		_fastBuffTime;

	player*		_player;

public:
	fastBuff();
	~fastBuff();

	HRESULT init(int numParticles, const WCHAR* filePath);
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;

	inline void setPlayer(player* p) { _player = p; }
};

