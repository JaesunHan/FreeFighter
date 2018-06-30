#pragma once
#include "action.h"

#include <list>
using namespace std;

class actionSequence : public action, public _actionDelegate
{
protected:
	list<action*>			_actions;
	list<action*>::iterator	_currentAction;

public:
	actionSequence();
	virtual ~actionSequence();

	void addAction(action* a);

	virtual void start() override;
	virtual void update() override;

	virtual void onActionFinish(action* sender) override;
};

