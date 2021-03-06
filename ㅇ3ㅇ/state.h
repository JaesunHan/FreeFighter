#pragma once

class enemy;

class state
{
protected:
	enemy* _enemy;

public:
	virtual void Update() = 0;

	inline void setEnemy(enemy* e) { _enemy = e; }
};

// 등장씬
class appear : public state
{
private:

public:
	appear() {};
	~appear() {};
	// state을(를) 통해 상속됨
	virtual void Update() override;
};

// 가만히
class idle : public state
{
private:

public:
	idle() {};
	~idle() {};
	// state을(를) 통해 상속됨
	virtual void Update() override;
};

// 달리기
class run : public state
{
private:

public:
	run() {};
	~run() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

// 랜덤 달리기
class rndRun : public state
{
private:
	int _rndCount;

public:
	rndRun() { _rndCount = 0; }
	~rndRun() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

// 집으로 달리기
class goHome : public state
{
private:

public:
	goHome() {};
	~goHome() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

// 피격
class damaged : public state
{
private:
	float _speed;

public:
	damaged() { _speed = 0.05f; }
	~damaged() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

// 피격
class recovery : public state
{
private:

public:
	recovery() {};
	~recovery() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

//죽음
class death : public state
{
private:

public:
	death() {};
	~death() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

//공격
class attack01 : public state
{
private:

public:
	attack01() {};
	~attack01() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

class attack02 : public state
{
private:

public:
	attack02() {};
	~attack02() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

class attack03 : public state
{
private:

public:
	attack03() {};
	~attack03() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};


class skill01 : public state
{
private:

public:
	skill01() {};
	~skill01() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};
class skill02 : public state
{
private:

public:
	skill02() {};
	~skill02() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};
class skill03 : public state
{
private:

public:
	skill03() {};
	~skill03() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};
