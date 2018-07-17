#pragma once

class enemy;
class playerManager;
class player;

class enemyManager
{
private:
	playerManager* _pm;

private:
	vector<enemy*> _vEnemy;		// ���ʹ� �����ϴ� ����

private:
	int _stage;
	int _timer;

private:
	// ��������
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
	void CreateEnemyInit();
	void CreateEnemyUpdate();

	vector<enemy*> GetEnemy() { return _vEnemy; }
	
	// �÷��̾� �Ŵ��� ��ũ����
	void SetPlayerAdressLink(playerManager* player) { _pm = player; }
	// PhysX(��������) ��ũ����
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }
};

