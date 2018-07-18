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
	void Render(int size);

	void ChangeStage(int num);

	void CreateEnemy(D3DXVECTOR3* target);
	D3DXVECTOR3	MakePos(D3DXVECTOR3 areaCenterPos);
	bool WithinArea(D3DXVECTOR3 areaCenterPos, D3DXVECTOR3 playerPos, float radius);

	void CreateMiddleBoss();

	vector<enemy*> GetEnemy() { return _vEnemy; }
	
	// �÷��̾� �Ŵ��� ��ũ����
	void SetPlayerAdressLink(playerManager* player) { _pm = player; }
	// PhysX(��������) ��ũ����
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }
};

