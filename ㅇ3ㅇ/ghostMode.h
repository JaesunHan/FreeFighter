#pragma once
#include "particle.h"

class player;

class ghostMode : public particleSystem
{
private:
	float		_radius;
	float		_ghostModeTime;

	player*		_player;

public:
	ghostMode();
	~ghostMode();

	HRESULT init(float radius, int numParticles, const WCHAR* filePath);
	virtual void update(float timeDelta) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;

	inline void setPlayer(player* p) { _player = p; }

};

