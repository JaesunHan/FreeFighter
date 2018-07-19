#include "stdafx.h"
#include "camera.h"


camera::camera()
	: _angleX(0.0f)
	, _angleY(0.0f)
	, _distance(5.0f)
	, _eye(0, _distance, 0)
	, _up(0, 1, 0)
	, _lookAt(0, 0, 0)
{
}

camera::~camera()
{
}

void camera::init()
{
	// ȭ�� ũ�� �޾ƿ���
	RECT rc;
	GetClientRect(_hWnd, &rc);

	// �������� ��Ʈ���� ����
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection,
		D3DX_PI / 4.0f,					// �þ� ��
		rc.right / (float)rc.bottom,	// ȭ�� ����(���� / ����)
		0.1f,							// ȭ�鿡 ���� ����� z��
		1000.0f);						// ȭ�鿡 ���� �� z��

	// ���� ��Ʈ������ ����̽��� ����
	D3DDEVICE->SetTransform(D3DTS_PROJECTION, &projection);
}

void camera::release()
{
	D3DXMATRIX iden;
	D3DXMatrixIdentity(&iden);
	D3DDEVICE->SetTransform(D3DTS_PROJECTION, &iden);
	D3DDEVICE->SetTransform(D3DTS_VIEW, &iden);
}

void camera::update(D3DXVECTOR3* focus)
{
	_eye = D3DXVECTOR3(0, 0, -_distance);

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		_moveStart = _ptMouse;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		_angleX += (_ptMouse.y - _moveStart.y) / 100.0f;
		_angleY += (_ptMouse.x - _moveStart.x) / 100.0f;

		_moveStart = _ptMouse;
	}

	if (_angleX >= D3DX_PI / 2 - D3DX_16F_EPSILON)
		_angleX = D3DX_PI / 2 - D3DX_16F_EPSILON;
	if (_angleX <= -D3DX_PI / 2 + D3DX_16F_EPSILON)
		_angleX = -D3DX_PI / 2 + D3DX_16F_EPSILON;

	if (_angleY > D3DX_PI * 2)
		_angleY -= D3DX_PI * 2;
	if (_angleY < 0)
		_angleY += D3DX_PI * 2;

	D3DXMATRIX temp;
	D3DXMatrixRotationYawPitchRoll(&temp, _angleY, _angleX, 0.0f);
	D3DXVec3TransformCoord(&_eye, &_eye, &temp);

	if (focus)
	{
		_lookAt = *focus;
		_eye += _lookAt;
	}

	// �� ��Ʈ���� ����
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view,
		&_eye,
		&_lookAt,
		&_up);

	// ���� ��Ʈ������ ����̽��� ����
	D3DDEVICE->SetTransform(D3DTS_VIEW, &view);
}

// ��Ŀ���� �ٶ󺸴� ������ ���ʿ��� ��Ŀ���� ����ٴϴ� ī�޶�
void camera::update(D3DXVECTOR3* focus, D3DXVECTOR3* dir)
{
	_eye = D3DXVECTOR3(0, 0, -_distance);

	if (focus && dir)
	{
		// _eye�� ��ġ�� �ٶ󺸴� ���� * -_distance�� ������
		D3DXMATRIX matR;
		_angleY = getAngle(0, 0, dir->x, dir->z) + D3DX_PI / 2;
		D3DXMatrixRotationY(&matR, _angleY);
		D3DXVec3TransformCoord(&_eye, &_eye, &matR);

		// _lookAt�� y���� ���� �÷� TPS���� �並 ������ְ�
		// _eye�� ��ġ�� focus��ŭ �Ű���
		_lookAt = *focus;
		_lookAt.y += 1.5f;
		_eye += _lookAt;
	}

	// �� ��Ʈ���� ����
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view,
		&_eye,
		&_lookAt,
		&_up);

	// ���� ��Ʈ������ ����̽��� ����
	D3DDEVICE->SetTransform(D3DTS_VIEW, &view);
}

void camera::update(D3DXVECTOR3 * lookat, D3DXVECTOR3 * eye, D3DXVECTOR3* up)
{
	_eye = *eye;

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		_moveStart = _ptMouse;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		_angleX += (_ptMouse.y - _moveStart.y) / 100.0f;
		_angleY += (_ptMouse.x - _moveStart.x) / 100.0f;

		_moveStart = _ptMouse;
	}

	if (_angleX >= D3DX_PI / 2 - D3DX_16F_EPSILON)
		_angleX = D3DX_PI / 2 - D3DX_16F_EPSILON;
	if (_angleX <= -D3DX_PI / 2 + D3DX_16F_EPSILON)
		_angleX = -D3DX_PI / 2 + D3DX_16F_EPSILON;

	if (_angleY > D3DX_PI * 2)
		_angleY -= D3DX_PI * 2;
	if (_angleY < 0)
		_angleY += D3DX_PI * 2;

	D3DXMATRIX temp;
	D3DXMatrixRotationYawPitchRoll(&temp, _angleY, _angleX, 0.0f);
	D3DXVec3TransformCoord(&_eye, &_eye, &temp);

	if (lookat)
	{
		_lookAt = *lookat;
		_eye += _lookAt;
	}

	// �� ��Ʈ���� ����
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view,
		&_eye,
		&_lookAt,
		&_up);

	// ���� ��Ʈ������ ����̽��� ����
	D3DDEVICE->SetTransform(D3DTS_VIEW, &view);
}

void camera::cameraZoom(float zoom)
{
	_distance -= zoom;
}
