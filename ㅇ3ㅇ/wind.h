#pragma once

#include "particle.h"

class wind : public particleSystem
{
public:
	wind();
	~wind();

	// particleSystem��(��) ���� ��ӵ�
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;
};

