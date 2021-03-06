#pragma once
#include "particle.h"

class player;
class vineAtk : public particleSystem
{
private:
	float			_radius;		//������̾�Ʈ ��ġ�κ��� �ݰ� ��
	float			_angleZ;
	float			_angleY;
	vector<float>	_angleSpd;		//���ӵ�
	vector<float>	_frontDir;		//������ ���� ������ ���� (����)
	//vector<D3DXVECTOR3>	_frontDir;		//������ ���� ������ ���⺤�͸� ��� ����

	float			_lifeTime;
	int				_atkCount;

	player*			_player;

	int				_attackCount;

	int				_particleIdx;		//������

public:
	vineAtk();
	~vineAtk();
	HRESULT init(float radius, int numParticles, const WCHAR* folder, const WCHAR* fileName, D3DXVECTOR3 startPos);

	//virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime()) override;
	virtual void update(float timeDelta = TIMEMANAGER->getElapsedTime());
	virtual void resetParticle(PARTICLE_ATTRIBUTE * attr);
	virtual void addParticle();

	virtual void preRender();
	virtual void render();
	virtual void postRender();

	

	inline void setPlayer(player* p) { _player = p; }
};

