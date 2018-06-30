#pragma once

class enemy;

class enemyManager
{
private:
	vector<enemy*> _vEnemy;

private:
	int _stage;

public:
	enemyManager();
	~enemyManager();

	void Init();
	void Update();
	void Render();

	void ChangeStage(int num);
};

