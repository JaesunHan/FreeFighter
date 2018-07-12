#include "stdafx.h"
#include "poisonArrow.h"
#include "testPlayer.h"


poisonArrow::poisonArrow()
	: _radius(2.0f)
	, _isHit(false)
	, _dir(0, 0, 0)
	, _player(NULL)
	, _dirAngle(0.0f)
{
}


poisonArrow::~poisonArrow()
{
}

HRESULT poisonArrow::init(float radius, int numParticles, const WCHAR* filePath, D3DXVECTOR3 pos, PxVec3 dir, float dirAngle)
{
	_radius = radius;
	_size = 0.05f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for (int i = 0; i < numParticles; ++i)
		addParticle();

	_dir = dir;
	_speed = 0.7f;
	_startPosition = pos;

	particleSystem::init(filePath);

	_dirAngle = dirAngle;

	_range = 10.0f;

	return S_OK;
}

void poisonArrow::update(float timeDelta)
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

			if (getDistance(D3DXVECTOR3(0, 0, 0), iter->position) >(_radius * 4.0f))
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
				_radius = 0.25f;
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

	D3DXMATRIX matT, matR;
	D3DXMatrixRotationY(&matR, _dirAngle);
	D3DXMatrixTranslation(&matT, _controller->getPosition().x, _controller->getPosition().y, _controller->getPosition().z);
	_worldMatrix = matR * matT;
}

void poisonArrow::resetParticle(bool isHit)
{
	_isHit = isHit;

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
		this->resetParticle(&(*iter));
}

void poisonArrow::resetParticle(PARTICLE_ATTRIBUTE* attr)
{
	if (!_isHit)
	{
		float theta = RND->getFromFloatTo(-15.0f * DEG2RAD, 15.0f * DEG2RAD);
		float pi = RND->getFromFloatTo(0.0f, 360.0f * DEG2RAD);
		float r = RND->getFromFloatTo(0.0f, _radius);

		float x = r * sinf(theta) * cosf(pi);
		float y = r * sinf(theta) * sinf(pi);
		float z = r * cosf(theta);

		attr->position = D3DXVECTOR3(x, y, z);

		attr->isAlive = true;

		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &attr->position);

		attr->velocity = dir * RND->getFromFloatTo(0.01f, 0.05f);
		D3DXVec3Normalize(&attr->acceleration, &attr->velocity);
		attr->acceleration *= -RND->getFromFloatTo(0.01f, 0.1f);
	}
	else
	{
		float theta = RND->getFromFloatTo(-30.0f * DEG2RAD, 30.0f * DEG2RAD);
		float pi = RND->getFromFloatTo(0.0f, 360.0f * DEG2RAD);
		float r = RND->getFromFloatTo(0.0f, _radius);

		float x = r * sinf(theta) * cosf(pi);
		float y = r * sinf(theta) * sinf(pi);
		float z = r * cosf(theta);

		attr->position = D3DXVECTOR3(-x, -y, -z);

		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &attr->position);

		attr->velocity = -dir * RND->getFromFloatTo(0.01f, 0.05f);
		D3DXVec3Normalize(&attr->acceleration, &attr->velocity);
		attr->acceleration *= -RND->getFromFloatTo(0.01f, 0.1f);
	}

	attr->startColor = D3DCOLOR_ARGB(255, 225, 190, 231);
	attr->endColor = D3DCOLOR_ARGB(255, 74, 20, 140);
}

void poisonArrow::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void poisonArrow::render()
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

void poisonArrow::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void poisonArrow::createController(PxControllerManager** cm, PxMaterial * m)
{
	PxCapsuleControllerDesc desc;
	desc.radius = 0.5f / 3 * 2;
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
	_controller->getActor()->setName("poisonArrow");
}
