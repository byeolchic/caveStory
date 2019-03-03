#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, function<void(void)> cbFunction)
{
	_callbackFunction = cbFunction;

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = { (LONG)(2 * CAMERA->getPosX()) + x - _image->GetFrameWidth() / 2 , (LONG)(2 * CAMERA->getPosY()) + y - _image->GetFrameHeight() / 2
		,(LONG)(2 * CAMERA->getPosX()) + x + _image->GetFrameWidth() / 2 , (LONG)(2 * CAMERA->getPosX()) + y + _image->GetFrameHeight() / 2 };

	boolCount = 0;

	return S_OK;
}





void button::release()
{
}

void button::update(float x, float y)
{
	POINT p;
	p.x = _ptMouse.x;
	p.y = _ptMouse.y;
	if (PtInRect(&_rc, p))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;

	//todo
	_rc = { (LONG)(CAMERA->getPosX() + x - _image->GetFrameWidth() / 2) , (LONG)(CAMERA->getPosY() + y - _image->GetFrameHeight() / 2)
		 , (LONG)(CAMERA->getPosX() + x + _image->GetFrameWidth() / 2 ), (LONG)(CAMERA->getPosY() + y + _image->GetFrameHeight() / 2) };

}

void button::toggleUpdate()
{
	// 잘 안되넹...나중에 시간 남으면 손보자
	// todo
	POINT p;
	p.x = _ptMouse.x;
	p.y = _ptMouse.y;

	if (boolCount % 2 == 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_rc, p))
			{
				_direction = BUTTONDIRECTION_DOWN;
				++boolCount;
			}
		}
	}
	else if(boolCount % 2 == 1)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_rc, p))
			{
				_direction = BUTTONDIRECTION_UP;
				++boolCount;

			}
			//else _direction = BUTTONDIRECTION_NULL;

		}
		_callbackFunction();
	}
	//if (!PtInRect(&_rc, p))
	//{
	//	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//		_direction = BUTTONDIRECTION_NULL;
	//}

}

void button::render()
{
	switch (_direction)
	{
	case BUTTONDIRECTION_NULL:	case BUTTONDIRECTION_UP:
		_image->frameRender(_rc.left , _rc.top ,
			_btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
	case BUTTONDIRECTION_DOWN:
		_image->frameRender(_rc.left, _rc.top,
			_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;

	}
}
