#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"


enemy::enemy()
	: _distance(0.0f)
{
	ZeroMemory(&_sphere, sizeof(tagSphere));
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
			_act = ACT_ATTACK01;
		}
	}	
	
	//애니메이션 셋팅
	AnimationSetting();
	
	if (!isAbsoluteMotion() && !YouAndIDistance())
	enemyController::Moving();

	interfaceCharacter::Update();

	//절대판정이 끝나면 기본상태로 바꿔준다.
	if (isAbsoluteMotion())
	{
		//빛이 만들어준 애니메이션이 끝나면 트루가 되는 엄청 좋은 함수
		if (_skinnedMesh->IsAnimationEnd())
		{
			_act = ACT_IDLE;
		}
	}
}

void enemy::Render()
{
	interfaceCharacter::Render();
	
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


void enemy::SetSRT(D3DXVECTOR3 sca, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	_worldSca = sca;
	_worldRot = rot;
	_worldPos = pos;

	enemyController::Init();
}

void enemy::SetDistance(float dis)
{
	_distance = dis;
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

