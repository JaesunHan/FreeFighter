#pragma once
class camera;
class cameraWalk
{
private:


	camera * _camera;

	D3DXVECTOR3		_camEye;
	D3DXVECTOR3		_camLookAt;
	D3DXVECTOR3		_camUpDir;

	vector<TRANSLATION*>	_vPosTrack;
	//vector<ROTATION*>		_vRotShakeTrack;

private:
	DWORD	_firstFrame;
	DWORD	_lastFrame;
	DWORD	_frameSpeed;
	DWORD	_ticksPerFrame;

	DWORD	_currentFrame;

	DWORD	_startKeyFrame;
public:
	cameraWalk();
	~cameraWalk();

	void init();
	void update();

	void shakeCamera(int keyFrame);

	//						start 부터      end 까지		timeSec 동안 이동
	void LinearInterpolationEye(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec);			//카메라의 vEye 값 변경(구면선형보간)
	void LinearInterpolationLookAt(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec);		//카메라의 바라보는 곳 변경(구면선형보간)
	void LinearInterpolationUpDir(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec);			//카메라의 윗방향 변경(구면선형보간)
	void InitShakeTrack();//카메라 흔들리는 효과 track 저장


	camera* getCamera() { return _camera; }
	int getKeyFrame();
	void setStartKeyFrame() { _startKeyFrame = getKeyFrame(); }
	void setCamLookAt(D3DXVECTOR3 v) { _camLookAt = v; }
};

