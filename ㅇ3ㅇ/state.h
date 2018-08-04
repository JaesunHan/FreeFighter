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

// �����
class appear : public state
{
private:

public:
	appear() {};
	~appear() {};
	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

// ������
class idle : public state
{
private:

public:
	idle() {};
	~idle() {};
	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

// �޸���
class run : public state
{
private:

public:
	run() {};
	~run() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

// ���� �޸���
class rndRun : public state
{
private:
	int _rndCount;

public:
	rndRun() { _rndCount = 0; }
	~rndRun() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

// ������ �޸���
class goHome : public state
{
private:

public:
	goHome() {};
	~goHome() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

// �ǰ�
class damaged : public state
{
private:
	float _speed;

public:
	damaged() { _speed = 0.05f; }
	~damaged() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

// �ǰ�
class recovery : public state
{
private:

public:
	recovery() {};
	~recovery() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

//����
class death : public state
{
private:

public:
	death() {};
	~death() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

//����
class attack01 : public state
{
private:

public:
	attack01() {};
	~attack01() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

class attack02 : public state
{
private:

public:
	attack02() {};
	~attack02() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};

class attack03 : public state
{
private:

public:
	attack03() {};
	~attack03() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};


class skill01 : public state
{
private:

public:
	skill01() {};
	~skill01() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};
class skill02 : public state
{
private:

public:
	skill02() {};
	~skill02() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};
class skill03 : public state
{
private:

public:
	skill03() {};
	~skill03() {};

	// state��(��) ���� ��ӵ�
	virtual void Update() override;
};
