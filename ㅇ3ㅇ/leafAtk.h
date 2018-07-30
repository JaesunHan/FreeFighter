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
	vector<float>	_angleSpd;		//���ӵ�
	float			_MaxDistance;	//��ų�� ������� �ִ� �Ÿ�
	float			_lifeTime;
	int				_atkCount;
	float			_skillHeight;	//���α׷��� ����

	player*			_player;			
	//cube*			_collisionCube;		//�浹�� ť��

	//PxController*	_particleCollision; //��ƼŬ �浹�� �ݸ���


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

