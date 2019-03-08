#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addFrameImage("boxFrame", L"image/frameImg/boxFrame.png", 160, 40, 4, 1);
	IMAGEMANAGER->addFrameImage("doorFrame", L"image/frameImg/doorFrame.png", 160, 80, 4, 1);
	IMAGEMANAGER->addFrameImage("lifeCapsule", L"image/frameImg/lifeCapsule.png", 80, 40, 2, 1);
	IMAGEMANAGER->addFrameImage("lifeChargeFrame", L"image/frameImg/lifeChargeFrame.png", 80, 40, 2, 1);

	IMAGEMANAGER->addFrameImage("saveFrame", L"image/frameImg/saveFrame.png", 320, 40, 8, 1);
	IMAGEMANAGER->addFrameImage("lifeChargeFrame", L"image/frameImg/lifeChargeFrame.png", 80, 40, 2, 1);
	IMAGEMANAGER->addFrameImage("boxFrame", L"image/frameImg/boxFrame.png", 160, 40, 4, 1);
	IMAGEMANAGER->addFrameImage("lifeCapsule", L"image/frameImg/lifeCapsule.png", 80, 40, 2, 1);

	SCENEMANAGER->addScene("mapToolScene", new mapToolScene);
	SCENEMANAGER->addScene("townScene", new townScene);
	SCENEMANAGER->addScene("playerTestScene", new playerTestScene);

	SCENEMANAGER->changeScene("mapToolScene");
	

	_count = 0;

	_cursor1 = LoadCursorFromFile("cute1.cur");
	_cursor2 = LoadCursorFromFile("cute2.cur");
	
	if (MAPTOOLSCENE)
	{
		SCENEMANAGER->changeScene("mapToolScene");
	}
	else
	{
		SCENEMANAGER->changeScene("townScene");
	}

	

	
	

	
	return S_OK;
}

void playGround::release()
{
	gameNode::release();
	
}

void playGround::update()
{
	gameNode::update();
	
	SCENEMANAGER->update();
	cursor();
}

void playGround::render()
{
	// Draw ���� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->beginDraw();
	//===========================================================================
	//				##		���⿡ �ڵ� �ۼ�(Start)			##



	SCENEMANAGER->render();
	//wstring temp;
	//temp = L"���������!!!!�տ�";
	//D2DMANAGER->drawText(temp.c_str(), 0, 0, 20, RGB(0,0,255));

	


	//				##			���⿡ �ڵ� �ۼ�(End)			##
	//===========================================================================
	//				##ī�޶� ���� ���콺 ���� �ð����� ���	##===================
	
	WCHAR str[128];
	swprintf_s(str, L"ī�޶�X : %d", CAMERA->getPosX());
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 80);
	swprintf_s(str, L"cameraY : %d", CAMERA->getPosY());
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 100);
	swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 140);
	swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 160);
	TIMEMANAGER->render();
	// Draw �� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->endDraw();
}

void playGround::cursor()
{
	
	++_count;
	if (_count % 16 < 8)
	{
		SetCursor(_cursor1);
	}
	else if (_count % 16 >= 8)
	{
		SetCursor(_cursor2);
	}
}
