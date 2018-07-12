#pragma once
#include "particle.h"

class testPlayer;

class fireBall : public particleSystem
{
private:
	float		_radius;
	bool		_isHit;

	PxVec3		_dir;
	float		_speed;

	testPlayer*		_player;

public:
	fireBall();
	virtual ~fireBall();

	HRESULT init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos, PxVec3 dir);
	virtual void update(float timeDelta) override;
	virtual void resetParticle(bool isHit);
	virtual void resetParticle(PARTICLE_ATTRIBUTE* attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;

	void createController(PxControllerManager** cm, PxMaterial* m);

	inline void setPlayer(testPlayer* p) { _player = p; }
};

