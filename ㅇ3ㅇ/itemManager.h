#pragma once

class item;

class itemManager
{
private:

	vector<item*>		_vItem;					//�������� ������ ��� �� ����
	vector<item*>::iterator _viItem;

private:
	PxControllerManager * _cm;
	PxMaterial*				_material;

public:
	itemManager();
	~itemManager();

	void Init();
	void Update();
	void Render();


	inline void setPhysX(PxControllerManager* cm, PxMaterial* m) { _cm = cm; _material = m; }

};

