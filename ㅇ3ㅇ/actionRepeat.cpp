#include "stdafx.h"
#include "actionRepeat.h"


actionRepeat::actionRepeat()
{
}


actionRepeat::~actionRepeat()
{
	for (auto p : _actions)
	{
		SAFE_DELETE(p);
	}
	_actions.clear();
}

void actionRepeat::addAction(action* a)
{
	_actions.push_back(a);
}

void actionRepeat::start()
{
	if (_actions.empty())
		return;

	_currentAction = _actions.begin();
	(*_currentAction)->start();
}

void actionRepeat::update()
{
	if (_currentAction == _actions.end())
		return;

	(*_currentAction)->update();
}

void actionRepeat::onActionFinish(action* sender)
{
	_currentAction++;

	if (_currentAction == _actions.end())
	_currentAction = _actions.begin();

	(*_currentAction)->start();
}