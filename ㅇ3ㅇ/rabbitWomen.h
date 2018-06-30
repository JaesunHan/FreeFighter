#pragma once
#include "character.h"

class objectNode;

class rabbitWomen : public character
{
private:
	objectNode* _root;

public:
	rabbitWomen();
	~rabbitWomen();

	void init();
	void release();
	void update();
	void render();

	inline void setRoot(objectNode* r) { _root = r; }
};

