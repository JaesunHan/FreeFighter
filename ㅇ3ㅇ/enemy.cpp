#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"

//에이스타지만 사실아님
#include "jmAstar.h"

enemy::enemy()
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
			_nextAct = ACT_IDLE;
			AnimationSetting();
		}
	}


	if (_targetPos)
	{
		//뛰는 조건 == 타겟이 있고, 일정거리 떨어져 있을 때, 그리고 공격이나 피격도중이 아닐때
		if (!YouAndIDistance() && !isAbsoluteMotion())
		{
			_nextAct = ACT_RUN_FRONT;
			AnimationSetting();
		}
		//공격하는 조건 == 타겟이 있고 일정범위 안으로 들어왔을 때
		else
		{
			_nextAct = ACT_ATTACK00;
			AnimationSetting();
		}
	}	
	
	interfaceCharacter::Update();
}

void enemy::Render()
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);

	//애니메이션 셋팅
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

void enemy::SetStatus(int num)
{
	_status.hp = 10 * num;
	_status.atkDmg = 3 * num;
	_status.def = 1 * num;
	_status.mp = 5 * num;
	_status.speed = 1 * (num * 0.03f);
}

void enemy::Moving()
{
	D3DXMATRIX matS, matMoveR, matLookR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matMoveR);
	D3DXMatrixIdentity(&matLookR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, _worldSca.x, _worldSca.y, _worldSca.z);
	D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);

	if (_targetPos)
	{
		PxControllerState state;
		_controller->getState(state);

		float angle = getAngle(_worldPos.x, _worldPos.z, (*_targetPos).x, (*_targetPos).z) - D3DX_PI / 2;
		D3DXMatrixRotationYawPitchRoll(&matLookR, angle, 0.0f, 0.0f);

		_worldDir = D3DXVECTOR3(0, 0, -1);
		D3DXMatrixRotationYawPitchRoll(&matMoveR, angle, 0.0f, 0.0f);
		D3DXVec3TransformNormal(&_worldDir, &_worldDir, &matMoveR);

		//방향 + 크기 == 속도 
		_velocity.x = _worldDir.x * 0.05f;
		_velocity.z = _worldDir.z * 0.05f;

		if (!isAbsoluteMotion())
		{	
			D3DXVECTOR3 tempPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
			_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

			//굳이 _worldPos에 옮겨서 안해도 되지만 _worldPos로 계산하는게 생각보다 많아서
			_worldPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);

			D3DXMatrixTranslation(&matT, _worldPos.x, _worldPos.y, _worldPos.z);
		}
		
	}

	_worldTM = matS * matLookR * matT;
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

