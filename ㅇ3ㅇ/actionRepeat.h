#pragma once
#include "action.h"

#include <list>
using namespace std;

class actionRepeat : public action, public _actionDelegate
{
	list<action*>			_actions;
	list<action*>::iterator	_currentAction;
public:
	actionRepeat();
	virtual ~actionRepeat();

	void addAction(action* a);

	virtual void start() override;
	virtual void update() override;

	virtual void onActionFinish(action* sender) override;
};

