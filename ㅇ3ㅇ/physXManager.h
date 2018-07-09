#pragma once

//Set this to the IP address of the system running the PhysX Visual Debugger that you want to connect to.
#define PVD_HOST "127.0.0.1"

#define PHYSX physXManager::GetInstance()

class physXManager
{
	SINGLETONE(physXManager)

private:
	PxDefaultAllocator		_allocator;
	PxDefaultErrorCallback	_errorCallBack;

	PxFoundation*			_foundation;
	PxPhysics*				_physics;

	PxDefaultCpuDispatcher*	_dispatcher;

	PxSceneDesc*			_sceneDesc;

public:
	HRESULT init(bool isInteractive = true);
	void release(bool isInteractive = true);

	void createScene(OUT PxScene** scene, OUT PxMaterial** material);

	inline PxPhysics* getPhysics() { return _physics; }
};

