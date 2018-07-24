#pragma once
#include "particle.h"

class enemy;

class smoke : public particleSystem
{
private:
	enemy*			_enemy;
	vector<float>	_vMaxHeight;
	vector<float>	_vSpeed;

	int				_particleNum;

public:
	smoke();
	~smoke();

	virtual void init(int numParticles, const WCHAR* filePath);
	// particleSystem을(를) 통해 상속됨
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;

	virtual void preRender();
	virtual void render();
	virtual void postRender();

	void SetEnemyAdressLink(enemy* e) { _enemy = e; }
};

