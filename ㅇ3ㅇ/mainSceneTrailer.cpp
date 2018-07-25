#include "stdafx.h"
#include "mainSceneTrailer.h"
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
	return S_OK;
}

void mainSceneTrailer::release()
{
	SAFE_OBJRELEASE(_camera);
	SAFE_OBJRELEASE(_grid);
}

void mainSceneTrailer::update()
{
}

void mainSceneTrailer::render()
{
}
