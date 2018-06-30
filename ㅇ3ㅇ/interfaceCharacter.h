#pragma once

class skinnedMesh;

struct tagCharState
{

};

class interfaceCharacter
{
private:
	skinnedMesh* _skinnedMesh;

private:
	tagCharState _state;

public:
	interfaceCharacter();
	~interfaceCharacter();

	virtual void Setup(wstring keyPath, wstring keyName);
	virtual void Update() = 0;
	virtual void Render() = 0;

};

