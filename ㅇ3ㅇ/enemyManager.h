#pragma once

class enemy;
class playerManager;
class player;

class enemyManager
{
private:
	playerManager* _pm;

private:
	vector<enemy*> _vEnemy;		// 에너미 관리하는 벡터

private:
	int _stage;
	int _timer;

private:
	// 물리엔진
	PxControllerManager*	_cm;
	PxMaterial*				_material;

public:
	enemyManager();
	~enemyManager();

	void Init();
	void Release();
	void Update();
	void Render(int size);

	void ChangeStage(int num);

	void CreateEnemy(D3DXVECTOR3* target);
	D3DXVECTOR3	MakePos(D3DXVECTOR3 areaCenterPos);
	bool WithinArea(D3DXVECTOR3 areaCenterPos, D3DXVECTOR3 playerPos, float radius);

	void CreateMiddleBoss();

	vector<enemy*> GetEnemy() { return _vEnemy; }
	
	// 플레이어 매니저 링크연결
	void SetPlayerAdressLink(playerManager* player) { _pm = player; }
	// PhysX(물리엔진) 링크연결
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }
};

