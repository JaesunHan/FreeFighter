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

	//						start ����      end ����		timeSec ���� �̵�
	void LinearInterpolationEye(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec);			//ī�޶��� vEye �� ����(���鼱������)
	void LinearInterpolationLookAt(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec);		//ī�޶��� �ٶ󺸴� �� ����(���鼱������)
	void LinearInterpolationUpDir(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, float timeSec);			//ī�޶��� ������ ����(���鼱������)
	void InitShakeTrack();//ī�޶� ��鸮�� ȿ�� track ����


	camera* getCamera() { return _camera; }
	int getKeyFrame();
	void setStartKeyFrame() { _startKeyFrame = getKeyFrame(); }
	void setCamLookAt(D3DXVECTOR3 v) { _camLookAt = v; }
};

