#pragma once
class action;
class _actionDelegate
{
public:
	virtual void onActionFinish(action* sender) = 0;
};

class objectNode;

class action
{
public:
	action();
	virtual ~action();

protected:
	objectNode*	_owner;
	_actionDelegate* _delegate;

public:
	virtual void start() = 0;
	virtual void update() = 0;

	inline objectNode* getOwner() { return _owner; }
	inline void setOwner(objectNode* e) { _owner = e; }

	inline _actionDelegate* getDelegate() { return _delegate; }
	inline void setDelegate(_actionDelegate* d) { _delegate = d; }
};

