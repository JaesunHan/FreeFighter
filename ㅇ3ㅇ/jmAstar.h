#pragma once

// �̰��� �������� �׽�Ʈ aStar Ŭ�����Դϴ�
// ���߿� ������������ �� Ȯ���� �ſ� ���� ������
// ...... ���Ŵϴ�.

class enemy;

class jmAstar
{
private:

public:
	jmAstar();
	~jmAstar();

	void FindPath(D3DXVECTOR3* target, enemy* front, enemy* back);

	
};

