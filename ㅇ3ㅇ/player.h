#pragma once
#include "interfaceCharacter.h"
#include "playerController.h"



class player : public interfaceCharacter, public playerController
{
private:

public:
	player();
	virtual ~player();

	// interfaceCharacter에게 상속받은 함수
	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update() override;
	virtual void Render() override;



};

