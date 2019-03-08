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
	// Draw 시작 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->beginDraw();
	//===========================================================================
	//				##		여기에 코드 작성(Start)			##



	SCENEMANAGER->render();
	//wstring temp;
	//temp = L"우오오오와!!!!왕왕";
	//D2DMANAGER->drawText(temp.c_str(), 0, 0, 20, RGB(0,0,255));

	


	//				##			여기에 코드 작성(End)			##
	//===========================================================================
	//				##카메라 정보 마우스 정보 시간정보 출력	##===================
	
	WCHAR str[128];
	swprintf_s(str, L"카메라X : %d", CAMERA->getPosX());
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 80);
	swprintf_s(str, L"cameraY : %d", CAMERA->getPosY());
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 100);
	swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 140);
	swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 160);
	TIMEMANAGER->render();
	// Draw 끝 - 이 코드가 빠지면 D2D 출력 X
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
