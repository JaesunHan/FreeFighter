#pragma once
#include "enemy.h"

#define COOLTIME 200

class fightEnemy : public enemy
{
protected:
	int		_coolTime[3];
	bool	_useSkill[3];

	bool	_isFastSkillOn;
	int		_fastSkillCount;

public:
	fightEnemy();
	~fightEnemy();

	virtual void Init(wstring keyPath, wstring keyName);
	virtual void Update();
	virtual void Render(float elapsedTime = TIMEMANAGER->getElapsedTime());

	virtual void EnemyFightAI();

	virtual void UseSkill01();
	virtual void UseSkill02();
	virtual void UseSkill03();

};

