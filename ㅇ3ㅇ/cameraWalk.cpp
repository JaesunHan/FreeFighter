#include "stdafx.h"
#include "cameraWalk.h"
#include "camera.h"


cameraWalk::cameraWalk()
{

	_firstFrame = 0;
	_lastFrame = 200;
	_frameSpeed = 30;
	_ticksPerFrame= 160;

	_currentFrame= 0;
}


cameraWalk::~cameraWalk()
{
}

void cameraWalk::init()
{
	_startTickCount = GetTickCount();
	_camera = new camera;
	_camEye = D3DXVECTOR3(0, 5.5, -15);
	_camLookAt = D3DXVECTOR3(0, 5.5, 0);
	_camUpDir = D3DXVECTOR3(0, 1, 0);
	_camera->setDistance(15);
	InitShakeTrack(); 

}

void cameraWalk::update()
{
	//shakeCamera(getKeyFrame());
	//if (_camera)
	//{
	//	_camera->update(&_camLookAt);
	//	_camera->setAngle(_camEye);
	//}
}

void cameraWalk::release()
{
	if (_camera)
		_camera->release();
}

void cameraWalk::shakeCamera(int keyFrame)
{
	// 현재 프레임 번호 찾기
	int nextIndex = 0;
	for (int i = 0; i < _vPosShake.size(); ++i)
	{
		if (keyFrame < _vPosShake[i]->tick)
		{
			nextIndex = i;
			break;
		}
	}
	if (nextIndex == 0)
		nextIndex = 1;
	int prevIndex = nextIndex - 1;

	float t = (keyFrame - _vPosShake[prevIndex]->tick) / (float)(_vPosShake[nextIndex]->tick - _vPosShake[prevIndex]->tick);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v,
		&_vPosShake[prevIndex]->pos,
		&_vPosShake[nextIndex]->pos,
		t);
	_camEye = v;

	if (_camera)
	{
		_camera->setAngle(_camEye);
		_camera->update(&_camLookAt, &_camEye, &_camUpDir);
		
	}
}

void cameraWalk::LinearInterpolationEye(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec)
{
	D3DXVec3Lerp(&_camEye, &vStart, &vEnd, timeSec);
}

void cameraWalk::LinearInterpolationLookAt(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec)
{
	D3DXVec3Lerp(&_camLookAt, &vStart, &vEnd, timeSec);
}

void cameraWalk::LinearInterpolationUpDir(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec)
{
	D3DXVec3Lerp(&_camUpDir, &vStart, &vEnd, timeSec);
}

void cameraWalk::InitShakeTrack()
{
	if (!_vPosShake.empty())
		_vPosShake.clear();
	int time = 10;
	//준보스가 위에서 떨어질 때 카메라가 정면을 바라보고있는 트랙
	for (int i = 0; i < time; ++i)
	{
		TRANSLATION* track = new TRANSLATION;
		track->tick = _ticksPerFrame * (i + 1);
		
		track->pos = D3DXVECTOR3(0.0f, 5.5f, 1.0f);
		_vPosShake.push_back(track);
		
	}

	D3DXVECTOR3 center = D3DXVECTOR3(0, 5.5, 1.0f);
	//카메라가 흔들리는 트랙
	for (int i = 0; i < _lastFrame; ++i)
	{
		TRANSLATION* track = new TRANSLATION;
		//TRANSLATION* track2 = new TRANSLATION;
		track->tick = (_ticksPerFrame * time) + 40 * (i + 1);
		//track2->tick = track->tick + 5;

		float angle = (RND->getFromIntTo(-5, 5)) * DEG2RAD;
		D3DXMATRIX matR;
		D3DXMatrixRotationY(&matR, angle);
		D3DXVec3TransformCoord(&track->pos, &center, &matR);
		_vPosShake.push_back(track);
		//if (i % 2 == 0) 
		//{
		//	track->pos = D3DXVECTOR3(0.1f, 5.5f, 0.0f);
		//	//track2->pos = track->pos;
		//	_vPosShake.push_back(track);
		//	//_vPosShake.push_back(track2);
		//	//_vPosShake.push_back(track);
		//}
		//else
		//{
		//	track->pos = D3DXVECTOR3(-0.1f, 5.5f, 0.0f);
		//	//track2->pos = track->pos;
		//	_vPosShake.push_back(track);
		//	//_vPosShake.push_back(track2);
		//	//_vPosShake.push_back(track);
		//}
		
	}

}

int cameraWalk::getKeyFrame()
{
	int first = _firstFrame * _ticksPerFrame;
	int last = _lastFrame * _ticksPerFrame;

	return ((GetTickCount() - _startTickCount) * _ticksPerFrame / _frameSpeed) % (last - first) + first;
}

