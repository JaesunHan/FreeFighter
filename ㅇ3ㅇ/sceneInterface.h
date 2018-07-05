#pragma once

typedef class _scene
{
private:

public:
	_scene() {};
	virtual ~_scene() {};

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
} iScene;