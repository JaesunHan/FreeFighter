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
		1.0f,							// ȭ�鿡 ���� ����� z��
		10000.0f);						// ȭ�鿡 ���� �� z��

	// ���� ��Ʈ������ ����̽��� ����
	D3DDEVICE->SetTransform(D3DTS_PROJECTION, &projection);
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

void camera::cameraZoom(float zoom)
{
	_distance -= zoom;
}
