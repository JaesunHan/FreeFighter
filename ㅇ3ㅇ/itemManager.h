#pragma once

class item;

class itemManager
{
private:

	vector<item*>		_vItem;					//아이템의 정보를 담아 줄 벡터
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

