#pragma once
#include "particle.h"

class player;

class poisonArrow : public particleSystem
{
private:
	float		_radius;
	bool		_isHit;

	PxVec3		_dir;
	float		_dirAngle;
	float		_speed;

	player*		_player;

public:
	poisonArrow();
	virtual ~poisonArrow();

	HRESULT init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos, PxVec3 dir, float dirAngle);
	virtual void update(float timeDelta) override;
	virtual void resetParticle(bool isHit);
	virtual void resetParticle(PARTICLE_ATTRIBUTE* attr) override;

	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;

	void createController(PxControllerManager** cm, PxMaterial* m);

	inline void setPlayer(player* p) { _player = p; }
};

