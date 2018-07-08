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
};

