#include "stdafx.h"
#include "skinnedMesh.h"
#include "AllocatedHierachy.h"


skinnedMesh::skinnedMesh()
	: _root(NULL)
	, _aniController(NULL)
	, _currentAnimationSet(0)
	, _maxAnimationSet(0)
	, _parentMatrix(NULL)
	, _blendTime(1.0f)
	, _passedBlendTime(0.0f)
	, _isPause(false)
{
}


skinnedMesh::~skinnedMesh()
{
}

#ifdef UNICODE
void skinnedMesh::init(const WCHAR* folder, const WCHAR* file)
{
	wstring filePath = folder + wstring(L"\\") + file;

	AllocatedHierachy ah;
	ah.setTextureFolder(wstring(folder)); 

	if (FAILED(D3DXLoadMeshHierarchyFromX(filePath.c_str(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		D3DDEVICE,
		&ah,
		0,
		&_root,
		&_aniController)))
	{
		return;
	}

	this->setBoneMatrixPtrs(_root);

	_maxAnimationSet = _aniController->GetMaxNumAnimationSets();
}

void skinnedMesh::init(wstring keyName, const WCHAR* folder, const WCHAR* file)
{
	skinnedMesh* newMesh = SKINNEDMESHMANAGER->addSkinnedMesh(keyName, folder, file);

	_root = newMesh->_root;

	newMesh->_aniController->CloneAnimationController(
		newMesh->_aniController->GetMaxNumAnimationOutputs(),
		newMesh->_aniController->GetMaxNumAnimationSets(),
		newMesh->_aniController->GetMaxNumTracks(),
		newMesh->_aniController->GetMaxNumEvents(),
		&_aniController);

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

void skinnedMesh::init(wstring keyName, const WCHAR* folder, const WCHAR* file)
{
	skinnedMesh* newMesh = SKINNEDMESHMANAGER->addSkinnedMesh(keyName, folder, file);

	_root = newMesh->_root;

	newMesh->_aniController->CloneAnimationController(
		SKINNEDMESHMANAGER->findMesh(keyName)->_aniController->GetMaxNumAnimationOutputs(),
		SKINNEDMESHMANAGER->findMesh(keyName)->_aniController->GetMaxNumAnimationSets(),
		SKINNEDMESHMANAGER->findMesh(keyName)->_aniController->GetMaxNumTracks(),
		SKINNEDMESHMANAGER->findMesh(keyName)->_aniController->GetMaxNumEvents(),
		&_aniController);
}
#endif

void skinnedMesh::release()
{
	if (_root)
	{
		AllocatedHierachy ah;
		D3DXFrameDestroy(_root, &ah);
	}

	SAFE_RELEASE(_aniController);
}

void skinnedMesh::destroy()
{
	SAFE_RELEASE(_aniController);
}

void skinnedMesh::update()
{

	D3DXTRACK_DESC temp;
	_aniController->GetTrackDesc(1, &temp);
	if (temp.Enable)
	{
		LPD3DXANIMATIONSET anim = NULL;
		D3DXTRACK_DESC desc;
		_aniController->GetTrackAnimationSet(1, &anim);

		float period = anim->GetPeriod();
		float current = fmod(temp.Position, period);

		SAFE_RELEASE(anim);
		if (current >= period - 0.1f)
			_aniController->SetTrackPosition(1, period - 0.1f);
		// 이거 있는게 맞는거같은게
		// 만약 애니메이션이 끝나서 상태가 공격->아이들로 바뀌면
		// 1번트랙에 아이들이고 0번트랙에 공격이잖아??ㅇㅇ
		// 근데 밑에 저걸 해버리면
		// 아이들 상태 애니메이션도 처음으로 돌아가버려서
		// 결국 아이들상태 첫 애니메이션이랑 공격애니메이션이랑 블렌드가 되버린단말이지
		// 근데 상관없지않아?? 상관있지
		// 음 예를들어 공격->아이들이라 할 때
		// 공격모션 끝이 팔을 뻗은 애니메이션이야
		// 그럼 팔을 뻗은거부터 아이들로 돌아와야할거아냐??ㅇㅇ
		// 근데 공격모션 처음부분은 팔을 잽 날리기 직전ㅇ이ㅏㄴ아거앚이ㅏ아아아아아아아아아아 뭔소린지 알겟어 ㅇㅋㅇㅋ
		// 그래서 만약 트랙1번이 켜져있을 때(블렌딩이 필요할 때
		// 트랙1번을 가장 마지막으로 고정시켜두는거임 ㅇㅎ ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ

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
	}
	
}

void skinnedMesh::update(LPD3DXFRAME frame, LPD3DXFRAME parent)
{
	tagBone* bone = (tagBone*)frame;
	bone->combinedTransformationMatrix = bone->TransformationMatrix;

	// ?? 어디서 2번 곱해짐??
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

void skinnedMesh::render(float elapsedTime)
{
	if (!_isPause)
	{
		if (SCENEMANAGER->isCurrentIsParent())
			_aniController->AdvanceTime(elapsedTime, NULL);
		else if (SCENEMANAGER->getCurrentScene() == SCENEMANAGER->findChild(_T("storyScene"), _T("appearScene")))
			_aniController->AdvanceTime(elapsedTime / 3, NULL);
	}

	this->update(_root);
	this->updateSkinnedMesh(_root);

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

	_currentAnimationSet = index;

	//_aniController->ResetTime();
	_aniController->SetTrackPosition(0, 0);

	_isPause = false;
	
	SAFE_RELEASE(temp);
}

void skinnedMesh::setAnimationIndexBlend(UINT index)
{
	LPD3DXANIMATIONSET prev = NULL;
	LPD3DXANIMATIONSET next = NULL;

	// 0번 트랙을 1번트랙으로 옮겨줌
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
	_aniController->SetTrackPosition(0, 0);
	//_aniController->SetTrackPosition(1, 0); 
	
	_currentAnimationSet = index;

	_isPause = false;

	SAFE_RELEASE(prev);
	SAFE_RELEASE(next);
}

bool skinnedMesh::IsAnimationEnd()
{
	return (this->getCurrentAnimationRate() >= (0.9f - FLT_EPSILON));
}

float skinnedMesh::getCurrentAnimationRate()
{
	LPD3DXANIMATIONSET anim = NULL;
	D3DXTRACK_DESC desc;
	_aniController->GetTrackAnimationSet(0, &anim);
	_aniController->GetTrackDesc(0, &desc);

	float period = anim->GetPeriod();
	float current = desc.Position / period;

	SAFE_RELEASE(anim);

	return current;
}
