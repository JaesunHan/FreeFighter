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
		//�ٴ� ���� == Ÿ���� �ְ�, �����Ÿ� ������ ���� ��, �׸��� �����̳� �ǰݵ����� �ƴҶ�
		if (!YouAndIDistance() && !isAbsoluteMotion())
		{
			_act = ACT_RUN_FRONT;
		}
		//�����ϴ� ���� == Ÿ���� �ְ� �������� ������ ������ ��
		else
		{
			_act = ACT_ATTACK01;
		}
	}	
	
	//�ִϸ��̼� ����
	AnimationSetting();
	
	if (!isAbsoluteMotion() && !YouAndIDistance())
	enemyController::Moving();

	interfaceCharacter::Update();

	//���������� ������ �⺻���·� �ٲ��ش�.
	if (isAbsoluteMotion())
	{
		//���� ������� �ִϸ��̼��� ������ Ʈ�簡 �Ǵ� ��û ���� �Լ�
		if (_skinnedMesh->IsAnimationEnd())
		{
			_act = ACT_IDLE;
		}
	}
}

void enemy::Render()
{
	interfaceCharacter::Render();
	
	// === ������ �� =====
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

