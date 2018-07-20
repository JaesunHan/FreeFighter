#pragma once
#include "particle.h"

class player;
class leafAtk : public particleSystem
{
private	:

	
	//float			_startRadius;		
	//float			_endRadius;
	float			_angleZ;
	vector<float>	_angleSpd;		//각속도
	float			_MaxDistance;	//스킬이 쏘아지는 최대 거리
	float			_lifeTime;
	int				_atkCount;

	player*			_player;
public:
	leafAtk();
	~leafAtk();

	HRESULT init(float range, float angleZ, int numParticles, const WCHAR* folder, const WCHAR* fileName, D3DXVECTOR3 startPos);

	//이거 왜 virtual로 해야하는지 잘 모르겠다.
	//virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	void update(float timeDelta = TIMEMANAGER->getElapsedTime());
	void resetParticle(PARTICLE_ATTRIBUTE * attr) ;

	void preRender() ;
	void render() ;
	void postRender() ;
};

