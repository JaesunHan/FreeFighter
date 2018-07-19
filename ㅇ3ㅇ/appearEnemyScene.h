#pragma once

#include "sceneInterface.h"

#include "gameMode.h"
#include "playerKeySet.h"

////�������� �غ��� ����
//enum EnemyKind
//{
//	EK_NONE,
//	EK_middle_boss,			//�غ���
//	EK_final_bose,			//���� ����
//	EK_END
//};

class playerManager;
class enemyManager;
class gameObject;
class background;
//class camera;
class cameraWalk;
class appearEnemyScene : public _scene
{
private:
	D3DVIEWPORT9		_originViewPort;
	//Kinds				_enemyMode;				//�غ����� ��Ÿ������ ������ ��Ÿ������


	//���丮������ �޾ƿ� ������
	//D3DVIEWPORT9			_originViewport;

	//playerManager*			_pm;		//��� �Ⱦ�����...
	enemyManager*			_em;

	// ���� ��� ����
	//GAME_MODE						_gameMode;
	//PLAYER_MODE						_playerMode;
	//vector<PLAYABLE_CHARACTER>		_vPlayerSelect;

	//// ����������
	//PxScene*						_physXScene;
	//PxMaterial*						_material;
	//PxControllerManager*			_cm;

	// ��׶����
	D3DXMATRIX						_mapMatWorld;
	//LPD3DXMESH						_testGround;
	background*						_pBG;


	////���ʹ� ���� ī�޶�
	//camera*							_camera;
	cameraWalk*						_pCW;

	int								_cnt;			//����� Count

public:
	appearEnemyScene();
	~appearEnemyScene();

	// _scene��(��) ���� ��ӵ�
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

public:
	//inline void setEnemyKinds(Kinds k)
	//{
	//	_enemyMode = k;
	//}

	//
	inline void setEnemyManager(enemyManager* em)
	{
		_em = em;
	}
	
	inline void setMapMatWorld(D3DXMATRIX mat)
	{
		_mapMatWorld = mat;
	}

	inline void setBackground(background* bg)
	{
		_pBG = bg;
	}
	void setCamWalkStartKeyFrame();

};

