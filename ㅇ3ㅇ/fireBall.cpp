#include "stdafx.h"
#include "fireBall.h"
#include "testPlayer.h"


fireBall::fireBall()
	: _radius(2.0f)
	, _isHit(false)
	, _dir(0, 0, 0)
	, _player(NULL)
{
}


fireBall::~fireBall()
{
}

HRESULT fireBall::init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos, PxVec3 dir)
{
	_radius = radius;
	_size = 0.05f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for (int i = 0; i < numParticles; ++i)
		addParticle();

	_dir = dir;
	_speed = 0.3f;
	_startPosition = pos;

	particleSystem::init(filePath);

	_range = 10.0f;

	return S_OK;
}

void fireBall::update(float timeDelta)
{
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		iter->position += iter->velocity;
		iter->velocity += iter->acceleration;

		if (!_isHit)
		{
			float t = getDistance(D3DXVECTOR3(0, 0, 0), iter->position) / _radius;
			iter->currentColor = (1 - t) * iter->startColor + iter->endColor * t;

			if (iter->position.y < 0.0f)
				this->resetParticle(&(*iter));
		}
		else
		{
			float t = getDistance(D3DXVECTOR3(0, 0, 0), iter->position) / (_radius * 4);
			iter->currentColor = (1 - t) * iter->startColor + iter->endColor * t;

			if (getDistance(D3DXVECTOR3(0, 0, 0), iter->position) > (_radius * 4.0f))
				iter->isAlive = false;
		}
	}

	D3DXVECTOR3 currentPos;
	_controller->resize(0.01f);
	if (!_isHit)
	{
		_speed = -0.3f;
		_controller->move(_dir * _speed, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());
	
		PxControllerState state;
		_controller->getState(state);
		if (state.collisionFlags & PxControllerCollisionFlag::eCOLLISION_SIDES)
		{
			if (_player->getController()->getActor() != state.touchedActor)
			{
				_isHit = true;
				this->resetParticle(_isHit);
				//testPlayer* target = (testPlayer*)_player->getController()->getUserData();
				//target->setPosition(D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z));
			}
		}

		currentPos = D3DXVECTOR3(_controller->getPosition().x, _controller->getPosition().y, _controller->getPosition().z);
		if (getDistance(_startPosition, currentPos) > _range)
		{
			_isHit = true;
			this->resetParticle(_isHit);
		}
	}
	else
		_speed = 0.0f;

	D3DXMatrixTranslation(&_worldMatrix, _controller->getPosition().x, _controller->getPosition().y, _controller->getPosition().z);
}

void fireBall::resetParticle(bool isHit)
{
	_isHit = isHit;

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
		this->resetParticle(&(*iter));
}

void fireBall::resetParticle(PARTICLE_ATTRIBUTE* attr)
{
	float theta = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
	float pi = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
	float r = RND->getFromFloatTo(-_radius, _radius);

	float x = r * sinf(theta) * cosf(pi);
	float y = r * sinf(theta) * sinf(pi);
	float z = r * cosf(theta);

	attr->position = D3DXVECTOR3(x, y, z);

	if (!_isHit)
	{
		attr->isAlive = true;
		attr->velocity.x = attr->velocity.z = 0.0f;
		attr->velocity.y = 0.1f * RND->getFromFloatTo(0.5f, 2.0f);

		attr->acceleration.x = attr->acceleration.z = 0.0f;
		attr->acceleration.y = -0.1f * RND->getFromFloatTo(0.5f, 2.0f);
	}
	else
	{
		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &attr->position);

		attr->velocity = dir * RND->getFromFloatTo(0.01f, 0.05f);
		D3DXVec3Normalize(&attr->acceleration, &attr->velocity);
		attr->acceleration *= -RND->getFromFloatTo(0.01f, 0.1f);
	}

	attr->startColor = D3DCOLOR_ARGB(255, 247, 247, 198);
	attr->endColor = D3DCOLOR_ARGB(255, 148, 0, 16);
}

void fireBall::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void fireBall::render()
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

void fireBall::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void fireBall::createController(PxControllerManager** cm, PxMaterial* m)
{
	PxCapsuleControllerDesc desc;
	desc.radius = _radius / 3 * 2;
	desc.height = 0.01f;
	desc.position = PxExtendedVec3(_startPosition.x, _startPosition.y + desc.height + desc.radius * 2, _startPosition.z);
	desc.stepOffset = 0.00001f;
	desc.volumeGrowth = 1.9f;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(0, 1, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_controller = (*cm)->createController(desc);
	_controller->getActor()->setName("fireBall");
}
