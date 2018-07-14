#pragma once

#include "state.h"

class enemy;

class stateContext
{
private:
	state* _state;

public:
	stateContext();
	~stateContext();

	void setState(state* s, enemy* e) { SAFE_DELETE(_state); _state = s; _state->setEnemy(e);  }

	void Update() { _state->Update(); }
};

