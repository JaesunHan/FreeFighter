#pragma once
#include "action.h"

class actionBezier : public action
{
protected:
	float		_startTime;
	float		_currentTime;

	float		_totalTime;

	D3DXVECTOR3	_from;
	D3DXVECTOR3	_to;
	D3DXVECTOR3	_via;

public:
	actionBezier();
	virtual ~actionBezier();

	virtual void start() override;
	virtual void update() override;

	inline void setTotalTime(float total) { _totalTime = total; }
	inline float getTotalTime() { return _totalTime; }

	inline void setFrom(D3DXVECTOR3 from) { _from = from; }
	inline D3DXVECTOR3 getFrom() { return _from; }

	inline void setTo(D3DXVECTOR3 to) { _to = to; }
	inline D3DXVECTOR3 getTo() { return _to; }

	inline void setVia(D3DXVECTOR3 via) { _via = via; }
	inline D3DXVECTOR3 getVia() { return _via; }
};

