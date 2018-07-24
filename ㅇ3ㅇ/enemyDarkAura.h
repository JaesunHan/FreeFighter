
#pragma once

#include <vector>
using namespace std;

#include "particle.h"

class enemy;

class enemyDarkAura : public particleSystem
{
private:
	float			_radius;
	vector<float>	_angleSpeed;
	vector<float>	_maxHeight;
	float			_lifeTime;
	int				_attackCount;

	enemy*			_enemy;
	bool			_live;

public:
	enemyDarkAura();
	virtual ~enemyDarkAura();

	HRESULT init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos);
	HRESULT init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos, float size, bool live);

	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;

	inline void setPlayer(enemy* e) { _enemy = e; }
};
