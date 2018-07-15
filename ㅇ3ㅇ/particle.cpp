#include "stdafx.h"
#include "particle.h"


particleSystem::particleSystem()
	: _startPosition(0, 0, 0)
	, _size(0.1f)
	, _textureName(_T(""))
	, _vb(NULL)
	, _maxParticles(4000)
	, _controller(NULL)
	, _range(1.0f)
	, _emitRate(1000.0f)
	, _vbSize(2000)
	, _vbOffset(0)
	, _vbBatchSize(500)
	, _name(_T(""))
{
	D3DXMatrixIdentity(&_worldMatrix);
}


particleSystem::~particleSystem()
{
}

HRESULT particleSystem::init(const WCHAR* filePath)
{
	D3DDEVICE->CreateVertexBuffer(
		_vbSize * sizeof(tagPC_Vertex),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		tagPC_Vertex::FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		0);

	TEXTUREMANAGER->addTexture(filePath, D3DDEVICE, filePath);
	_textureName = wstring(filePath);

	return S_OK;
}

void particleSystem::release()
{
	if (_controller)
	{
		_controller->release();
		_controller = NULL;
	}

	SAFE_RELEASE(_vb);
}

void particleSystem::reset()
{
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		resetParticle(&(*iter));
	}
}

void particleSystem::addParticle()
{
	PARTICLE_ATTRIBUTE attr;

	resetParticle(&attr);

	_particles.push_back(attr);
}

void particleSystem::preRender()
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DDEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	D3DDEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	D3DDEVICE->SetRenderState(D3DRS_POINTSIZE, FtoDW(_size));
	D3DDEVICE->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));
	D3DDEVICE->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDW(100.0f));
	
	D3DDEVICE->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.0f));
	D3DDEVICE->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.0f));
	D3DDEVICE->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.0f));

	D3DDEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	D3DDEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// 알파블랜딩 방식 결정
	D3DDEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	D3DDEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DDEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void particleSystem::render()
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
			vb->c = (D3DCOLOR)iter->startColor;
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

void particleSystem::postRender()
{
	//D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
	D3DDEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	D3DDEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	D3DDEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	D3DXMATRIX iden;
	D3DXMatrixIdentity(&iden);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &iden);
}

void particleSystem::removeDeadParticles()
{
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end();)
	{
		if (!iter->isAlive)
			iter = _particles.erase(iter);
		else
			++iter;
	}
}

bool particleSystem::isEmpty()
{
	return (_particles.empty());
}

bool particleSystem::isDead()
{
	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		if (iter->isAlive)
			return false;
	}

	return true;
}
