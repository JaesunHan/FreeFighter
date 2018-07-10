#pragma once

class enemy;
class testCube;

class enemyManager
{
private:
	testCube* _tc;

private:
	vector<enemy*> _vEnemy;

private:
	int _stage;
	int _timer;
	D3DXVECTOR3 _testTarget;

	// 물리엔진
private:
	PxControllerManager*	_cm;
	PxMaterial*				_material;

public:
	enemyManager();
	~enemyManager();

	void Init();
	void Update();
	void Render();

	void ChangeStage(int num);
	void CreateEnemy();

	vector<enemy*> GetEnemy() { return _vEnemy; }
	
	void SetTestCubeAdressLink(testCube* tc) { _tc = tc; }

	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }
};

