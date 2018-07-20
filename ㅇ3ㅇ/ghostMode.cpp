#include "stdafx.h"
#include "ghostMode.h"
#include "player.h"
#include "reaper.h"


ghostMode::ghostMode()
	: _radius(1.0f)
	, _ghostModeTime(0.0f)
	, _player(NULL)
{
}


ghostMode::~ghostMode()
{
}

HRESULT ghostMode::init(float radius, int numParticles, const WCHAR * filePath)
{
	_radius = radius;
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	_ghostModeTime = 0.0f;

	for (int i = 0; i < numParticles; ++i)
		this->addParticle();

	particleSystem::init(filePath);

	return S_OK;
}

void ghostMode::update(float timeDelta)
{
	// �������� ��׵��� ��� ������������ �����ؾ���
	// ����� �Ű������� timeDelta�̰�
	// å�� �ֱ淡 �߰��� �س��µ� �� �� ���� �Ƚ������
	// �켱 ��ƼŬ �ϳ� �ϳ��� �������� �����غ���
	// �ϴ� �ּ������ؼ� �����ٰ� ���� �ּ� �����ϸ鼭 �� �ٽ� ���� ���ؾȵǴ°� ����� ����ǰ�� ����

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		D3DXMATRIX matR;
		// �Ʊ� velocity�� ���ӵ��� ���� ����?? ��ø�ǳ�? ����
		D3DXMatrixRotationY(&matR, iter->velocity.y);
		// �� ���� ��ŭ �������� �����ִ°���
		D3DXVec3TransformCoord(&iter->position, &iter->position, &matR);

		// �Ÿ��� ���� ������������ ���� �ٲ���
		// ���������̶�°��� ������ �ð��� �ִ°� �Ƴ�
		// t = ���� / ��ü
		// ���� _radius�� ��ƼŬ���� ���� �� �ִ� ������ �ִ밪�̾�
		// �׷��Ƿ� ��ü�� ��
		// �׸��� ���Ͷ� pos �� �� y���� 0�̴ϱ�
		// �ܼ��� ������ ������ �Ÿ��� ��ŭ �������ֳĸ�
		// distance�� ��Ƶа���
		// �׸��� �װ� �ٷ� ����
		// t = ���� / ��ü�� �Ȱ���
		// ��� �� ��ƼŬ�� ��ƼŬ�� �������� �̰� ����
		// ���� ���忡���� ������
		// �÷��̾ ����;߰���??
		D3DXVECTOR3 center(0, 0, 0);
		D3DXVECTOR3 pos = iter->position;
		pos.y = 0.0f;
		float distance = getDistance(center, pos);
		float d = distance / _radius;
		iter->currentColor = (1 - d) * iter->startColor + d * iter->endColor;

		// ������ �ð� ����
		iter->lifeTime += TIMEMANAGER->getElapsedTime();
	}

	// ���� ��ġ��� ��
	D3DXVECTOR3 playerPos = _player->GetPosition();
	// �� �ؿ��� �Ϻ��ϰ� �Ȱ�����
	//D3DXMatrixTranslation(&_worldMatrix, playerPos.x, playerPos.y, playerPos.z);
	_worldMatrix._41 = playerPos.x;
	_worldMatrix._42 = playerPos.y;
	_worldMatrix._43 = playerPos.z;
	//�̰� ��? ���� �� �Ұ� ����? ���� ��ƼŬ�� �׷���

	_ghostModeTime += TIMEMANAGER->getElapsedTime();
	if (_ghostModeTime > 5.0f)
	{
		((reaper*)_player)->turnOffGhostMode();

		list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

		for (; iter != _particles.end(); ++iter)
			iter->isAlive = false;
	}
}

void ghostMode::resetParticle(PARTICLE_ATTRIBUTE * attr)
{
	// ���⼭���Ͱ� ���� ������
	// ���� �Ϸ��°�
	// ��...
	// �ϴ� �����ϰ� �÷��̾� ������ ���ۺ��� ���°Ÿ� ������

	// �������� ��� ���� �������̾� �Ѹ���� ���� ������ �������� �����ϰ�
	// worldMatrix�� �Űܼ� ���� ���ϴ� ��ġ�� ���ٰ� �����ϸ� ��
	float angle = RND->getFromFloatTo(0.0f, D3DX_PI * 2);		// �ϴ� ������ �����ϰ� ����??
	float x = RND->getFromFloatTo(1.0f, _radius) * cosf(angle); // �� ���� * ������ �ϸ� �� ����� ���ɴϴ�. (feat.�ﰢ�Լ�)
	float y = RND->getFromFloatTo(0.0f, 1.0f);
	float z = RND->getFromFloatTo(1.0f, _radius) * -sinf(angle);
	attr->position = D3DXVECTOR3(x, y, z);						// ���� �ʱ� ��ġ�� ��Ҿ�

	// ���� �ӵ��� ���� �����ӵ��� ��Ÿ���ŵ� ����
	// (�����ӵ� : �������� ���� �ӵ�)
	// �ٵ� ���� �������� �̵���ų ������ ���� ����
	// �׷��Ƿ� velocity���� ȸ���ӵ� ������ ���ž�
	// �׸��� �츰 ���� y�����θ� ȸ���ϸ� ��
	attr->velocity = D3DXVECTOR3(0.0f, RND->getFromFloatTo(0.5f, 10.0f) * DEG2RAD, 0.0f);

	// ���ӵ��� ���� ��� �ɰŰ���
	
	attr->isAlive = true;
	attr->startColor = D3DCOLOR_ARGB(255, 134, 114, 231);
	attr->endColor = D3DCOLOR_ARGB(255, 38, 21, 121);

	attr->currentColor = attr->startColor;

	attr->lifeTime = 0.0f;
	// ���� ������ ó�� ����
}

void ghostMode::preRender()
{
	particleSystem::preRender();

	D3DDEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void ghostMode::render()
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

void ghostMode::postRender()
{
	particleSystem::postRender();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
