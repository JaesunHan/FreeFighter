#include "stdafx.h"
#include "enemyDarkAura.h"
#include "player.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "enemy.h"


enemyDarkAura::enemyDarkAura()
{
}


enemyDarkAura::~enemyDarkAura()
{
	_angleSpeed.clear();
	_maxHeight.clear();
}

HRESULT enemyDarkAura::init(float radius, int numParticles, const WCHAR * filePath, D3DXVECTOR3 pos)
{
	_radius = radius;
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	_angleSpeed.resize(numParticles);
	_maxHeight.resize(numParticles);
	for (int i = 0; i < numParticles; ++i)
	{
		_angleSpeed[i] = RND->getFromFloatTo(0.5f * DEG2RAD, 10.0f * DEG2RAD);
		_maxHeight[i] = RND->getFromFloatTo(3.0f, 5.0f);
		addParticle();
	}

	_name = _T("darkAura");
	_startPosition = pos;

	particleSystem::init(filePath);

	_range = radius;
	_lifeTime = 0.0f;
	_attackCount = 0;

	_worldMatrix._41 = pos.x;
	_worldMatrix._42 = pos.y;
	_worldMatrix._43 = pos.z;

	return S_OK;
}

void enemyDarkAura::update(float timeDelta)
{
	_lifeTime += TIMEMANAGER->getElapsedTime();

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();
	int i = 0;
	for (; iter != _particles.end(); ++iter, ++i)
	{
		iter->position += iter->velocity;
		iter->velocity += iter->acceleration;

		D3DXMATRIX matR;
		D3DXMatrixRotationY(&matR, _angleSpeed[i]);
		D3DXVec3TransformCoord(&iter->position, &iter->position, &matR);

		D3DXVECTOR3 temp = iter->position;
		temp.y = 0.0f;
		float t = getDistance(temp, D3DXVECTOR3(0, 0, 0)) / _radius;
		iter->currentColor = (1 - t) * iter->startColor + iter->endColor * t;

		if (iter->position.y > _maxHeight[i])
		{
			if (_lifeTime > 3.5f)
				iter->isAlive = false;
			else
				this->resetParticle(&(*iter));
		}
	}

	//_attackCount++;
	//if (_attackCount % 3 == 0)
	//{
	//	for (int i = 0; i < _player->getEM()->GetEnemy().size(); ++i)
	//	{
	//		if (_player->getEM()->GetEnemy()[i]->GetIsDead()) continue;
	//
	//		D3DXVECTOR3 enemyPos = _player->getEM()->GetEnemy()[i]->GetPosition();
	//		enemyPos.y = 0.0f;
	//		D3DXVECTOR3 position = _startPosition;
	//		position.y = 0.0f;
	//		if (getDistance(enemyPos, position) < _radius * 1.3f)
	//		{
	//			_player->getEM()->GetEnemy()[i]->HitDamage(_player->getAtk() / 10);
	//		}
	//	}
	//
	//	_attackCount = 0;
	//}
}

void enemyDarkAura::resetParticle(PARTICLE_ATTRIBUTE * attr)
{
	attr->position = D3DXVECTOR3(0.0f, 0.0f, RND->getFromFloatTo(0.5f, _radius));
	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, RND->getFromFloatTo(0.0f, D3DX_PI * 2));
	D3DXVec3TransformCoord(&attr->position, &attr->position, &matR);
	attr->velocity = D3DXVECTOR3(0.0f, RND->getFromFloatTo(0.001f, 0.01f), 0.0f);
	attr->acceleration = D3DXVECTOR3(0.0f, RND->getFromFloatTo(0.01f, 0.05f), 0.0f);
	attr->isAlive = true;

	attr->startColor = D3DCOLOR_ARGB(255, 255, 190, 231);
	attr->endColor = D3DCOLOR_ARGB(255, 74, 20, 140);
}

void enemyDarkAura::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void enemyDarkAura::render()
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

void enemyDarkAura::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
