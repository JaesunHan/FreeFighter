#include "stdafx.h"
#include "skinnedMesh.h"
#include "AllocatedHierachy.h"


skinnedMesh::skinnedMesh()
	: _root(NULL)
	, _aniController(NULL)
	, _ah(NULL)
	, _currentAnimationSet(0)
	, _maxAnimationSet(0)
	, _parentMatrix(NULL)
	, _blendTime(1.0f)
	, _passedBlendTime(0.0f)
{
}


skinnedMesh::~skinnedMesh()
{
}

#ifdef UNICODE
void skinnedMesh::init(const WCHAR* folder, const WCHAR* file)
{
	wstring filePath = folder + wstring(L"\\") + file;

	_ah = new AllocatedHierachy;
	_ah->setTextureFolder(wstring(folder)); 

	if (FAILED(D3DXLoadMeshHierarchyFromX(filePath.c_str(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		D3DDEVICE,
		_ah,
		0,
		&_root,
		&_aniController)))
	{
		return;
	}

	this->setBoneMatrixPtrs(_root);

	_maxAnimationSet = _aniController->GetMaxNumAnimationSets();
}
#else
void skinnedMesh::init(const char* folder, const char* file)
{
	string filePath = folder + string("\\") + file;

	_ah = new AllocatedHierachy;
	_ah->setTextureFolder(string(folder));

	if (FAILED(D3DXLoadMeshHierarchyFromX(filePath.c_str(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		D3DDEVICE,
		_ah,
		0,
		&_root,
		&_aniController)))
	{
		return;
	}

	this->setBoneMatrixPtrs(_root);

	_maxAnimationSet = _aniController->GetMaxNumAnimationSets();
}
#endif

void skinnedMesh::release()
{
	if (_ah && _root)
		_ah->DestroyFrame(_root);

	SAFE_RELEASE(_aniController);
}

void skinnedMesh::update()
{
	_passedBlendTime += TIMEMANAGER->getElapsedTime() * 5.0f;
	if (_passedBlendTime > _blendTime)
	{
		_aniController->SetTrackWeight(0, 1.0f);
		_aniController->SetTrackWeight(1, 0.0f);

		_aniController->SetTrackEnable(1, FALSE);
	}
	else
	{
		float weight = _passedBlendTime / _blendTime;
		_aniController->SetTrackWeight(0, weight);
		_aniController->SetTrackWeight(1, 1.0f - weight);
	}

	_aniController->AdvanceTime(TIMEMANAGER->getElapsedTime(), NULL);

	this->update(_root);
	this->updateSkinnedMesh(_root);
}

void skinnedMesh::update(LPD3DXFRAME frame, LPD3DXFRAME parent)
{
	tagBone* bone = (tagBone*)frame;
	bone->combinedTransformationMatrix = bone->TransformationMatrix;

	// ?? ��� 2�� ������??
	if (bone == _root && _parentMatrix)
		bone->combinedTransformationMatrix *= (*_parentMatrix);

	if (parent)
		bone->combinedTransformationMatrix *= ((tagBone*)parent)->combinedTransformationMatrix;

	if (frame->pFrameSibling)
		this->update(frame->pFrameSibling, parent);

	if (frame->pFrameFirstChild)
		this->update(frame->pFrameFirstChild, frame);
}

void skinnedMesh::updateSkinnedMesh(LPD3DXFRAME frame)
{
	tagBone* bone = (tagBone*)frame;

	if (bone)
	{
		if (bone->pMeshContainer)
		{
			tagBone_Mesh* boneMesh = (tagBone_Mesh*)bone->pMeshContainer;
			if (boneMesh->pSkinInfo)
			{
				DWORD numOfBones = boneMesh->pSkinInfo->GetNumBones();
				for (DWORD i = 0; i < numOfBones; ++i)
					boneMesh->currentBoneMatrices[i] = boneMesh->boneOffsetMatrices[i] * (*boneMesh->boneMatrixPtrs[i]);

				BYTE* src = NULL, *dest = NULL;
				boneMesh->originMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
				boneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

				boneMesh->pSkinInfo->UpdateSkinnedMesh(boneMesh->currentBoneMatrices,
					NULL,
					src,
					dest);

				boneMesh->MeshData.pMesh->UnlockVertexBuffer();
				boneMesh->originMesh->UnlockVertexBuffer();
			}
		}
	}

	if (frame->pFrameSibling)
		updateSkinnedMesh(frame->pFrameSibling);

	if (frame->pFrameFirstChild)
		updateSkinnedMesh(frame->pFrameFirstChild);
}

void skinnedMesh::render()
{
	this->render(_root);
}

void skinnedMesh::render(LPD3DXFRAME frame)
{
	tagBone* bone = (tagBone*)frame;

	if (bone->pMeshContainer)
	{
		tagBone_Mesh* boneMesh = (tagBone_Mesh*)bone->pMeshContainer;
		if (bone->pMeshContainer->MeshData.pMesh)
		{
			//if (_parentMatrix)
			//	D3DDEVICE->SetTransform(D3DTS_WORLD, &(bone->combinedTransformationMatrix * (*_parentMatrix)));
			//else
			//	D3DDEVICE->SetTransform(D3DTS_WORLD, &bone->combinedTransformationMatrix);

			for (int i = 0; i < boneMesh->vMtlTex.size(); ++i)
			{
				D3DDEVICE->SetMaterial(&MATERIALMANAGER->findMaterial(boneMesh->vMtlTex[i].mtlName));
				D3DDEVICE->SetTexture(0, TEXTUREMANAGER->findTexture(boneMesh->vMtlTex[i].textureName));
				bone->pMeshContainer->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (frame->pFrameSibling)
		this->render(frame->pFrameSibling);

	if (frame->pFrameFirstChild)
		this->render(frame->pFrameFirstChild);
}

void skinnedMesh::setBoneMatrixPtrs(LPD3DXFRAME frame)
{
	if (frame && frame->pMeshContainer)
	{
		tagBone_Mesh* boneMesh = (tagBone_Mesh*)frame->pMeshContainer;
		if (boneMesh->pSkinInfo)
		{
			DWORD numOfBones = boneMesh->pSkinInfo->GetNumBones();
			for (int i = 0; i < numOfBones; ++i)
			{
				tagBone* bone = (tagBone*)D3DXFrameFind(_root, boneMesh->pSkinInfo->GetBoneName(i));

				boneMesh->boneMatrixPtrs[i] = &(bone->combinedTransformationMatrix);
			}
		}
	}

	if (frame->pFrameFirstChild)
		this->setBoneMatrixPtrs(frame->pFrameFirstChild);

	if (frame->pFrameSibling)
		this->setBoneMatrixPtrs(frame->pFrameSibling);
}

void skinnedMesh::setAnimationSet(UINT index)
{
	LPD3DXANIMATIONSET temp;
	_aniController->GetAnimationSet(index, &temp);
	_aniController->SetTrackAnimationSet(0, temp);
	_aniController->SetTrackEnable(0, TRUE);

	//_aniController->ResetTime();

	SAFE_RELEASE(temp);
}

void skinnedMesh::setAnimationIndexBlend(UINT index)
{
	LPD3DXANIMATIONSET prev = NULL;
	LPD3DXANIMATIONSET next = NULL;

	// 0�� Ʈ���� 1��Ʈ������ �Ű���
	D3DXTRACK_DESC temp;
	_aniController->GetTrackDesc(0, &temp);
	_aniController->GetTrackAnimationSet(0, &prev);

	_aniController->SetTrackAnimationSet(1, prev);
	_aniController->SetTrackDesc(1, &temp);

	_aniController->GetAnimationSet(index, &next);
	_aniController->SetTrackAnimationSet(0, next);

	_aniController->SetTrackWeight(0, 0.0f);
	_aniController->SetTrackWeight(1, 1.0f);

	_aniController->SetTrackEnable(0, TRUE);
	_aniController->SetTrackEnable(1, TRUE);

	_passedBlendTime = 0.0f;

	//_aniController->ResetTime();

	SAFE_RELEASE(prev);
	SAFE_RELEASE(next);
}
