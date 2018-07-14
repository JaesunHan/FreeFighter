#pragma once

class enemy;
class playerManager;

class enemyManager
{
private:
	playerManager* _pm;

private:
	vector<enemy*> _vEnemy;		//에너미 관리하는 벡터

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
	void Render();

	void ChangeStage(int num);
	void CreateEnemy();
	void Attack();

	vector<enemy*> GetEnemy() { return _vEnemy; }
	
	//플레이어 매니저 링크연결
	void SetPlayerAdressLink(playerManager* player) { _pm = player; }
	//피직스(물리엔진) 링크연결
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }
};

