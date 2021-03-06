#pragma once
#include "particle.h"


class cube;
class player;
class leafAtk : public particleSystem
{
private	:
	int				_attackCount;
	
	//float			_startRadius;		
	//float			_endRadius;
	float			_angleZ;
	float			_angleY;
	vector<float>	_angleSpd;		//각속도
	float			_MaxDistance;	//스킬이 쏘아지는 최대 거리
	float			_lifeTime;
	int				_atkCount;
	float			_skillHeight;	//싸인그래프 높이

	player*			_player;			
	//cube*			_collisionCube;		//충돌용 큐브

	//PxController*	_particleCollision; //파티클 충돌용 콜리전


public:
	leafAtk();
	~leafAtk();

	HRESULT init(float range, float skillHeight, float angleZ, float angleY, int numParticles, const WCHAR* folder, const WCHAR* fileName, D3DXVECTOR3 startPos);

	//virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime());
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr) ;
	virtual void addParticle();

	virtual void preRender() ;
	virtual void render() ;
	virtual void postRender() ;

	void createController(PxControllerManager** cm, PxMaterial * m);


	inline void setPlayer(player* p) { _player = p; }
};

