#pragma once

#include <vector>
using namespace std;

class mainSceneCharacter;
class camera;
class grid;

class mainSceneTrailer
{
private:
	float		_currentTime;

	vector<mainSceneCharacter*>		_vCharacters;
	int								_currentChar1;
	int								_currentChar2;
	
	camera*							_camera;
	grid*							_grid;

	PxScene*						_physXScene;
	PxMaterial*						_material;
	PxControllerManager*			_cm;

public:
	mainSceneTrailer();
	~mainSceneTrailer();

	HRESULT init();
	void release();
	void update();
	void render();

	void resetAni();
};

