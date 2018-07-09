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
	//���������� ������ �⺻���·� �ٲ��ش�.
	if (isAbsoluteMotion())
	{
		if (_skinnedMesh->IsAnimationEnd())
		{
			_act = ACT_IDLE;			
			//���� �������� �־��� �Լ�
			enemyController::Init();
		}
	}

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

			_act = ACT_ATTACK00;
		}
	}	

	interfaceCharacter::Update();
}

void enemy::Render()
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�ִϸ��̼� ����
	AnimationSetting();
	interfaceCharacter::Render();
	
	if (_isDebug)
	{
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
}

void enemy::Moving()
{
	if (!isAbsoluteMotion() && !YouAndIDistance())
		enemyController::Moving();
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
	//Ÿ�ٰ� ���� ���� ���
	float dis01 = D3DXVec3Length(&(*target - v1->GetPosition()));
	float dis02 = D3DXVec3Length(&(*target - v2->GetPosition()));

	//Ÿ�ٰ� ���̰� �� ��� ���߾�� �ϴ� ��
	if (dis01 > dis02) return v1;
	if (dis02 > dis01) return v2;

	return NULL;
}

