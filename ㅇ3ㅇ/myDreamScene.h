#pragma once
#include "sceneInterface.h"

class enemyManager;
class playerManager;
class camera;
class testCube;

class myDreamScene : public iScene
{
private:
	enemyManager*	_em;
	camera*			_camera;
	testCube*		_cube;

	//��������
	PxScene*				_physXScene;
	PxMaterial*				_material;
	PxControllerManager*	_cm;

private:
	D3DXVECTOR3		_testTarget;
	int				_testStage;

public:
	myDreamScene();
	~myDreamScene();

	// _scene��(��) ���� ��ӵ�
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
};

