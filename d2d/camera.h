#pragma once
#include "singletonBase.h"
#define CAMERA_SPEED				5.f
#define CAMERA_MAPTOOL_SHOW_WIDTH	800
#define CAMERA_MAPTOOL_SHOW_HEIGHT	640


class camera : public singletonBase<camera>
{
private:

	float _posX;
	float _posY;
	float _maxX;
	float _maxY;


public:
	camera();
	~camera();

	HRESULT init();
	HRESULT init(float x, float y, float maxX, float maxY);

	void release();
	void update();
	void move(float	x, float y);
	void mapToolMove();

	float getPosX() { return _posX; }
	float getPosY() { return _posY; }



};

