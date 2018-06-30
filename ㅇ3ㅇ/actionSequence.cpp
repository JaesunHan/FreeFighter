#include "stdafx.h"
#include "actionSequence.h"


actionSequence::actionSequence()
{
}


actionSequence::~actionSequence()
{
	for (auto p : _actions)
	{
		SAFE_DELETE(p);
	}
	_actions.clear();
}

void actionSequence::addAction(action* a)
{
	_actions.push_back(a);
}

void actionSequence::start()
{
	if (_actions.empty())
		return;

	_currentAction = _actions.begin();
	(*_currentAction)->start();
}

void actionSequence::update()
{
	if (_currentAction == _actions.end())
		return;

	(*_currentAction)->update();
}

void actionSequence::onActionFinish(action* sender)
{
	if (_currentAction == _actions.end())
		return;

	_currentAction++;

	if (_currentAction == _actions.end())
		return;

	(*_currentAction)->start();
}
