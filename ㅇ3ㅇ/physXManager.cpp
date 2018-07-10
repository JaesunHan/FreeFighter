#include "stdafx.h"
#include "physXManager.h"


physXManager::physXManager()
	: _foundation(NULL)
	, _physics(NULL)
	, _dispatcher(NULL)
	, _sceneDesc(NULL)
{
}

physXManager::~physXManager()
{
}

HRESULT physXManager::init(bool isInteractive)
{
	_foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, _allocator, _errorCallBack);

	_physics = PxCreatePhysics(PX_PHYSICS_VERSION, (*_foundation), PxTolerancesScale(), true);

	_sceneDesc = new PxSceneDesc(_physics->getTolerancesScale());
	_sceneDesc->gravity = PxVec3(0.0f, -9.81f, 0.0f);
	_dispatcher = PxDefaultCpuDispatcherCreate(2);
	_sceneDesc->cpuDispatcher = _dispatcher;
	_sceneDesc->filterShader = PxDefaultSimulationFilterShader;
	
	return S_OK;
}

void physXManager::release(bool isInteractive)
{
	PX_UNUSED(isInteractive);

	if (_dispatcher)
	{
		_dispatcher->release();
		_dispatcher = NULL;
	}

	if (_physics)
	{
		_physics->release();
		_physics = NULL;
	}

	if (_foundation)
	{
		_foundation->release();
		_foundation = NULL;
	}

	SAFE_DELETE(_sceneDesc);
}

void physXManager::createScene(OUT PxScene** scene, OUT PxMaterial** material)
{
	(*scene) = _physics->createScene((*_sceneDesc));

	(*material) = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane((*_physics), PxPlane(0,1,0,0), (*(*material)));
	(*scene)->addActor((*groundPlane));
}
