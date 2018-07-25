#pragma once
class camera
{
private:
	D3DXVECTOR3		_eye;
	D3DXVECTOR3		_up;
	D3DXVECTOR3		_lookAt;

	POINT			_moveStart;

	float			_angleX;
	float			_angleY;
	float			_distance;

public:
	camera();
	~camera();

	void init();
	void release();
	void update(D3DXVECTOR3* focus = NULL);
	void update(D3DXVECTOR3* focus, float distance);
	void update(D3DXVECTOR3* focus, D3DXVECTOR3* dir, float distance = 5.0f);
	void update(D3DXVECTOR3* lookat, D3DXVECTOR3* eye, D3DXVECTOR3* up);

	void cameraZoom(float zoom);

	inline D3DXVECTOR3 getDirection() { return _lookAt - _eye; }
	inline void setAngle(D3DXVECTOR3 angle) { _angleX = angle.y, _angleY = angle.x; }
	inline void setDistance(float distance) { _distance = distance; }
};

