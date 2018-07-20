#pragma once

class progressBar
{
private:
	wstring	_keyName;

	float	_maxWidth;
	float	_width;

	float	_fromGauge;		//���� ü�¹� ��ġ
	float	_toGauge;		//������ ü�¹� ��ġ

	float	_maxHp;			//�� ü��
	float	_currentHp;		//���� ü��

	float	_isHit;			//�¾ҳ�
	float	_currentTime;	//����ð�
	float	_totalTime;		//�ѽð�

	image*	_hpBarBack;
	image*	_hpBarHalf;		//��� ���� �����Դϴ�. �ٸ����� ���� �����ϴ� mayBe
	image*  _hpBarAlmost;	//��� ���� �����Դϴ�. �ٸ����� ���� �����ϴ� mayBe
	image*	_hpBarFront;

public:
	progressBar();
	~progressBar();

	// Ű�� , ���ϰ�� (ù .\\���� �ȵ�) , �����̸� (ù \\���� �ȵ�) , �������� , maxHp
	void Init(wstring keyName, wstring filePath, wstring fileName, wstring fileForm , float maxHp);
	// ���� ü��
	void Update(float currentGauge);
	void Update(float currentGauge, float maxGauge);
	// 2D���� ��ǥ x, y
	void Render(float x, float y);
	void Render(float x, float y, D3DXVECTOR3 sca);
	// 3D��ǥ ������ �˾Ƽ� ��ȯ�� �Լ��� �ֽ���
	void Render(D3DXVECTOR3 dest);
	void Render(D3DXVECTOR3 dest, D3DXVECTOR3 sca);

	wstring GetProgressBarKey() { return _keyName; }
};

