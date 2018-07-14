#pragma once
class cube;
class background
{
private:
	
	LPD3DXMESH						_meshMap;			//�� �޽�
	vector<tagObjectMtlData>		_vecMapMtlData;

	LPD3DXMESH						_meshSurface;			//surface �޽�
	vector<tagObjectMtlData>		_vecSurfaceMtlData;

	D3DXMATRIX						_mapMatWorld;			//���� ��ġ�� ��ġ

	cube*							_sky;

	PxController*					_pController;
	PxControllerManager**			_pCM;
	PxMaterial*						_pMaterial;

public:
	background();
	~background();
	HRESULT init();					//�⺻ �ϴ� �� ������� ����
#ifdef UNICODE
	//				�ϴ��ؽ��İ��ִ� ������ �����̸�,		�� ���� �ִ� ������ �����̸�
	HRESULT init(WCHAR*	skyFolder, WCHAR* skyFileName, WCHAR* mapFolder, WCHAR* mapFileName);
#else 
	HRESULT init(char*	skyFolder, char* skyFileName, char* mapFolder, char* mapFileName);
#endif // UNICODE

	
	void update();
	void render();
	void release();
	void setLigh();
	void setSky();

	void createController(PxControllerManager** cm, PxMaterial* m, D3DXVECTOR3 sizeVector);

	inline PxController* getController() { return _pController; }

};

