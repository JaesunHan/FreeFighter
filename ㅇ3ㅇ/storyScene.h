#pragma once
#include "sceneInterface.h"

class storyScene : public _scene
{
private:
	LPD3DXMESH						_meshMap;			//¸Ê ¸Þ½Ã
	vector<tagObjectMtlData>		_vecMapMtlData;		

	LPD3DXMESH						_meshSurface;			//surface ¸Þ½Ã
	vector<tagObjectMtlData>		_vecSurfaceMtlData;

	D3DXMATRIX						_mapMatWorld;


public:
	storyScene();
	~storyScene();

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;
};

