#include "stdafx.h"
#include "fastBuff.h"
#include "player.h"


fastBuff::fastBuff()
	: _radius(1.0f)
	, _fastBuffTime(0.0f)
	, _player(NULL)
{
}


fastBuff::~fastBuff()
{
}

HRESULT fastBuff::init(int numParticles, const WCHAR* filePath)
{
	_radius = 1.0f;
	_size = 0.05f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for (int i = 0; i < numParticles; ++i)
		this->addParticle();

	_name = _T("fastBuff");

	particleSystem::init(filePath);

	return S_OK;
}

void fastBuff::update(float timeDelta)
{
	_fastBuffTime += TIMEMANAGER->getElapsedTime();
	if (_fastBuffTime > FAST_MAX_TIME)
		_player->setIsFast(false);

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();
	D3DXVECTOR3 pos = _player->GetPosition();

	for (; iter != _particles.end(); ++iter)
	{
		iter->position += iter->velocity;
		D3DXMATRIX matR;
		D3DXMatrixRotationY(&matR, 10.0f * DEG2RAD);
		D3DXVec3TransformNormal(&iter->velocity, &iter->velocity, &matR);

		iter->velocity.y -= 0.01f;

		if (iter->velocity.y < 0.0f)
		{
			if (_player->getIsFast())
				this->resetParticle(&(*iter));
			else
				iter->isAlive = false;
		}

		float t = iter->velocity.y / 0.1f;
		iter->currentColor = (1 - t) * iter->startColor + iter->endColor * t;
	}

	_worldMatrix._41 = pos.x;
	_worldMatrix._42 = pos.y;
	_worldMatrix._43 = pos.z;
}

void fastBuff::resetParticle(PARTICLE_ATTRIBUTE* attr)
{
	float angle = RND->getFromFloatTo(0.0f * DEG2RAD, 360.0f * DEG2RAD);

	attr->position = D3DXVECTOR3(_radius * cosf(angle), 0.0f, _radius * -sinf(angle));
	attr->velocity.x = attr->position.x * RND->getFromFloatTo(0.01f, 0.1f);
	attr->velocity.z = attr->position.z * RND->getFromFloatTo(0.01f, 0.1f);
	attr->velocity.y = RND->getFromFloatTo(0.05f, 0.1f);

	attr->isAlive = true;

	attr->startColor = D3DCOLOR_ARGB(255, 206, 231, 231);
	attr->endColor = D3DCOLOR_ARGB(255, 74, 132, 247);

	attr->currentColor = attr->startColor;
}

void fastBuff::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void fastBuff::render()
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

void fastBuff::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
