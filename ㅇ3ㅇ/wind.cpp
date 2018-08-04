#include "stdafx.h"
#include "wind.h"
#include "enemy.h"


wind::wind()
{
}


wind::~wind()
{
}

void wind::init(float radius, int numParticles, const WCHAR* filePath)
{
	_maxHeight = 5.0f;

	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	_createCount = 0;
	_maxParticles = numParticles;
	for (int i = 0; i < 10; ++i)
		addParticle();

	particleSystem::init(filePath);

	_time = 0.0f;

}

void wind::update(float timeDelta)
{
	_time += TIMEMANAGER->getElapsedTime();
	if (_particles.size() < _maxParticles)
	{
		_createCount++;
		if (_createCount % 2 == 0)
		{
			for (int i = 0; i < 10; ++i)
				addParticle();
			_createCount = 0;
		}
	}

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		iter->position += iter->velocity * 0.07f;

		float t = iter->position.y / _maxHeight;
		iter->currentColor = (1 - t) * iter->startColor + iter->endColor * t;

		if (iter->position.y > _maxHeight)
		{
			if (_time < 3.0f)
				this->resetParticle(&(*iter));
			else
				iter->isAlive = false;
		}
	}

	_worldMatrix._41 = _enemy->GetPosition().x;
	_worldMatrix._42 = _enemy->GetPosition().y;
	_worldMatrix._43 = _enemy->GetPosition().z;
}

void wind::resetParticle(PARTICLE_ATTRIBUTE* attr)
{
	float angle = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
	float x = cosf(angle);
	float y = 0.0f;
	float z = -sinf(angle);
	attr->position = D3DXVECTOR3(x, y, z);

	D3DXVECTOR3 temp = attr->position;
	D3DXVec3Normalize(&temp , &temp);
	attr->velocity = temp + D3DXVECTOR3(0, 1, 0);

	attr->isAlive = true;
	attr->startColor = D3DCOLOR_ARGB(255, 100, 100, 100);
	attr->endColor = D3DCOLOR_ARGB(255, 0, 0, 0);

}

void wind::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void wind::render()
{
	if (_particles.empty()) return;

	this->preRender();

	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_textureName));
	D3DDEVICE->SetFVF(tagPC_Vertex::FVF);
	D3DDEVICE->SetStreamSource(0, _vb, 0, sizeof(tagPC_Vertex));
	D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);

	if (_vbOffset >= _vbSize)
		_vbOffset = 0;

	tagPC_Vertex* vb = NULL;
	_vb->Lock(_vbOffset * sizeof(tagPC_Vertex),
		_vbBatchSize * sizeof(tagPC_Vertex),
		(void**)&vb,
		_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	DWORD numParticlesInBatch = 0;

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();
	for (; iter != _particles.end(); ++iter)
	{
		if (iter->isAlive)
		{
			vb->p = iter->position;
			vb->c = (D3DCOLOR)iter->currentColor;
			vb++;

			numParticlesInBatch++;
			if (numParticlesInBatch == _vbBatchSize)
			{
				_vb->Unlock();

				D3DDEVICE->DrawPrimitive(
					D3DPT_POINTLIST,
					_vbOffset,
					_vbBatchSize);

				_vbOffset += _vbBatchSize;

				if (_vbOffset >= _vbSize)
					_vbOffset = 0;

				_vb->Lock(_vbOffset * sizeof(tagPC_Vertex),
					_vbBatchSize * sizeof(tagPC_Vertex),
					(void**)&vb,
					_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				numParticlesInBatch = 0;
			}
		}
	}

	_vb->Unlock();

	if (numParticlesInBatch != 0)
	{
		D3DDEVICE->DrawPrimitive(
			D3DPT_POINTLIST,
			_vbOffset,
			numParticlesInBatch);
	}

	_vbOffset += _vbBatchSize;

	this->postRender();
}

void wind::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
