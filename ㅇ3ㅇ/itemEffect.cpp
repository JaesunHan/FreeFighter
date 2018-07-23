#include "stdafx.h"
#include "itemEffect.h"
#include "player.h"


itemEffect::itemEffect()
	: _buffTime(1.0f)
	, _particleCount(0.0f)
	, _currentTime(0.0f)
{
}


itemEffect::~itemEffect()
{
}

HRESULT itemEffect::init(int numParticles, const WCHAR * filePath, D3DXCOLOR color, float buffTime)
{
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;
	_buffTime = buffTime;
	_currentTime = 0.0f;

	_maxParticles = numParticles;
	addParticle();

	_particleCount = 0.0f;

	_color = color;

	particleSystem::init(filePath);

	return S_OK;
}

void itemEffect::update(float timeDelta)
{
	if (_particles.size() < _maxParticles)
	{
		_particleCount += TIMEMANAGER->getElapsedTime();
		if (_particleCount > _buffTime / _maxParticles)
		{
			addParticle();
			_particleCount = 0.0f;
		}
	}

	_currentTime += TIMEMANAGER->getElapsedTime();
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();
	for (; iter != _particles.end(); ++iter)
	{
		D3DXMATRIX matR;
		D3DXMatrixRotationY(&matR, iter->velocity.y);
		D3DXVec3TransformCoord(&iter->position, &iter->position, &matR);
		iter->lifeTime += iter->velocity.y;

		float t = _currentTime / _buffTime;
		iter->currentColor = (1 - t) * iter->startColor + t * iter->endColor;

		if (iter->lifeTime > D3DX_PI * 2)
		{
			if (_currentTime < _buffTime)
				this->resetParticle(&(*iter));
			else
				iter->isAlive = false;
		}
	}

	D3DXVECTOR3 playerPos = _player->GetPosition();
	_worldMatrix._41 = playerPos.x;
	_worldMatrix._42 = playerPos.y;
	_worldMatrix._43 = playerPos.z;
}

void itemEffect::resetParticle(PARTICLE_ATTRIBUTE * attr)
{
	float angle = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
	float r = RND->getFromFloatTo(0.5f, 1.5f);

	attr->position.x = r * cosf(angle);
	attr->position.y = RND->getFromFloatTo(0.0f, 0.5f);
	attr->position.z = r * -sinf(angle);

	attr->velocity.y = RND->getFromFloatTo(5.0f, 10.0f) * DEG2RAD;

	attr->isAlive = true;

	attr->startColor = _color;
	attr->endColor = _color;
	attr->endColor.a = 0;

	attr->lifeTime = 0.0f;
}

void itemEffect::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void itemEffect::render()
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

void itemEffect::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
