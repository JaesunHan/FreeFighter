#include "stdafx.h"
#include "gravityShot.h"
#include "reaper.h"
#include "enemyManager.h"
#include "enemy.h"


gravityShot::gravityShot()
	: _radius(2.0f)
	, _isHit(false)
	, _dir(0, 0, 0)
	, _player(NULL)
{
}


gravityShot::~gravityShot()
{
}

HRESULT gravityShot::init(float radius, int numParticles, const WCHAR * filePath, D3DXVECTOR3 pos, PxVec3 dir)
{
	_radius = radius;
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for (int i = 0; i < numParticles; ++i)
		addParticle();

	_dir = dir;
	_speed = 0.3f;
	_startPosition = pos;

	particleSystem::init(filePath);

	_range = 5.0f;

	return S_OK;
}

void gravityShot::update(float timeDelta)
{
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	if (_isHit)
		_gravityTime += TIMEMANAGER->getElapsedTime();

	for (; iter != _particles.end(); ++iter)
	{
		iter->position += iter->velocity;
		iter->velocity += iter->acceleration;


		float t = getDistance(D3DXVECTOR3(0, 0, 0), iter->position) / _radius;
		if (t > 1.0f)
			t = 1.0f;
		iter->currentColor = (1 - t) * iter->startColor + iter->endColor * t;

		if (!_isHit)
		{
			if (iter->position.y < 0.0f)
				this->resetParticle(&(*iter));
		}
		else
		{
			if (_gravityTime < 5.0f)
			{
				if (getDistance(D3DXVECTOR3(0, 0, 0), iter->position) < _radius)
					this->resetParticle(&(*iter));
			}
			else
			{
				if (getDistance(D3DXVECTOR3(0, 0, 0), iter->position) < _radius)
					iter->isAlive = false;
			}
		}
	}

	if (!_isHit && _controller)
	{
		D3DXVECTOR3 currentPos;
		_controller->resize(0.01f);
		_controller->move(_dir * _speed, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());
		_speed -= 0.005f;
		if (_speed < 0.0f)
			_speed = 0.0f;

		PxControllerState state;
		_controller->getState(state);

		if (_controller)
		{
			currentPos = D3DXVECTOR3(_controller->getPosition().x, _controller->getPosition().y, _controller->getPosition().z);
			if (((reaper*)_player)->isGravityStart())
			{
				_isHit = true;
				this->resetParticle(_isHit);
				_controller->release();
				_controller = NULL;
				_gravityTime = 0.0f;
			}

			if (_controller)
				D3DXMatrixTranslation(&_worldMatrix, _controller->getPosition().x, _controller->getPosition().y, _controller->getPosition().z);
		}
	}
	else
	{
		_speed = 0.0f;

		D3DXVECTOR3 currentPos = D3DXVECTOR3(_worldMatrix._41, _worldMatrix._42, _worldMatrix._43);
		for (int i = 0; i < _player->getEM()->GetEnemy().size(); ++i)
		{
			if (_player->getEM()->GetEnemy()[i]->GetIsDead()) continue;

			if (getDistance(currentPos, _player->getEM()->GetEnemy()[i]->GetPosition()) < 5.0f)
			{
				D3DXVECTOR3 dir = currentPos - _player->getEM()->GetEnemy()[i]->GetPosition();
				D3DXVec3Normalize(&dir, &dir);
				_player->getEM()->GetEnemy()[i]->SetPosition(_player->getEM()->GetEnemy()[i]->GetPosition() + dir * 0.03f);
			}
		}
	}
}

void gravityShot::resetParticle(bool isHit)
{
	_isHit = isHit;

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
		this->resetParticle(&(*iter));
}

void gravityShot::resetParticle(PARTICLE_ATTRIBUTE * attr)
{
	float theta = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
	float pi = RND->getFromFloatTo(0.0f, D3DX_PI * 2);

	if (!_isHit)
	{
		float r = RND->getFromFloatTo(-_radius, _radius);

		float x = r * sinf(theta) * cosf(pi);
		float y = r * sinf(theta) * sinf(pi);
		float z = r * cosf(theta);

		attr->position = D3DXVECTOR3(x, y, z);

		attr->isAlive = true;
		attr->velocity.x = attr->velocity.z = 0.0f;
		attr->velocity.y = 0.1f * RND->getFromFloatTo(0.5f, 2.0f);

		attr->acceleration.x = attr->acceleration.z = 0.0f;
		attr->acceleration.y = -0.1f * RND->getFromFloatTo(0.5f, 2.0f);
	}
	else
	{
		float r = RND->getFromFloatTo(-_radius * 4, _radius * 4);

		float x = r * sinf(theta) * cosf(pi);
		float y = r * sinf(theta) * sinf(pi);
		float z = r * cosf(theta);

		attr->position = D3DXVECTOR3(x, y, z);

		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &attr->position);
		dir *= -1.0f;

		attr->acceleration = dir * RND->getFromFloatTo(0.001f, 0.002f);
		attr->velocity *= 0.0f;

		attr->lifeTime = 0.0f;
	}

	attr->startColor = D3DCOLOR_ARGB(255, 255, 190, 231);
	attr->endColor = D3DCOLOR_ARGB(255, 74, 20, 140);
}

void gravityShot::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void gravityShot::render()
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

void gravityShot::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void gravityShot::createController(PxControllerManager ** cm, PxMaterial * m)
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
	_controller->getActor()->setName("gravityShot");
}
