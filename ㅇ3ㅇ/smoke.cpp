#include "stdafx.h"
#include "smoke.h"
#include "enemy.h"
#include "particle.h"


smoke::smoke()
{
}


smoke::~smoke()
{
}

void smoke::init(int numParticles, const WCHAR * filePath)
{
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	_particleNum = numParticles;

	for (int i = 0; i < numParticles; ++i)
	{
		addParticle();

		float rndHeight = RND->getFromFloatTo(4.0f, 6.0f);
		_vMaxHeight.push_back(rndHeight);
		float rndSpeed = RND->getFromFloatTo(0.05f, 0.1f);
		_vSpeed.push_back(rndSpeed);
	}
	
	particleSystem::init(filePath);
}

void smoke::update(float timeDelta)
{
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	int i = 0;

	for (; iter != _particles.end(); iter++, i++)
	{
		iter->position += iter->velocity * _vSpeed[i];

		float t = iter->position.y / _vMaxHeight[i];
		iter->currentColor = (1 - t) * iter->startColor + iter->endColor * t;

		if (iter->position.y > _vMaxHeight[i])
			resetParticle(&(*iter));
	}

	_worldMatrix._41 = _enemy->GetPosition().x;
	_worldMatrix._42 = _enemy->GetPosition().y;
	_worldMatrix._43 = _enemy->GetPosition().z;
}

void smoke::resetParticle(PARTICLE_ATTRIBUTE* attr)
{
	attr->position = D3DXVECTOR3(0, 0, 0);
	attr->velocity = D3DXVECTOR3(0, 0.1, 0);
	attr->isAlive = true;
	attr->startColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	attr->endColor = D3DCOLOR_ARGB(255, 0, 255, 0);
}

void smoke::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void smoke::render()
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

void smoke::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
