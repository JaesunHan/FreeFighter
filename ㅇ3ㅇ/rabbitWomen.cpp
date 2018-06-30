#include "stdafx.h"
#include "rabbitWomen.h"
#include "objectNode.h"


rabbitWomen::rabbitWomen()
	: _root(NULL)
{
}


rabbitWomen::~rabbitWomen()
{
}

void rabbitWomen::init()
{
	if (_root)
		_root->setParentMatrix(&_worldMatrix);
}

void rabbitWomen::release()
{
	if (_root)
		_root->release();
}

void rabbitWomen::update()
{
	character::update();

	if (_root)
		_root->update();
}

void rabbitWomen::render()
{
	if (_root)
		_root->render();
}
