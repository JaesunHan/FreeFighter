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

class rndRun : public state
{
private:

public:
	rndRun() {};
	~rndRun() {};

	// state을(를) 통해 상속됨
	virtual void Update() override;
};

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
class damage01 : public state
{
private:

public:
	damage01() {};
	~damage01() {};

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
