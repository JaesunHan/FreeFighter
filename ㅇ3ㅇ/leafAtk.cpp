#include "stdafx.h"
#include "leafAtk.h"


leafAtk::leafAtk()
{
}


leafAtk::~leafAtk()
{
}

HRESULT leafAtk::init(float range, float angleZ, int numParticles, const WCHAR * folder, const WCHAR * fileName, D3DXVECTOR3 startPos)
{
	_angleZ = 0.0f;
	_size = 0.5f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;			//???

	_angleSpd.resize(numParticles);

	for (int i = 0; i < numParticles; ++i)
	{
		_angleSpd[i] = RND->getFromFloatTo(0.1f * DEG2RAD, 0.4f * DEG2RAD);
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
	_lifeTime += timeDelta;

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();
	int i = 0; 
	for (; iter != _particles.end(); ++iter, ++i)
	{
		float x, y, z;
		x = (-180 + (180 / _particles.size()) * _lifeTime)*DEG2RAD;
		y = sinf(x);
		z = 0.0f;

		D3DXVECTOR3	vPos = D3DXVECTOR3(x, y, z);
		iter->position = vPos;
		D3DXMATRIX matR;
		D3DXMatrixRotationX(&matR, _angleZ);
		D3DXVec3TransformCoord(&iter->position, &iter->position, &matR);

		D3DXVECTOR3 temp = iter->position;
		temp.y = 0.0f;

		//float t = getDistance(temp, D3DXVECTOR3(0, 0, 0)) / _range;
		//iter->currentColor = (1 - t)*iter->startColor + iter->endColor;

		if (iter->position.x > _range)
		{
			if (_lifeTime > 3.5f)
				iter->isAlive = false;
			else
				this->resetParticle(&(*iter));
		}
	}
}

void leafAtk::resetParticle(PARTICLE_ATTRIBUTE * attr)
{
	attr->position = D3DXVECTOR3(0.0f, 0.0f, 0);
	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, _angleZ);
	D3DXVec3TransformCoord(&attr->position, &attr->position, &matR);
	//attr->velocity = D3DXVECTOR3(0.0f, RND->getFromFloatTo(0.001f, 0.01f), 0.0f);
	//attr->acceleration = D3DXVECTOR3(0.0f, RND->getFromFloatTo(0.01f, 0.05f), 0.0f);
	attr->isAlive = true;

	//attr->startColor = D3DCOLOR_ARGB(255, 255, 190, 231);
	//attr->endColor = D3DCOLOR_ARGB(255, 74, 20, 140);
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
