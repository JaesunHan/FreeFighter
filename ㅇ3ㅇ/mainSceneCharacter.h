#pragma once

class skinnedMesh;

enum MAINCHARACTER_ANI
{
	ANI_NONE = -1,
	ANI_IDLE,
	ANI_MOVE,
	ANI_END
};

class mainSceneCharacter
{
private:
	skinnedMesh*		_skinnedMesh;
	D3DXVECTOR3			_worldPos;
	D3DXVECTOR3			_worldDir;
	D3DXVECTOR3			_worldSca;

	D3DXMATRIX			_worldTM;

	PxController*		_controller;
	PxVec3				_velocity;

	int					_aniIndex[ANI_END];
	MAINCHARACTER_ANI	_currentAni;

public:
	mainSceneCharacter();
	~mainSceneCharacter();

	HRESULT init(wstring keyPath, wstring keyName);
	void release();
	void update();
	void move();

	void CreateWorldMatrix(float correctionAngle = -D3DX_PI / 2);

	void render(float elapsedTime);

	void createContoller(PxControllerManager** cm, PxMaterial* m);

	void changeAnimation(MAINCHARACTER_ANI ani);
	bool isCrush();

	void setPosition(D3DXVECTOR3 pos, D3DXVECTOR3 dir);
	inline D3DXVECTOR3 getWorldPos() { return _worldPos; }
};

