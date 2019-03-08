#include "stdafx.h"
#include "camera.h"


camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init()
{
	_posX = 0;
	_posY = 0;
	_maxX = 0;
	_maxY = 0;
	return S_OK;
}

HRESULT camera::init(float x, float y, float maxX, float maxY)
{
	_posX = x;
	_posY = y;
	_maxX = maxX;
	_maxY = maxY;

	return S_OK;
}


void camera::release()
{
}

void camera::update()
{
	/*if (KEYMANAGER->isStayKeyDown(VK_LEFT)  && _posX > 0)
	{
		_posX -= CAMERA_SPEED;
		if (_posX < 0)
		{
			_posX = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)  && _posX < _maxX)
	{
		_posX += CAMERA_SPEED;
		if (_posX + 800 > _maxX)
		{
			_posX = _maxX - WINSIZEX;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_posY--;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_posY++;
	}*/
}

void camera::move(float x, float y)
{
	_posX = x - WINSIZEX / 2;
	_posY = y - WINSIZEY / 2;
}

void camera::mapToolMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _posX > 0)
	{
		_posX -= CAMERA_SPEED;
		if (_posX < 0)
		{
			_posX = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _posX < _maxX)
	{
		_posX += CAMERA_SPEED;
		if (_posX + CAMERA_MAPTOOL_SHOW_WIDTH > _maxX)
		{
			_posX = _maxX - CAMERA_MAPTOOL_SHOW_WIDTH;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _posY > 0)
	{
		_posY -= CAMERA_SPEED;
		if (_posY < 0)
		{
			_posY = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _posY < _maxY)
	{
		_posY+= CAMERA_SPEED;
		if (_posY + CAMERA_MAPTOOL_SHOW_HEIGHT > _maxY)
		{
			_posY = _maxY - CAMERA_MAPTOOL_SHOW_HEIGHT;
		}
	}
}
