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
	// 이제부터 얘네들이 어떻게 움직여야할지 결정해야함
	// 참고로 매개변수에 timeDelta이건
	// 책에 있길래 추가는 해놨는데 난 한 번도 안썼엌ㅋㅋ
	// 우선 파티클 하나 하나의 움직임을 제어해보자
	// 일단 주석정리해서 보내줄게 ㅇㅇ 주석 정리하면서 함 다시 봐바 이해안되는거 물어보고 담배피고옴 ㅇㅋ

	list<PARTICLE_ATTRIBUTE>::iterator iter = _particles.begin();

	for (; iter != _particles.end(); ++iter)
	{
		D3DXMATRIX matR;
		// 아까 velocity를 각속도로 쓴다 했지?? 중첩되나? ㅇㅇ
		D3DXMatrixRotationY(&matR, iter->velocity.y);
		// 그 각도 만큼 포지션을 돌려주는거임
		D3DXVec3TransformCoord(&iter->position, &iter->position, &matR);

		// 거리에 따른 선형보간으로 색을 바꿔줌
		// 선형보간이라는것의 기준은 시간만 있는건 아냐
		// t = 현재 / 전체
		// 지금 _radius가 파티클들이 있을 수 있는 반지름 최대값이야
		// 그러므로 전체가 됨
		// 그리고 센터랑 pos 둘 다 y값이 0이니까
		// 단순히 원으로 따져서 거리가 얼만큼 떨어져있냐를
		// distance에 담아둔거지
		// 그리고 그게 바로 현재
		// t = 현재 / 전체가 된거지
		// 사실 이 파티클은 파티클들 움직임은 이게 끝임
		// 이젠 월드에서의 움직임
		// 플레이어를 따라와야겠지??
		D3DXVECTOR3 center(0, 0, 0);
		D3DXVECTOR3 pos = iter->position;
		pos.y = 0.0f;
		float distance = getDistance(center, pos);
		float d = distance / _radius;
		iter->currentColor = (1 - d) * iter->startColor + d * iter->endColor;

		// 생성된 시간 측정
		iter->lifeTime += TIMEMANAGER->getElapsedTime();
	}

	// 월드 위치잡기 끝
	D3DXVECTOR3 playerPos = _player->GetPosition();
	// 이 밑에랑 완벽하게 똑같은게
	//D3DXMatrixTranslation(&_worldMatrix, playerPos.x, playerPos.y, playerPos.z);
	_worldMatrix._41 = playerPos.x;
	_worldMatrix._42 = playerPos.y;
	_worldMatrix._43 = playerPos.z;
	//이게 끝? ㅇㅇ 더 할거 없고? 현재 파티클은 그러해

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
	// 여기서부터가 가장 관건임
	// 지금 하려는건
	// 음...
	// 일단 간단하게 플레이어 주위를 빙글빙글 도는거만 만들어보자

	// 말했지만 얘는 로컬 포지션이야 한마디로 모든건 원점을 기준으로 생성하고
	// worldMatrix를 옮겨서 내가 원하는 위치에 띄운다고 생각하면 됨
	float angle = RND->getFromFloatTo(0.0f, D3DX_PI * 2);		// 일단 각도를 랜덤하게 잡지??
	float x = RND->getFromFloatTo(1.0f, _radius) * cosf(angle); // 그 각도 * 반지름 하면 원 모양이 나옵니다. (feat.삼각함수)
	float y = RND->getFromFloatTo(0.0f, 1.0f);
	float z = RND->getFromFloatTo(1.0f, _radius) * -sinf(angle);
	attr->position = D3DXVECTOR3(x, y, z);						// 이제 초기 위치를 잡았어

	// 원래 속도라 함은 선형속도를 나타내거든 보통
	// (선형속도 : 직선으로 가는 속도)
	// 근데 나는 직선으로 이동시킬 생각이 없어 지금
	// 그러므로 velocity값을 회전속도 값으로 쓸거야
	// 그리고 우린 지금 y축으로만 회전하면 돼
	attr->velocity = D3DXVECTOR3(0.0f, RND->getFromFloatTo(0.5f, 10.0f) * DEG2RAD, 0.0f);

	// 가속도는 지금 없어도 될거같음
	
	attr->isAlive = true;
	attr->startColor = D3DCOLOR_ARGB(255, 134, 114, 231);
	attr->endColor = D3DCOLOR_ARGB(255, 38, 21, 121);

	attr->currentColor = attr->startColor;

	attr->lifeTime = 0.0f;
	// 여기 까지가 처음 생성
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
