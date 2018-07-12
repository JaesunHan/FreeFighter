#pragma once

#include <list>
using namespace std;

typedef struct tagParticle
{
	D3DXVECTOR3		p;
	D3DCOLOR		c;
	float			size;

	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE
	};

	tagParticle()
		: p(0,0,0)
		, c(WHITE)
		, size(0.1f)
	{ }

} PARTICLE;

typedef struct tagParticleAttribute
{
	D3DXVECTOR3		position;
	D3DXVECTOR3		velocity;
	D3DXVECTOR3		acceleration;

	float			lifeTime;
	float			age;

	D3DXCOLOR		startColor;
	D3DXCOLOR		endColor;

	D3DXCOLOR		currentColor;

	bool			isAlive;

	tagParticleAttribute()
		: position(0, 0, 0)
		, velocity(0, 0, 0)
		, acceleration(0, 0.1f, 0)
		, lifeTime(1.0f)
		, age(0)
		, startColor(D3DCOLOR_ARGB(255, 0, 0, 0))
		, endColor(D3DCOLOR_ARGB(255, 0, 0, 0))
		, isAlive(true)
		, currentColor(D3DCOLOR_ARGB(255, 0, 0, 0))
	{ }

} PARTICLE_ATTRIBUTE;

class particleSystem
{
protected:
	D3DXVECTOR3				_startPosition;

	float					_size;

	wstring					_textureName;

	LPDIRECT3DVERTEXBUFFER9	_vb;
	// ���� �ý��� �� ������ �� �ִ� �ִ� ��ƼŬ ��
	int						_maxParticles;

	D3DXMATRIX				_worldMatrix;

	// ��� ���� + ��ü �̵�
	PxController*			_controller;
	float					_range;

	// �ʴ� ��ƼŬ ��
	float					_emitRate;

	// �ý��� �� ��ƼŬ �Ӽ� ����Ʈ
	list<PARTICLE_ATTRIBUTE>	_particles;

	// ���ؽ� ���۰� ������ �� �ִ� �ִ� ��ƼŬ ��
	DWORD	_vbSize;
	DWORD	_vbOffset;
	DWORD	_vbBatchSize;

public:
	particleSystem();
	virtual ~particleSystem();

	virtual HRESULT init(const WCHAR* filePath);
	virtual void release();
	virtual void update(float timeDelta) = 0;

	virtual void reset();
	virtual void resetParticle(PARTICLE_ATTRIBUTE* attr) = 0;
	virtual void addParticle();

	virtual void preRender();
	virtual void render();
	virtual void postRender();

	virtual void removeDeadParticles();

	bool isEmpty();
	bool isDead();
};

