#pragma once

#include <map>
using namespace std;

#include "sceneInterface.h"

#define SCENEMANAGER sceneManager::GetInstance()

#ifdef UNICODE
class sceneNode
{
private:
	_scene* _parent;
	_scene* _currentScene;
	map<wstring, _scene*> _child;

public:
	sceneNode() {};
	~sceneNode() {};

	HRESULT init();
	void release();
	void sceneRelease();
	void update();
	void render();

	_scene* addChild(wstring name, _scene* child);

	_scene* findParent();
	_scene* findChild(wstring name);

	HRESULT changeChild(wstring name);
	HRESULT changeParent();

	BOOL deleteChild(wstring name);
	BOOL deleteAll();

	inline void setParent(_scene* p) { _parent = _currentScene = p; }

	inline _scene* getCurrentScene() { return _currentScene; }
	inline _scene* getParentScene() { return _parent; }
};

class sceneManager
{
	SINGLETONE(sceneManager)

private:
	static sceneNode* _currentScene;

	map<wstring, sceneNode*>	_mSceneList;

public:
	HRESULT init();
	HRESULT sceneInit();
	HRESULT sceneInit(wstring sceneName);
	HRESULT currentSceneInit();
	void release();
	void sceneRelease();
	void update();
	void render();

	sceneNode* findScene(wstring sceneName);
	_scene* findParent(wstring sceneName);
	_scene* findChild(wstring parent, wstring child);

	sceneNode* addScene(wstring sceneName, _scene* scene);
	_scene* addChild(wstring parent, wstring child, _scene* scene);

	HRESULT changeScene(wstring sceneName);
	HRESULT changeChild(wstring childName);
	HRESULT changeParent();

	inline _scene* getCurrentScene() { return _currentScene->getCurrentScene(); }
	inline bool isCurrentIsParent() { return (_currentScene->getCurrentScene() == _currentScene->getParentScene()); }
};
#else
class sceneNode
{
private:
	_scene * _parent;
	_scene* _currentScene;
	map<string, _scene*> _child;

public:
	sceneNode() {};
	~sceneNode() {};

	_scene* addChild(string name, _scene* child);
	_scene* findChild(string name);
	HRESULT changeChild(string name);
	HRESULT changeParent();
	BOOL deleteChild(string name);
	BOOL deleteAll();
	void release();
};

class sceneManager
{
	SINGLETONE(sceneManager)

private:
	static sceneNode* _currentScene;

	map<string, sceneNode*>	_mSceneList;

public:
	HRESULT init();
	HRESULT sceneInit(string sceneName);
	void release();
	void update();
	void render();

	sceneNode* findScene(string sceneName);
	_scene* findChild(string parnet, string child);

	sceneNode* addScene(string sceneName, _scene* scene);
	_scene* addChild(string parent, string sceneName, _scene* scene);

	HRESULT changeScene(string sceneName);
	HRESULT changeChild(string childName);
	HRESULT changeParent();
};
#endif
