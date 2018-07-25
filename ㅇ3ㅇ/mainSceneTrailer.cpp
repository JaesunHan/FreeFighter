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
	IMAGEMANAGER->addImage(_T("whiteMask"), _T(".\\texture\\whiteMask.bmp"));

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
		_vCharacters[i]->setPosition(D3DXVECTOR3(100, 100, 100), D3DXVECTOR3(1, 0, 0));
	}

	_camera = new camera;
	_camera->init();

	_grid = new grid;
	_grid->init(WHITE, 15, 0.0f);

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
	D3DXVECTOR3 char1Pos;
	D3DXVECTOR3 char2Pos;

	char1Pos = _vCharacters[_currentChar1]->getWorldPos();
	char1Pos.x += 3.0f;
	char2Pos = _vCharacters[_currentChar2]->getWorldPos();
	char2Pos.x -= 3.0f;
	_focus = (char1Pos + char2Pos) / 2;
	_focus.y = 1.5f;

	if (_vCharacters[_currentChar1] && _vCharacters[_currentChar2])
	{
		if (_vCharacters[_currentChar1]->isCrush() &&
			_vCharacters[_currentChar2]->isCrush())
		{
			_aniElapsedTime = 0.0f;

			if (!_isWhiteEnd)
			{
				_whiteAlpha += 5;
				if (_whiteAlpha > 255)
				{
					_whiteAlpha = 255;
					_isWhiteEnd = true;
				}
			}
			else
			{
				_focus = D3DXVECTOR3(5000, 5000, 5000);
				_whiteAlpha -= 2;
				if (_whiteAlpha < 0)
				{
					_whiteAlpha = 0;
					this->resetAni();
				}
			}
		}
		else
		{
			_aniElapsedTime = TIMEMANAGER->getElapsedTime();
			_currentTime += TIMEMANAGER->getElapsedTime();
			if (_currentTime > 6.0f)
			{
				_vCharacters[_currentChar1]->changeAnimation(ANI_MOVE);
				_vCharacters[_currentChar2]->changeAnimation(ANI_MOVE);
			}

			_vCharacters[_currentChar1]->update();
			_vCharacters[_currentChar2]->update();
		}
	}

	if (_camera)
		_camera->update(&_focus, (char1Pos.x - char2Pos.x));
}

void mainSceneTrailer::render()
{
	if (_vCharacters[_currentChar1])
		_vCharacters[_currentChar1]->render(_aniElapsedTime);

	if (_vCharacters[_currentChar2])
		_vCharacters[_currentChar2]->render(_aniElapsedTime);

	if (_grid)
		_grid->render();

	if (_vCharacters[_currentChar1]->isCrush() &&
		_vCharacters[_currentChar2]->isCrush())
		IMAGEMANAGER->alphaRender(_T("whiteMask"), _whiteAlpha);
}

void mainSceneTrailer::resetAni()
{
	_aniElapsedTime = TIMEMANAGER->getElapsedTime();
	_currentTime = 0.0f;

	_isWhiteEnd = false;
	_whiteAlpha = 0;

	_currentChar1 = -1;
	_currentChar2 = -1;

	_currentChar1 = RND->getInt(4);
	do
	{
		_currentChar2 = RND->getInt(4);
	} while (_currentChar1 == _currentChar2);

	if (_vCharacters[_currentChar1])
	{
		_vCharacters[_currentChar1]->changeAnimation(ANI_IDLE);
		_vCharacters[_currentChar1]->setPosition(D3DXVECTOR3(15.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	}

	if (_vCharacters[_currentChar2])
	{
		_vCharacters[_currentChar2]->changeAnimation(ANI_IDLE);
		_vCharacters[_currentChar2]->setPosition(D3DXVECTOR3(-15.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	}
}
