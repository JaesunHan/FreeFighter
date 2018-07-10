#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"


enemy::enemy()
	: _distance(0.0f)
{
	ZeroMemory(&_sphere, sizeof(tagSphere));
	D3DXMatrixIdentity(&_worldTM);
}

enemy::~enemy()
{
}

void enemy::Init(wstring keyPath, wstring keyName)
{
	interfaceCharacter::Init(keyPath, keyName);
	_skinnedMesh->setParentMatrix(&_worldTM);
}

void enemy::Update()
{
	//절대판정이 끝나면 기본상태로 바꿔준다.
	if (isAbsoluteMotion())
	{
		if (_skinnedMesh->IsAnimationEnd())
		{
			_act = ACT_IDLE;			
		}
	}

	if (_targetPos)
	{
		//뛰는 조건 == 타겟이 있고, 일정거리 떨어져 있을 때, 그리고 공격이나 피격도중이 아닐때
		if (!YouAndIDistance() && !isAbsoluteMotion())
		{
			_act = ACT_RUN_FRONT;
		}
		//공격하는 조건 == 타겟이 있고 일정범위 안으로 들어왔을 때
		else
		{

			_act = ACT_ATTACK00;
		}
	}	

	interfaceCharacter::Update();
}

void enemy::Render()
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);

	//애니메이션 셋팅
	AnimationSetting();
	interfaceCharacter::Render();
	
	if (_isDebug)
	{
		// === 디버깅용 원 =====
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, _worldPos.x + _sphere.center.x,
			_worldPos.y + _sphere.center.y,
			_worldPos.z + _sphere.center.z);
		D3DDEVICE->SetTransform(D3DTS_WORLD, &matT);
		_sphere.sphere->DrawSubset(0);
		D3DXMatrixIdentity(&matT);
		D3DDEVICE->SetTransform(D3DTS_WORLD, &matT);
		// ====================
	}
}

void enemy::Moving()
{
	D3DXMATRIX matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);
	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	if (_targetPos)
	{
		_worldDir = (*_targetPos) - _worldPos;
		D3DXVec3Normalize(&_worldDir, &_worldDir);

		_velocity.x = _worldDir.x * 0.5f;
		_velocity.z = _worldDir.z * 0.5f;

		float angle = getAngle(0, 0, _worldDir.x, _worldDir.z) - D3DX_PI / 2;

		//D3DXMatrixRotationY(&matR, angle);
		D3DXMatrixRotationYawPitchRoll(&matR, angle, 0.0f, 0.0f);

		_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

		_worldPos = D3DXVECTOR3(_controller->getPosition().x, _controller->getPosition().y, _controller->getPosition().z);
		D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);
	}

	_worldTM = matS * matR * matT;
}

bool enemy::YouAndIDistance()
{
	if (_targetPos)
	return D3DXVec3Length(&(_worldPos - *_targetPos)) < _distance;
}

float enemy::YouAndIDistance(D3DXVECTOR3 pos01, D3DXVECTOR3 pos02)
{
	return D3DXVec3Length(&(pos01 - pos02));
}

enemy* enemy::Collision(D3DXVECTOR3* target, enemy* v1, enemy* v2)
{
	//타겟과 적의 길이 계산
	float dis01 = D3DXVec3Length(&(*target - v1->GetPosition()));
	float dis02 = D3DXVec3Length(&(*target - v2->GetPosition()));

	//타겟과 길이가 더 길면 멈추어야 하는 적
	if (dis01 > dis02) return v1;
	if (dis02 > dis01) return v2;

	return NULL;
}

