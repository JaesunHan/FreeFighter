#pragma once

#include "particle.h"

class wind : public particleSystem
{
public:
	wind();
	~wind();

	// particleSystem을(를) 통해 상속됨
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;
};

