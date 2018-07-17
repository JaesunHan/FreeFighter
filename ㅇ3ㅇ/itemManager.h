#pragma once

class item;
class playerManager;

class itemManager
{
private:

	vector<item*>		_vItem;					//�������� ������ ��� �� ����
												//vector<item*>::iterator _viItem;
	playerManager*		_pm;
private:
	PxControllerManager * _cm;
	PxMaterial*				_material;

public:
	itemManager();
	~itemManager();

	void Init();
	void Update();
	void Render();
	void CreateItem();

	//������ ���� �׳��� ���ؼ�
	void setPlayerAdressLink(playerManager* player) { _pm = player; }

	//��������
	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }

};

