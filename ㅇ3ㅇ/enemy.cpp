#include "stdafx.h"
#include "enemy.h"
#include "skinnedMesh.h"

//���̽�Ÿ���� ��Ǿƴ�
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
	//���������� ������ �⺻���·� �ٲ��ش�.
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
		//�ٴ� ���� == Ÿ���� �ְ�, �����Ÿ� ������ ���� ��, �׸��� �����̳� �ǰݵ����� �ƴҶ�
		if (!YouAndIDistance() && !isAbsoluteMotion())
		{
			_nextAct = ACT_RUN_FRONT;
			AnimationSetting();
		}
		//�����ϴ� ���� == Ÿ���� �ְ� �������� ������ ������ ��
		else
		{
			_nextAct = ACT_ATTACK00;
			AnimationSetting();
		}
	}	
	
	interfaceCharacter::Update();
}

void enemy::Render(float elapsedTime)
{
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�ִϸ��̼� ����
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

		//���� + ũ�� == �ӵ� 
		_velocity.x = _worldDir.x * 0.05f;
		_velocity.z = _worldDir.z * 0.05f;

		if (!isAbsoluteMotion())
		{	
			D3DXVECTOR3 tempPos = D3DXVECTOR3(_controller->getFootPosition().x, _controller->getFootPosition().y, _controller->getFootPosition().z);
			_controller->move(_velocity, 0, TIMEMANAGER->getElapsedTime(), PxControllerFilters());

			//���� _worldPos�� �Űܼ� ���ص� ������ _worldPos�� ����ϴ°� �������� ���Ƽ�
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
	//Ÿ�ٰ� ���� ���� ���
	float dis01 = D3DXVec3Length(&(*target - v1->GetPosition()));
	float dis02 = D3DXVec3Length(&(*target - v2->GetPosition()));

	//Ÿ�ٰ� ���̰� �� ��� ���߾�� �ϴ� ��
	if (dis01 > dis02) return v1;
	if (dis02 > dis01) return v2;

	return NULL;
}

