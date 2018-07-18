#include "stdafx.h"
#include "cameraWalk.h"
#include "camera.h"


cameraWalk::cameraWalk()
{

	_firstFrame = 4;
	_lastFrame = 20;
	_frameSpeed = 30;
	_ticksPerFrame= 160;

	_currentFrame= 0;
}


cameraWalk::~cameraWalk()
{
}

void cameraWalk::init()
{
	_camera = new camera;
	_camEye = D3DXVECTOR3(0, 0, -5);
	_camLookAt = D3DXVECTOR3(0, 0, 0);
	_camUpDir = D3DXVECTOR3(0, 1, 0);

	InitShakeTrack();
}

void cameraWalk::update()
{
	shakeCamera(getKeyFrame());
	if (_camera)
	{
		_camera->update(&_camLookAt);
		_camera->setAngle(_camEye);
	}
}

void cameraWalk::shakeCamera(int keyFrame)
{
	// 현재 프레임 번호 찾기
	int nextIndex = 0;
	for (int i = 0; i < _vPosTrack.size(); ++i)
	{
		if (keyFrame < _vPosTrack[i]->tick)
		{
			nextIndex = i;
			break;
		}
	}
	if (nextIndex == 0)
		nextIndex = 1;
	int prevIndex = nextIndex - 1;

	float t = (keyFrame - _vPosTrack[prevIndex]->tick) / (float)(_vPosTrack[nextIndex]->tick - _vPosTrack[prevIndex]->tick);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v,
		&_vPosTrack[prevIndex]->pos,
		&_vPosTrack[nextIndex]->pos,
		t);
	_camEye = v;
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
	for (int i = 0; i < 20; ++i)
	{
		TRANSLATION* track = new TRANSLATION;
		track->tick = 160*(i+1);
		//if(i%2 == 0)
		//	track->axis = D3DXVECTOR3(0.4f, 0.06f, 0.0f);
		//else
		//	track->axis = D3DXVECTOR3(0.4f*(-1), 0.06f*(-1), 0.0f);
		if (i % 2 == 0) 
		{
			track->pos = D3DXVECTOR3(0.1f, 0.00f, 0.0f);
			_vPosTrack.push_back(track);
			if (i != 0)
			{
				_vPosTrack.push_back(track);
			}

		}
		else
		{
			track->pos = D3DXVECTOR3(-0.1f, 0.00f, 0.0f);
			_vPosTrack.push_back(track);
			_vPosTrack.push_back(track);
		}
		
	}

}

int cameraWalk::getKeyFrame()
{
	int first = _firstFrame * _ticksPerFrame;
	int last = _lastFrame * _ticksPerFrame;

	return (GetTickCount() * _ticksPerFrame / _frameSpeed) % (last - first) + first;
}

