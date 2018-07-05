#include "stdafx.h"
#include "AllocatedHierachy.h"


AllocatedHierachy::AllocatedHierachy()
{
}


AllocatedHierachy::~AllocatedHierachy()
{
}

STDMETHODIMP AllocatedHierachy::CreateFrame(LPCSTR boneName, LPD3DXFRAME* newFrame)
{
	tagBone* bone = new tagBone;
	ZeroMemory(bone, sizeof(tagBone));

	if (boneName)
	{
		UINT length = strlen(boneName) + 1;
		bone->Name = new char[length * sizeof(TCHAR)];
		strcpy_s(bone->Name, length * sizeof(TCHAR), boneName);
	}

	D3DXMatrixIdentity(&bone->combinedTransformationMatrix);
	D3DXMatrixIdentity(&bone->TransformationMatrix);

	*newFrame = bone;

	return S_OK;
}

STDMETHODIMP AllocatedHierachy::CreateMeshContainer(
	LPCSTR containerName,
	CONST D3DXMESHDATA* meshData,
	CONST D3DXMATERIAL* materials,
	CONST D3DXEFFECTINSTANCE* effectInstances,
	DWORD numMaterials,
	CONST DWORD* adjacency,
	LPD3DXSKININFO skinInfo,
	LPD3DXMESHCONTAINER* newMeshContainer)
{
	tagBone_Mesh* boneMesh = new tagBone_Mesh;
	ZeroMemory(boneMesh, sizeof(tagBone_Mesh));

	for (DWORD i = 0; i < numMaterials; ++i)
	{
		tagObjectMtlData tempData;
#ifdef UNICODE
		WCHAR temp[1024];
		MultiByteToWideChar(CP_ACP, 0, materials[i].pTextureFilename, -1, temp, sizeof(temp));
		tempData.mtlName = temp;
		tempData.textureName = temp;
		MATERIALMANAGER->addMaterial(temp, materials[i].MatD3D);
		TEXTUREMANAGER->addTexture(temp, (_textureFolder + wstring(L"\\") + wstring(temp)).c_str());
#else
		tempData.mtlName = materials[i].pTextureFilename;
		tempData.textureName = materials[i].pTextureFilename;
		MATERIALMANAGER->addMaterial(materials[i].pTextureFilename, materials[i].MatD3D);
		TEXTUREMANAGER->addTexture(materials[i].pTextureFilename, (_textureFolder + string("\\") + string(materials[i].pTextureFilename)).c_str());
#endif

		boneMesh->vMtlTex.push_back(tempData);
	}

	skinInfo->AddRef();
	boneMesh->pSkinInfo = skinInfo;

	meshData->pMesh->AddRef();
	boneMesh->MeshData.pMesh = meshData->pMesh;
	meshData->pMesh->CloneMeshFVF(
		meshData->pMesh->GetOptions(),
		meshData->pMesh->GetFVF(),
		D3DDEVICE,
		&boneMesh->originMesh);

	DWORD numOfBones = skinInfo->GetNumBones();

	boneMesh->boneMatrixPtrs = new D3DXMATRIX*[numOfBones];
	boneMesh->boneOffsetMatrices = new D3DXMATRIX[numOfBones];
	boneMesh->currentBoneMatrices = new D3DXMATRIX[numOfBones];

	for (DWORD i = 0; i < numOfBones; ++i)
	{
		boneMesh->boneOffsetMatrices[i] =
			*(skinInfo->GetBoneOffsetMatrix(i));
	}

	*newMeshContainer = boneMesh;

	return S_OK;
}

STDMETHODIMP AllocatedHierachy::DestroyFrame(LPD3DXFRAME frameToFree)
{
	tagBone* bone = (tagBone*)frameToFree;

	SAFE_DELETE_ARRAY(bone->Name);
	SAFE_DELETE(bone);

	return S_OK;
}

STDMETHODIMP AllocatedHierachy::DestroyMeshContainer(LPD3DXMESHCONTAINER meshContainerToFree)
{
	tagBone_Mesh* pBoneMesh = (tagBone_Mesh*)meshContainerToFree;

	SAFE_RELEASE(pBoneMesh->pSkinInfo);
	SAFE_RELEASE(pBoneMesh->MeshData.pMesh);
	SAFE_RELEASE(pBoneMesh->originMesh);

	SAFE_DELETE_ARRAY(pBoneMesh->boneMatrixPtrs);
	SAFE_DELETE_ARRAY(pBoneMesh->boneOffsetMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->currentBoneMatrices);

	SAFE_DELETE(pBoneMesh);

	return S_OK;
}
