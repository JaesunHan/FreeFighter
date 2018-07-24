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

	D3DXVECTOR3				_portal;

private:
	vector<enemy*> _vEnemy;		// 에너미 관리하는 벡터

	vector<enemy*> _vWall;		// 벽을 담당하는 에너미

private:
	EM_GAME_MODE _gm;

	int _stage;
	int _timer[2];
	int _strongMobAppearCount;
	int _middleBossAppearCount;

	bool _oneAppear;

	bool _killMiddleBoss;
	bool _killGateKeeper;

private:
	// 물리엔진
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

	void CreateEnemy(playerManager* pm);
	D3DXVECTOR3	MakePos(D3DXVECTOR3 areaCenterPos);
	bool WithinArea(D3DXVECTOR3 areaCenterPos, D3DXVECTOR3 playerPos, float radius);

	void CreatKerberos();
	void CreateMiddleBoss();
	void CreateBoss();

	vector<enemy*> GetEnemy() { return _vEnemy; }

	// 중간보스 등장
	bool GetMiddleBoss();
	// 중간보스 죽였니
	bool GetMiddleBossKill() { return _killMiddleBoss; }
	// 케르베로스 죽였니
	bool GetGateKeeperKill() { return _killGateKeeper; }

	// 보스방 입장
	bool GetInPortal();
	
	// 플레이어 매니저 링크연결
	void SetPlayerAdressLink(playerManager* player) { _pm = player; }
	// 아이템 매니저 링크연결
	void SetItemAdressLink(itemManager* im) { _im = im; }
	// PhysX(물리엔진) 링크연결
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }
};

