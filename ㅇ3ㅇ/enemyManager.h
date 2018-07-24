#pragma once

class enemy;
class playerManager;
class player;
class itemManager;
class particleSystem;

#define ENEMY_FULL 8

enum EM_GAME_MODE
{
	EM_GAME_STORY,
	EM_GAME_BATTLE
};

class enemyManager
{
private:
	playerManager*			_pm;
	itemManager*			_im;
	vector<particleSystem*>	_vParticle;
	int						_particleAppearCount;

private:
	vector<enemy*> _vEnemy;		// ���ʹ� �����ϴ� ����

	vector<enemy*> _vWall;		// ���� ����ϴ� ���ʹ�

private:
	EM_GAME_MODE _gm;

	int _stage;
	int _timer;
	int _strongMobAppearCount;
	int _middleBossAppearCount;

	bool _killMiddleBoss;
	bool _killGateKeeper;

private:
	// ��������
	PxControllerManager*	_cm;
	PxMaterial*				_material;

public:
	enemyManager();
	~enemyManager();

	void Init(int Mode = 0, int size = 1);
	void Release();
	void Update();
	void Render(int size = 1);
	void RenderParticle(int size = 1);

	void ChangeStage(int num);

	void CreateWall();
	void DestroyWall();

	void CreateFightEnemy();

	void CreateEnemy(D3DXVECTOR3* target);
	D3DXVECTOR3	MakePos(D3DXVECTOR3 areaCenterPos);
	bool WithinArea(D3DXVECTOR3 areaCenterPos, D3DXVECTOR3 playerPos, float radius);

	void CreatKerberos();
	void CreateMiddleBoss();
	void CreateBoss();

	vector<enemy*> GetEnemy() { return _vEnemy; }

	// �߰����� ����
	bool GetMiddleBoss();

	// �߰����� �׿���
	bool GetMiddleBossKill() { return _killMiddleBoss; }
	// �ɸ����ν� �׿���
	bool GetGateKeeperKill() { return _killGateKeeper; }
	
	// �÷��̾� �Ŵ��� ��ũ����
	void SetPlayerAdressLink(playerManager* player) { _pm = player; }
	// ������ �Ŵ��� ��ũ����
	void SetItemAdressLink(itemManager* im) { _im = im; }
	// PhysX(��������) ��ũ����
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }
};

