#include "stdafx.h"
#include "sceneManager.h"

#ifdef UNICODE
// ¾À ³ëµå
HRESULT sceneNode::init()
{
	if (FAILED(_parent->init()))
		return E_FAIL;

	map<wstring, _scene*>::iterator key = _child.begin();

	for (; key != _child.end(); ++key)
	{
		if (key->second)
		{
			if (FAILED(key->second->init()))
				return E_FAIL;
		}
	}
	
	return this->changeParent();
}

void sceneNode::release()
{
	SAFE_OBJRELEASE(_parent);
	this->deleteAll();
}

void sceneNode::sceneRelease()
{
	_parent->release();

	map<wstring, _scene*>::iterator iter = _child.begin();
	
	for (; iter != _child.end(); ++iter)
	{
		if (iter->second)
			iter->second->release();
	}
}

void sceneNode::update()
{
	if (_currentScene)
		_currentScene->update();
}

void sceneNode::render(bool isParentRendr)
{
	if (!_currentScene) return;

	if (isParentRendr)
	{
		if (_parent != _currentScene)
			_parent->render();
	}
	_currentScene->render();
}

_scene* sceneNode::addChild(wstring name, _scene* child)
{
	if (!child) return NULL;

	_scene* c = this->findChild(name);

	if (c)
	{
		SAFE_OBJRELEASE(child);
		return c;
	}

	_child.insert(make_pair(name, child));

	return child;
}

_scene* sceneNode::findParent()
{
	return _parent;
}

_scene* sceneNode::findChild(wstring name)
{
	map<wstring, _scene*>::iterator key = _child.find(name);

	if (key != _child.end())
		return key->second;

	return NULL;
}

HRESULT sceneNode::changeChild(wstring name)
{
	_scene* next = this->findChild(name);

	if (!next)
		return E_FAIL;

	_currentScene = next;

	return S_OK;
}

HRESULT sceneNode::changeParent()
{
	_currentScene = _parent;

	if (!_currentScene)
		return E_FAIL;

	return S_OK;
}

BOOL sceneNode::deleteChild(wstring name)
{
	map<wstring, _scene*>::iterator key = _child.find(name);

	if (key != _child.end())
	{
		SAFE_OBJRELEASE(key->second);
		_child.erase(key);
		return TRUE;
	}

	return FALSE;
}

BOOL sceneNode::deleteAll()
{
	map<wstring, _scene*>::iterator key = _child.begin();

	for (;key != _child.end();)
	{
		if (key->second)
		{
			SAFE_OBJRELEASE(key->second);
			key = _child.erase(key);
		}
		else ++key;
	}

	_child.clear();

	return TRUE;
}

// ¾À ¸Å´ÏÀú
sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

sceneNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

HRESULT sceneManager::sceneInit()
{
	if (!_currentScene) return E_FAIL;

	return _currentScene->init();
}

HRESULT sceneManager::sceneInit(wstring sceneName)
{
	sceneNode* s = this->findScene(sceneName);

	if (!s) return E_FAIL;

	return s->init();
}

HRESULT sceneManager::currentSceneInit()
{
	return _currentScene->getCurrentScene()->init();
}

void sceneManager::release()
{
	map<wstring, sceneNode*>::iterator key = _mSceneList.begin();

	for (; key != _mSceneList.end();)
	{
		if (key->second)
		{
			SAFE_OBJRELEASE(key->second);
			key = _mSceneList.erase(key);
		}
		else ++key;
	}

	_mSceneList.clear();
}

void sceneManager::sceneRelease()
{
	if (_currentScene)
		_currentScene->sceneRelease();
}

void sceneManager::update()
{
	if (_currentScene)
		_currentScene->update();
}

void sceneManager::render(bool isParentRender)
{
	if (_currentScene)
		_currentScene->render(isParentRender);
}

sceneNode* sceneManager::findScene(wstring sceneName)
{
	map<wstring, sceneNode*>::iterator key = _mSceneList.find(sceneName);

	if (key != _mSceneList.end())
		return key->second;

	return NULL;
}

_scene * sceneManager::findParent(wstring sceneName)
{
	map<wstring, sceneNode*>::iterator key = _mSceneList.find(sceneName);

	if (key != _mSceneList.end())
		return key->second->findParent();

	return NULL;
}

_scene* sceneManager::findChild(wstring parent, wstring child)
{
	map<wstring, sceneNode*>::iterator key = _mSceneList.find(parent);

	if (key != _mSceneList.end())
		return key->second->findChild(child);

	return NULL;
}

sceneNode* sceneManager::addScene(wstring sceneName, _scene* scene)
{
	sceneNode* s = this->findScene(sceneName);

	if (s)
	{
		SAFE_OBJRELEASE(scene);
		return s;
	}
	s = new sceneNode;
	s->setParent(scene);

	_mSceneList.insert(make_pair(sceneName, s));

	return s;
}

_scene* sceneManager::addChild(wstring parent, wstring child, _scene* scene)
{
	sceneNode* s = this->findScene(parent);

	if (s) return s->addChild(child, scene);

	return NULL;
}

HRESULT sceneManager::changeScene(wstring sceneName)
{
	sceneNode* next = this->findScene(sceneName);

	if (!next) return E_FAIL;

	this->sceneRelease();
	_currentScene = next;

	return S_OK;
}

HRESULT sceneManager::changeChild(wstring childName)
{
	return _currentScene->changeChild(childName);
}

HRESULT sceneManager::changeParent()
{
	return _currentScene->changeParent();
}

#else
// ¾À ³ëµå
HRESULT sceneNode::init()
{
	if (FAILED(_parent->init()))
		return E_FAIL;

	map<string, _scene*>::iterator key = _child.begin();

	for (; key != _child.end(); ++key)
	{
		if (key->second)
		{
			if (FAILED(key->second->init()))
				return E_FAIL;
		}
	}

	return this->changeParent();
}

void sceneNode::release()
{
	SAFE_OBJRELEASE(_parent);
	this->deleteAll();
}

void sceneNode::update()
{
	if (_currentScene)
		_currentScene->update();
}

void sceneNode::render()
{
	if (!_currentScene) return;

	if (_parent != _currentScene)
		_parent->render();
	_currentScene->render();
}

_scene* sceneNode::addChild(string name, _scene* child)
{
	if (!child) return NULL;

	_scene* c = this->findChild(name);

	if (c)
	{
		SAFE_OBJRELEASE(child);
		return c;
	}

	_child.insert(make_pair(name, child));

	return child;
}

_scene* sceneNode::findChild(string name)
{
	map<string, _scene*>::iterator key = _child.find(name);

	if (key != _child.end())
		return key->second;

	return NULL;
}

HRESULT sceneNode::changeChild(string name)
{
	_scene* next = this->findChild(name);

	if (!next)
		return E_FAIL;

	_currentScene = next;

	return S_OK;
}

HRESULT sceneNode::changeParent()
{
	_currentScene = _parent;

	if (!_currentScene)
		return E_FAIL;

	return S_OK;
}

BOOL sceneNode::deleteChild(string name)
{
	map<string, _scene*>::iterator key = _child.find(name);

	if (key != _child.end())
	{
		SAFE_OBJRELEASE(key->second);
		_child.erase(key);
		return TRUE;
	}

	return FALSE;
}

BOOL sceneNode::deleteAll()
{
	map<string, _scene*>::iterator key = _child.begin();

	for (; key != _child.end();)
	{
		if (key->second)
		{
			SAFE_OBJRELEASE(key->second);
			key = _child.erase(key);
		}
		else ++key;
	}

	_child.clear();

	return TRUE;
}

// ¾À ¸Å´ÏÀú
sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

sceneNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

HRESULT sceneManager::sceneInit(string sceneName)
{
	sceneNode* s = this->findScene(sceneName);

	if (!s) return E_FAIL;

	return s->init();
}

void sceneManager::release()
{
	map<string, sceneNode*>::iterator key = _mSceneList.begin();

	for (; key != _mSceneList.end();)
	{
		if (key->second)
		{
			SAFE_OBJRELEASE(key->second);
			key = _mSceneList.erase(key);
		}
		else ++key;
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene)
		_currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene)
		_currentScene->render();
}

sceneNode* sceneManager::findScene(string sceneName)
{
	map<string, sceneNode*>::iterator key = _mSceneList.find(sceneName);

	if (key != _mSceneList.end())
		return key->second;

	return NULL;
}

_scene* sceneManager::findChild(string parent, string child)
{
	map<string, sceneNode*>::iterator key = _mSceneList.find(parent);

	if (key != _mSceneList.end())
		return key->second->findChild(child);

	return NULL;
}

sceneNode* sceneManager::addScene(string sceneName, _scene* scene)
{
	sceneNode* s = this->findScene(sceneName);

	if (s)
	{
		SAFE_OBJRELEASE(s);
		return s;
	}
	s = new sceneNode;
	s->setParent(scene);

	_mSceneList.insert(make_pair(sceneName, s));

	return s;
}

_scene* sceneManager::addChild(string parent, string child, _scene* scene)
{
	sceneNode* s = this->findScene(parent);

	if (s) return s->addChild(child, scene);

	return NULL;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	sceneNode* next = this->findScene(sceneName);

	if (!next) return E_FAIL;

	_currentScene = next;

	return S_OK;
}

HRESULT sceneManager::changeChild(string childName)
{
	return _currentScene->changeChild(childName);
}

HRESULT sceneManager::changeParent()
{
	return _currentScene->changeParent();
}
#endif
