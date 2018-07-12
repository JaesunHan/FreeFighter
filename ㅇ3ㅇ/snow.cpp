#include "stdafx.h"
#include "snow.h"


snow::snow()
{
}


snow::~snow()
{
}

HRESULT snow::init(float range, int numParticles, const WCHAR* filePath)
{
	_range = range;
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;
		
	_minRange = D3DXVECTOR3(-_range / 2, -_range / 2, -_range / 2);
	_maxRange = D3DXVECTOR3(_range / 2, _range / 2, _range / 2);

	for (int i = 0; i < numParticles; ++i)
		addParticle();

	particleSystem::init(filePath);

	return S_OK;
}

void snow::update(float timeDelta)
{
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		iter->position += iter->velocity;

		if (!this->isPointInside(iter->position))
		{
			resetParticle(&(*iter));
		}
	}
}

void snow::resetParticle(PARTICLE_ATTRIBUTE* attr)
{
	attr->isAlive = true;

	attr->position = RND->getFromVec3To(_minRange, _maxRange);

	attr->position.y = _maxRange.y;

	attr->velocity.x = RND->getFromFloatTo(0.0f, 1.0f) * -0.1f;
	attr->velocity.y = RND->getFromFloatTo(0.0f, 1.0f) * -0.3f;
	attr->velocity.z = 0.0f;

	attr->startColor = WHITE;
}

bool snow::isPointInside(D3DXVECTOR3 pos)
{
	return (_minRange.x < pos.x && pos.x < _maxRange.x &&
			_minRange.y < pos.y && pos.y < _maxRange.y &&
			_minRange.z < pos.z && pos.z < _maxRange.z);
}
