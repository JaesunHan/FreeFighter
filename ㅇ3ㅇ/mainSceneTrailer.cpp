#include "stdafx.h"
#include "mainSceneTrailer.h"
#include "mainSceneCharacter.h"
#include "camera.h"
#include "grid.h"


mainSceneTrailer::mainSceneTrailer()
	: _physXScene(NULL)
	, _material(NULL)
	, _cm(NULL)
	, _camera(NULL)
	, _grid(NULL)
{
}


mainSceneTrailer::~mainSceneTrailer()
{
}

HRESULT mainSceneTrailer::init()
{
	//물리엔진이 적용되는 신 생성
	PHYSX->createScene(&_physXScene, &_material);
	_cm = PxCreateControllerManager(*_physXScene);
	_cm->setOverlapRecoveryModule(false);

	wstring name[4] = 
	{
		_T("zealot"),
		_T("reaper"),
		_T("woodGiant"),
		_T("fepee")
	};

	_vCharacters.resize(4);
	for (int i = 0; i < _vCharacters.size(); ++i)
	{
		wstring filePath = _T(".\\xFile\\") + name[i];
		wstring key = name[i] + _T(".X");

		_vCharacters[i] = new mainSceneCharacter;
		_vCharacters[i]->init(filePath, key);

		_vCharacters[i]->createContoller(&_cm, _material);
	}

	_camera = new camera;
	_camera->init();

	_grid = new grid;
	_grid->init(WHITE, 10, 0.0f);

	this->resetAni();

	return S_OK;
}

void mainSceneTrailer::release()
{
	SAFE_OBJRELEASE(_camera);
	SAFE_OBJRELEASE(_grid);

	for (int i = 0; i < _vCharacters.size(); ++i)
		SAFE_OBJRELEASE(_vCharacters[i]);
	_vCharacters.clear();
}

void mainSceneTrailer::update()
{
	if (_vCharacters[_currentChar1])
		_vCharacters[_currentChar1]->update();

	if (_vCharacters[_currentChar2])
		_vCharacters[_currentChar2]->update();


	if (_camera)
	{
		D3DXVECTOR3 char1Pos = _vCharacters[_currentChar1]->getWorldPos();
		char1Pos.x += 3.0f;
		D3DXVECTOR3 char2Pos = _vCharacters[_currentChar2]->getWorldPos();
		char2Pos.x -= 3.0f;
		D3DXVECTOR3 focus = (char1Pos + char2Pos) / 2;
		focus.y = 1.5f;

		_camera->update(&focus, (char1Pos.x - char2Pos.x));
	}
}

void mainSceneTrailer::render()
{
	if (_vCharacters[_currentChar1])
		_vCharacters[_currentChar1]->render();

	if (_vCharacters[_currentChar2])
		_vCharacters[_currentChar2]->render();

	if (_grid)
		_grid->render();
}

void mainSceneTrailer::resetAni()
{
	_currentTime = 0.0f;

	_currentChar1 = -1;
	_currentChar2 = -1;

	_currentChar1 = RND->getInt(4);
	do
	{
		_currentChar2 = RND->getInt(4);
	} while (_currentChar1 == _currentChar2);

	if (_vCharacters[_currentChar1])
	{
		_vCharacters[_currentChar1]->changeAnimation(ANI_MOVE);
		_vCharacters[_currentChar1]->setPosition(D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	}

	if (_vCharacters[_currentChar2])
	{
		_vCharacters[_currentChar2]->changeAnimation(ANI_MOVE);
		_vCharacters[_currentChar2]->setPosition(D3DXVECTOR3(-10.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	}
}
