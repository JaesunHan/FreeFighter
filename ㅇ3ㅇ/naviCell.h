#pragma once
class naviCell
{
private:
	D3DXVECTOR3				_triCenter;			//�ﰢ�� ����
	vector<D3DXVECTOR3>		_vertex;			//���ؽ�����
	vector<D3DXVECTOR3>		_verMid;			//���ؽ� ������ ����
	vector<D3DXVECTOR3>		_triVerMidInterval;	//���ؽ� ������ ������ �ﰢ�� ���������� �Ÿ�
	vector<naviCell*>		_link;				//�̿��� �ﰢ��

	string					_attribute;			//�Ӽ� , �������� ���� �����

public:
	naviCell();
	~naviCell();

	void Init(IN D3DXVECTOR3 v0, IN D3DXVECTOR3 v1, IN D3DXVECTOR3 v2);

	D3DXVECTOR3			GetTriCenter() { return _triCenter; }
	vector<D3DXVECTOR3> GetVertex() { return _vertex; }
	vector<D3DXVECTOR3> GetVerMid() { return _verMid; }
	vector<D3DXVECTOR3> GetTriVerMidInterval() { return _triVerMidInterval; }

	void SetLink(naviCell* nc) { _link.push_back(nc); }
};

