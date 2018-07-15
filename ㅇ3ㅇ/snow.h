#pragma once
#include "particle.h"

class snow : public particleSystem
{
private:
	D3DXVECTOR3 _minRange, _maxRange;

public:
	snow();
	virtual ~snow();

	HRESULT init(float range, int numParticles, const WCHAR* filePath);
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE* attr) override;

	bool isPointInside(D3DXVECTOR3 pos);
};

