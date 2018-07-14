#pragma once
class cube;
class background
{
private:
	
	LPD3DXMESH						_meshMap;			//맵 메시
	vector<tagObjectMtlData>		_vecMapMtlData;

	LPD3DXMESH						_meshSurface;			//surface 메시
	vector<tagObjectMtlData>		_vecSurfaceMtlData;

	D3DXMATRIX						_mapMatWorld;			//맵을 배치할 위치

	cube*							_sky;

	PxController*					_pController;
	PxControllerManager**			_pCM;
	PxMaterial*						_pMaterial;

public:
	background();
	~background();
	HRESULT init();					//기본 하늘 및 배경으로 세팅
#ifdef UNICODE
	//				하늘텍스쳐가있는 폴더와 파일이름,		맵 모델이 있는 폴더와 파일이름
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

