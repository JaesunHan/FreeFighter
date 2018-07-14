#pragma once

class enemy;

class state
{
protected:
	enemy* _owner;
public:
	virtual void Update() = 0;

	inline void setEnemy(enemy* e) { _owner = e; }
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

// �ǰ�
class damage01 : public state
{
private:

public:
	damage01() {};
	~damage01() {};

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
