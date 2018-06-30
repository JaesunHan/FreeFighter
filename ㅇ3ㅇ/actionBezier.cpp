#include "stdafx.h"
#include "actionBezier.h"
#include "objectNode.h"


actionBezier::actionBezier()
	: _totalTime(0.0f)
	, _currentTime(0.0f)
	, _startTime(0.0f)
	, _from(0, 0, 0)
	, _to(0, 0, 0)
{
}


actionBezier::~actionBezier()
{
}

void actionBezier::start()
{
	if (_owner)
	{
		_owner->positionWorld(_from);
		_currentTime = 0.0f;
		_startTime = TIMEMANAGER->getWorldTime();
	}
}

void actionBezier::update()
{
	_currentTime = TIMEMANAGER->getWorldTime() - _startTime;
	if (_currentTime > _totalTime)
	{
		_owner->positionWorld(_to);
		if (_delegate)
			_delegate->onActionFinish(this);
	}
	else
	{
		float t = _currentTime / _totalTime;
		D3DXVECTOR3 p = (1.0f - t) * (1.0f - t) * _from + 2 * (1.0f - t) * t * _via + t * t * _to;
		t += TIMEMANAGER->getElapsedTime();
		D3DXVECTOR3 next = (1.0f - t) * (1.0f - t) * _from + 2 * (1.0f - t) * t * _via + t * t * _to;
		_owner->positionWorld(p);
		_owner->rotateWorld(0.0f, getAngle(p.x, p.z, next.x, next.z) - 90 * DEG2RAD, 0.0f);
	}
}
