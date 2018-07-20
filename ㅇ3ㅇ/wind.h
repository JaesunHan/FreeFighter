#pragma once

#include "particle.h"

class enemy;

class wind : public particleSystem
{
	//원에서 랜덤하게 위로 흩날림을 원함
private:
	enemy*			_enemy;
	float			_maxHeight;

public:
	wind();
	~wind();

	virtual void init(float radius, int numParticles, const WCHAR* filePath);
	// particleSystem을(를) 통해 상속됨
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;

	virtual void preRender();
	virtual void render();
	virtual void postRender();

	void SetEnemyAdressLink(enemy* e) { _enemy = e; }
};

