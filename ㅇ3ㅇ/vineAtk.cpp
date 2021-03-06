#include "stdafx.h"
#include "vineAtk.h"
#include "player.h"
#include "enemyManager.h"
#include "enemy.h"



vineAtk::vineAtk()
{
}


vineAtk::~vineAtk()
{
}

HRESULT vineAtk::init(float radius, int numParticles, const WCHAR* folder, const WCHAR* fileName, D3DXVECTOR3 startPos)
{
	_radius = radius;
	_angleZ = 0.0f;
	_size = 50.0f;
	_vbSize = numParticles;
	_vbOffset = 0;
	_vbBatchSize = numParticles;

	_angleSpd.resize(numParticles);
	_frontDir.resize(numParticles);
	
	for (int i = 0; i < numParticles; ++i)
	{
		_angleSpd[i] = RND->getFromFloatTo(0.5f * DEG2RAD, 10.0f * DEG2RAD);
		float angle = ((D3DX_PI*2) / (float)numParticles) * i;
		_frontDir[i] = angle;
		//_frontDir[i] = D3DXVECTOR3(cosf(angle),0, -sinf(angle));
		addParticle();
	}
	_name = _T("_vineAtk");
	_startPosition = startPos;

	WCHAR		filePath[2018];
	wsprintf(filePath, _T(".\\%s\\%s"), folder, fileName);

	particleSystem::init(filePath);
	_lifeTime = 0.0f;

	_worldMatrix._41 = startPos.x;
	_worldMatrix._42 = startPos.y;
	_worldMatrix._43 = startPos.z;

	_particleIdx = 0;

	return S_OK;
}

void vineAtk::update(float timeDelta)
{
	
	_lifeTime += TIMEMANAGER->getElapsedTime();
	//캐럭터의 중점을 원점으로 하여, 팔방으로 덩굴이 뻗어져나간다.
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();
	int i = 0; 
	for (; iter != _particles.end(); ++iter, ++i)
	{
		if (_lifeTime <= 3.8f)
		{
			if (_lifeTime < 1.3f)
				continue;
			iter->isAlive = true; 
			_angleZ += 0.8f * DEG2RAD;
			
			iter->position.z += 0.18f;

			float t = iter->position.z / _range;
			if (t > 1.0f)
				t = 1.0f;
			iter->currentColor = (1 - t) * iter->startColor + t * iter->endColor;

			if (iter->position.z > _radius)
			{
				iter->position.z = _radius;
				if (_lifeTime > 3.7f)
					iter->isAlive = false;

			}
		}
	}
	//덩굴과 에너미간의 충돌은 구충돌로 처리한다.
	_attackCount++;
	if (_attackCount % 3 == 0 && _lifeTime > 1.3f)
	{
		vector<enemy*> vecEnemy = _player->getEM()->GetEnemy();
		for (int j = 0; j < vecEnemy.size(); ++j)
		{
			D3DXVECTOR3 enemyPos = vecEnemy[j]->GetPosition();
			enemyPos.y = 0.0f;
			//플레이어가 있는 위치를 중점으로 구를 형성해야한다.
			D3DXVECTOR3	skillCeneter = D3DXVECTOR3(0,0,0);
			D3DXVec3TransformCoord(&skillCeneter, &skillCeneter, &_worldMatrix);
			float distance = getDistance(enemyPos, skillCeneter);
			if (distance <= _radius)
			{
				_player->getEM()->GetEnemy()[j]->HitDamage(_player->getAtk() / (float)50);
			}
		}
		_attackCount = 0;
	}
}

void vineAtk::resetParticle(PARTICLE_ATTRIBUTE * attr)
{
	//float angle = RND->getFromFloatTo(0.00f, D3DX_PI * 2);
	float angle = RND->getFromFloatTo(0.01f, 0.1f);
	float r = RND->getFromFloatTo(0.1f, 0.3f);
	attr->position = _startPosition;
	//attr->position.x = 0.0f;
	//attr->position.y = 0.0f;
	//attr->position.z = 0.0f;

	attr->velocity = D3DXVECTOR3(0.0f, 0.0f, RND->getFromFloatTo(0.05f, 0.1f));
	attr->acceleration.x = angle;
	attr->acceleration.y = r;

	//attr->isAlive = true;

	attr->startColor = D3DCOLOR_ARGB(255, 210, 100, 80);
	attr->endColor = D3DCOLOR_ARGB(255, 210, 100, 80);
}

void vineAtk::addParticle()
{
	PARTICLE_ATTRIBUTE attr;

	resetParticle(&attr);

	//attr.position.z = RND->getFromFloatTo(0.0f, _range);
	_particles.push_back(attr);
}

void vineAtk::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void vineAtk::render()
{
	if (_particles.empty()) return;
	this->preRender();

	LPDIRECT3DTEXTURE9 tmpTex = TEXTUREMANAGER->findTexture(_textureName);
	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_textureName));
	D3DDEVICE->SetFVF(tagPC_Vertex::FVF);
	D3DDEVICE->SetStreamSource(0, _vb, 0, sizeof(tagPC_Vertex));
	//D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);

	if (_vbOffset >= _vbSize)
	{
		_vbOffset = 0;
		_particleIdx = 0;

	}
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
			//_particleIdx++;
			vb->p = iter->position;
			vb->c = (D3DCOLOR)iter->currentColor;
			vb++;

			numParticlesInBatch++;
			if (numParticlesInBatch == 1)
			{
				_vb->Unlock();

				D3DXMATRIX matT, matR;
				D3DXMatrixTranslation(&matT, _startPosition.x, _startPosition.y, _startPosition.z);
				D3DXMatrixRotationYawPitchRoll(&matR, _frontDir[_particleIdx++], 0.0f, _angleZ);
				_worldMatrix = matR * matT;
				D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);
				D3DDEVICE->DrawPrimitive(
					D3DPT_POINTLIST,
					_vbOffset,
					_vbOffset+1);

				_vbOffset += 1;

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
		//D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);
		D3DDEVICE->DrawPrimitive(
			D3DPT_POINTLIST,
			_vbOffset,
			numParticlesInBatch);
	}

	_vbOffset += _vbBatchSize;

	this->postRender();
	
	/*
	if (_particles.empty()) return;
	this->preRender();

	LPDIRECT3DTEXTURE9 tmpTex = TEXTUREMANAGER->findTexture(_textureName);
	D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(_textureName));
	D3DDEVICE->SetFVF(tagPC_Vertex::FVF);
	D3DDEVICE->SetStreamSource(0, _vb, 0, sizeof(tagPC_Vertex));
	//D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);

	if (_vbOffset >= _vbSize)
	{
		_vbOffset = 0;
		_particleIdx = 0;

	}
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
			//_particleIdx++;
			vb->p = iter->position;
			vb->c = (D3DCOLOR)iter->currentColor;
			vb++;

			numParticlesInBatch++;
			if (numParticlesInBatch == _vbBatchSize)
			{
				_vb->Unlock();

				D3DXMATRIX matT, matR;
				D3DXMatrixTranslation(&matT, _startPosition.x, _startPosition.y, _startPosition.z);
				D3DXMatrixRotationYawPitchRoll(&matR, _frontDir[_particleIdx++], 0.0f, 0.0f);
				_worldMatrix = matR * matT;
				D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);
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
		//D3DDEVICE->SetTransform(D3DTS_WORLD, &_worldMatrix);
		D3DDEVICE->DrawPrimitive(
			D3DPT_POINTLIST,
			_vbOffset,
			numParticlesInBatch);
	}

	_vbOffset += _vbBatchSize;

	this->postRender();
	*/
}

void vineAtk::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

