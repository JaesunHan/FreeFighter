#include "stdafx.h"
#include "leafAtk.h"


leafAtk::leafAtk()
{
}


leafAtk::~leafAtk()
{
}

HRESULT leafAtk::init(float range, float angleZ, float angleY, int numParticles, const WCHAR * folder, const WCHAR * fileName, D3DXVECTOR3 startPos)
{
	_angleY = angleY;
	_angleZ = angleZ;
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;			//???

	_angleSpd.resize(numParticles);
	for (int i = 0; i < numParticles; ++i)
	{
		_angleSpd[i] = RND->getFromFloatTo(0.5f * DEG2RAD, 10.0f * DEG2RAD);
		addParticle();
	}
	
	_name = _T("leafAtk");
	_startPosition = startPos;

	WCHAR		filePath[2048];
	wsprintf(filePath, _T(".\\%s\\%s"), folder, fileName);
	//WCHAR		filePath[2048];
	//wsprintf(filePath, _T("%s\\%s", folder.c_str(), fileName.c_str()));
	particleSystem::init(filePath);

	_range = range;
	_lifeTime = 0.0f;
	
	_worldMatrix._41 = startPos.x;
	_worldMatrix._42 = startPos.y;
	_worldMatrix._43 = startPos.z;

	return S_OK;
}

void leafAtk::update(float timeDelta)
{
	_lifeTime += TIMEMANAGER->getElapsedTime();
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();
	int i = 0;
	for (; iter != _particles.end(); ++iter, ++i)
	{
		iter->acceleration.x += _angleSpd[i];
		iter->position.x = iter->acceleration.y * cosf(iter->acceleration.x);
		iter->position.y = iter->acceleration.y * -sinf(iter->acceleration.x);

		iter->position.z += iter->velocity.z;
		float y = (iter->position.z / _range) * D3DX_PI * 2;
		iter->position.y += sinf(y);

		float t = iter->velocity.z / _range;
		if (t > 1.0f)
			t = 1.0f;
		iter->currentColor = (1 - t) * iter->startColor + t * iter->endColor;

		if (iter->position.z > _range)
		{
			if (_lifeTime > 3.5f)
				iter->isAlive = false;
			else
				this->resetParticle(&(*iter));
		}
	}

	D3DXMATRIX matT, matR;
	D3DXMatrixTranslation(&matT, _startPosition.x, _startPosition.y, _startPosition.z);
	D3DXMatrixRotationYawPitchRoll(&matR, _angleY, 0.0f, _angleZ);
	_worldMatrix = matR * matT;
}

void leafAtk::resetParticle(PARTICLE_ATTRIBUTE * attr)
{
	float angle = RND->getFromFloatTo(0.0f, D3DX_PI * 2);
	float r = RND->getFromFloatTo(0.1f, 0.3f);
	attr->position.x = r * cosf(attr->position.x);
	attr->position.y = r * -sinf(attr->position.x);
	attr->position.z = 0.0f;

	attr->velocity = D3DXVECTOR3(0.0f, 0.0f, RND->getFromFloatTo(0.01f, 0.1f));
	attr->acceleration.x = angle;
	attr->acceleration.y = r;

	attr->isAlive = true;

	attr->startColor = D3DCOLOR_ARGB(255, 27, 94, 32);
	attr->endColor = D3DCOLOR_ARGB(255, 220, 237, 200);
}

void leafAtk::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void leafAtk::render()
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

void leafAtk::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void leafAtk::createController(PxControllerManager ** cm, PxMaterial * m)
{
	PxCapsuleControllerDesc desc;
	desc.radius = _range / 3 * 2;
	desc.height = 0.01f;
	desc.position = PxExtendedVec3(_startPosition.x, _startPosition.y + desc.height + desc.radius * 2, _startPosition.z);
	desc.stepOffset = 0.00001f;
	desc.volumeGrowth = 1.9f;
	desc.slopeLimit = cosf(15.0f * DEG2RAD);
	desc.nonWalkableMode = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING;
	desc.upDirection = PxVec3(1, 0, 0);
	desc.contactOffset = 0.001f;
	desc.material = m;

	_controller = (*cm)->createController(desc);
	_controller->getActor()->setName("leafAttack");
}
