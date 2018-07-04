#pragma once
#include "interfaceCharacter.h"
#include "playerController.h"



class player : public interfaceCharacter, public playerController
{
private:

public:
	player();
	virtual ~player();

	// interfaceCharacter���� ��ӹ��� �Լ�
	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update() override;
	virtual void Render() override;



};

