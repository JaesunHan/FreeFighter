#pragma once
#include "particle.h"

class hitEffect : public particleSystem
{
private:
	float		_radius;

	D3DXCOLOR	_endColor;

public:
	hitEffect();
	~hitEffect();

	HRESULT init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos);
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;
};

