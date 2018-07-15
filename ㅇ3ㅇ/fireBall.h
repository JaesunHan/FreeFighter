#pragma once
#include "particle.h"

class player;

class fireBall : public particleSystem
{
private:
	float		_radius;
	bool		_isHit;

	PxVec3		_dir;
	float		_speed;

	player*		_player;

public:
	fireBall();
	virtual ~fireBall();

	HRESULT init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos, PxVec3 dir);
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void resetParticle(bool isHit);
	virtual void resetParticle(PARTICLE_ATTRIBUTE* attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;

	void createController(PxControllerManager** cm, PxMaterial* m);

	inline void setPlayer(player* p) { _player = p; }
};

