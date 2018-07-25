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
	// 화면 크기 받아오기
	RECT rc;
	GetClientRect(_hWnd, &rc);

	// 프로젝션 매트릭스 만듦
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection,
		D3DX_PI / 4.0f,					// 시야 각
		rc.right / (float)rc.bottom,	// 화면 비율(가로 / 세로)
		0.1f,							// 화면에 나올 가까운 z값
		1000.0f);						// 화면에 나올 먼 z값

	// 만든 매트릭스를 디바이스에 적용
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

	// 뷰 매트릭스 세팅
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view,
		&_eye,
		&_lookAt,
		&_up);

	// 만든 매트릭스를 디바이스에 적용
	D3DDEVICE->SetTransform(D3DTS_VIEW, &view);
}

// 포커스가 바라보는 방향의 뒤쪽에서 포커스를 따라다니는 카메라
void camera::update(D3DXVECTOR3* focus, D3DXVECTOR3* dir, float distance)
{
	_eye = D3DXVECTOR3(0, 0, -distance);

	if (focus && dir)
	{
		// _eye의 위치를 바라보는 방향 * -_distance로 맞춰줌
		D3DXMATRIX matR;
		_angleY = getAngle(0, 0, dir->x, dir->z) + D3DX_PI / 2;
		D3DXMatrixRotationY(&matR, _angleY);
		D3DXVec3TransformCoord(&_eye, &_eye, &matR);

		// _lookAt의 y값을 조금 올려 TPS같은 뷰를 만들어주고
		// _eye의 위치를 focus만큼 옮겨줌
		_lookAt = *focus;
		_lookAt.y += 1.5f + (distance - 5.0f) * 0.1f;
		_eye += _lookAt;
	}

	// 뷰 매트릭스 세팅
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view,
		&_eye,
		&_lookAt,
		&_up);

	// 만든 매트릭스를 디바이스에 적용
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

	// 뷰 매트릭스 세팅
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view,
		&_eye,
		&_lookAt,
		&_up);

	// 만든 매트릭스를 디바이스에 적용
	D3DDEVICE->SetTransform(D3DTS_VIEW, &view);
}

void camera::cameraZoom(float zoom)
{
	_distance -= zoom;
}
