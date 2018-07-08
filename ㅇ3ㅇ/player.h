#pragma once
#include "interfaceCharacter.h"
#include "playerController.h"

#include "playerKeySet.h"




class player : public interfaceCharacter, public playerController
{
protected:

	enum Charactor
	{
		CHARACTOR_NONE = -1,
		CHARACTOR_ARANZEBIA,
		CHARACTOR_GIGAS,
		CHARACTOR_KNIGHT,
		CHARACTOR_LUCIUS,
		CHARACTOR_END
	};

	Charactor	_Charactor;

private:


	int n;

	PLAYER_KEYSET	_keySet;

public:
	player();
	virtual ~player();

	// interfaceCharacter에게 상속받은 함수
	virtual void Init(PLAYERS p, wstring keyPath, wstring keyName);
	virtual void Update() override;
	virtual void Render() override;

	//void movement();

};

