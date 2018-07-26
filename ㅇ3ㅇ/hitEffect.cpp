#include "stdafx.h"
#include "hitEffect.h"


hitEffect::hitEffect()
	: _radius(0.5f)
{
}


hitEffect::~hitEffect()
{
}

HRESULT hitEffect::init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos)
{
	_radius = radius;
	_size = 0.05f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	_endColor = D3DCOLOR_ARGB(255, RND->getFromIntTo(0, 255), RND->getFromIntTo(0, 255), RND->getFromIntTo(0, 255));

	for (int i = 0; i < numParticles; ++i)
		addParticle();

	_startPosition = pos;

	particleSystem::init(filePath);

	_name = _T("hitEffect");

	D3DXMatrixIdentity(&_worldMatrix);
	_worldMatrix._41 = _startPosition.x;
	_worldMatrix._42 = _startPosition.y;
	_worldMatrix._43 = _startPosition.z;

	return S_OK;
}

void hitEffect::update(float timeDelta)
{
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		iter->position += iter->velocity;
		//iter->velocity += iter->acceleration;

		// �̺κ��� �Ÿ��� ���� ��������
		float t = getDistance(D3DXVECTOR3(0, 0, 0), iter->position) / (_radius * 4);
		iter->currentColor = (1 - t) * iter->startColor + iter->endColor * t;

		if (getDistance(D3DXVECTOR3(0, 0, 0), iter->position) > (_radius * 4))
			iter->isAlive = false;
	}
}

void hitEffect::resetParticle(PARTICLE_ATTRIBUTE* attr)
{
	// �׳�... �� ��ǥ�迡�� ��ġ�� �̷��� ��´ٰ� �ϴ����
	float theta = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
	float pi = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
	float r = RND->getFromFloatTo(-_radius, _radius);

	float x = r * sinf(theta) * cosf(pi);
	float y = r * sinf(theta) * sinf(pi);
	float z = r * cosf(theta);

	attr->position = D3DXVECTOR3(x, y, z);

	// �������� ��������ġ �������� �������κ��� ���� �־�������
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir, &attr->position);

	attr->velocity = dir * RND->getFromFloatTo(0.01f, 0.05f);

	// ���� õõ��
	D3DXVec3Normalize(&attr->acceleration, &attr->velocity);
	attr->acceleration *= -RND->getFromFloatTo(0.01f, 0.1f);

	attr->startColor = WHITE;
	attr->endColor = _endColor;
}

void hitEffect::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void hitEffect::render()
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

void hitEffect::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
