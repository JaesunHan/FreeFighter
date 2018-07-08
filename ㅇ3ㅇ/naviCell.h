#pragma once
class naviCell
{
private:
	D3DXVECTOR3				_triCenter;			//삼각형 중점
	vector<D3DXVECTOR3>		_vertex;			//버텍스정보
	vector<D3DXVECTOR3>		_verMid;			//버텍스 사이의 중점
	vector<D3DXVECTOR3>		_triVerMidInterval;	//버텍스 사이의 중점과 삼각형 중점사이의 거리
	vector<naviCell*>		_link;				//이웃한 삼각형
	bool					_isOpen;			//갈수있는 Cell인가
	string					_attribute;			//속성 , 쓸지말지 아직 고민중

public:
	naviCell();
	~naviCell();

	void Init(IN D3DXVECTOR3 v0, IN D3DXVECTOR3 v1, IN D3DXVECTOR3 v2);

	bool				GetIsOpen() { return _isOpen; }
	void				SetIsOpen(bool b) { _isOpen = b; }
	D3DXVECTOR3			GetTriCenter() { return _triCenter; }
	vector<D3DXVECTOR3> GetVertex() { return _vertex; }
	vector<D3DXVECTOR3> GetVerMid() { return _verMid; }
	vector<D3DXVECTOR3> GetTriVerMidInterval() { return _triVerMidInterval; }
	vector<naviCell*>	GetLink() { return _link; }
	void SetLink(naviCell* nc) { _link.push_back(nc); }
	void SetAttribute(string attr) { _attribute = attr; }
};

