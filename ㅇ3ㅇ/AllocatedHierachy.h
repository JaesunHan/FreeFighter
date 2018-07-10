#pragma once

#include <vector>
using namespace std;

struct tagBone : public D3DXFRAME
{
	D3DXMATRIX	combinedTransformationMatrix;	//최종적으로 쓰일 월드TM
};

struct tagBone_Mesh : public D3DXMESHCONTAINER
{
	LPD3DXMESH		originMesh;			
	D3DXMATRIX**	boneMatrixPtrs;		//뼈대 TM
	D3DXMATRIX*		boneOffsetMatrices;	// ? 
	D3DXMATRIX*		currentBoneMatrices;//현재 뼈대 TM

	vector<tagObjectMtlData>	vMtlTex;
	/*
	tagBone_Mesh()
		: originMesh(NULL)
		, boneMatrixPtrs(NULL)
		, boneOffsetMatrices(NULL)
		, currentBoneMatrices(NULL)
	{
		pMaterials = NULL;
		pEffects = NULL;
		NumMaterials = 0;
		pAdjacency = NULL;
		pSkinInfo = NULL;
		pNextMeshContainer = NULL;
		MeshData.pMesh = NULL;
	}

	~tagBone_Mesh()
	{
		if (originMesh)
		{
			originMesh->Release();
			originMesh = NULL;
		}

		if (boneMatrixPtrs)
		{
		}

		if (pSkinInfo)
			pSkinInfo->Release();

		if (MeshData.pMesh)
			MeshData.pMesh->Release();

		SAFE_DELETE_ARRAY(boneOffsetMatrices);
		SAFE_DELETE_ARRAY(currentBoneMatrices);
	}*/
};

class AllocatedHierachy : public ID3DXAllocateHierarchy
{
#ifdef UNICODE
protected:
	wstring	_textureFolder;

public:
	inline void setTextureFolder(wstring f) { _textureFolder = f; }
	inline wstring getTextureFolder() { return _textureFolder; }
#else
protected:
	string	_textureFolder;

public:
	inline void setTextureFolder(string f) { _textureFolder = f; }
	inline string getTextureFolder() { return _textureFolder; }
#endif

public:
	AllocatedHierachy();
	~AllocatedHierachy();

	STDMETHOD(CreateFrame)(THIS_ LPCSTR boneName,
		LPD3DXFRAME* newFrame) override;

	STDMETHODIMP CreateMeshContainer(
		LPCSTR containerName,
		CONST D3DXMESHDATA* meshData,
		CONST D3DXMATERIAL* materials,
		CONST D3DXEFFECTINSTANCE* effectInstances,
		DWORD numMaterials,
		CONST DWORD* adjacency,
		LPD3DXSKININFO skinInfo,
		LPD3DXMESHCONTAINER* newMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME frameToFree) override;

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;
};

