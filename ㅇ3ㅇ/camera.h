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
	void update(D3DXVECTOR3* focus, D3DXVECTOR3* dir);

	void cameraZoom(float zoom);

	inline D3DXVECTOR3 getDirection() { return _lookAt - _eye; }
	inline void setAngle(D3DXVECTOR3 angle) { _angleX = angle.y, _angleY = angle.x; }
};

