#pragma once
#include "particle.h"

class player;
class leafAtk : public particleSystem
{
private	:

	
	//float			_startRadius;		
	//float			_endRadius;
	float			_angleZ;
	vector<float>	_angleSpd;		//���ӵ�
	float			_MaxDistance;	//��ų�� ������� �ִ� �Ÿ�
	float			_lifeTime;
	int				_atkCount;

	player*			_player;
public:
	leafAtk();
	~leafAtk();

	HRESULT init(float range, float angleZ, int numParticles, const WCHAR* folder, const WCHAR* fileName, D3DXVECTOR3 startPos);

	//�̰� �� virtual�� �ؾ��ϴ��� �� �𸣰ڴ�.
	//virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	void update(float timeDelta = TIMEMANAGER->getElapsedTime());
	void resetParticle(PARTICLE_ATTRIBUTE * attr) ;

	void preRender() ;
	void render() ;
	void postRender() ;
};

