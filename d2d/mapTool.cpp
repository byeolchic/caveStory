#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	//���� �Խ� ��׶���
	IMAGEMANAGER->addImage("maptoolBackground", L"image/tile/mapToolBackground2.png", 1250, 840);

	//����, ���� ��ư
	IMAGEMANAGER->addFrameImage("nextButton", L"image/buttonImg/nextButton.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("preButton", L"image/buttonImg/preButton.png", 60, 120, 1, 2);

	_sampleNextPageButton = new button;
	_sampleNextPageButton->init("nextButton", WINSIZEX - 50, 490, PointMake(0, 1), PointMake(0, 0), cbChangeNextSample);
	_samplePrePageButton = new button;
	_samplePrePageButton->init("preButton", WINSIZEX - 150, 490, PointMake(0, 1), PointMake(0, 0), cbChangePreSample);

	//������Ʈ ��ư
	IMAGEMANAGER->addFrameImage("objectButton", L"image/buttonImg/objectButton.png", 100, 120, 1, 2);
	_selectObj = std::move(bind(&mapTool::selectObj, this));
	_objButton = new button;
	_objButton->init("objectButton", WINSIZEX - 280, 490, PointMake(0, 1), PointMake(0, 0), _selectObj);


	//�� x��, y�� ��ư
	IMAGEMANAGER->addFrameImage("X��", L"image/buttonImg/X��.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("Y��", L"image/buttonImg/Y��.png", 60, 120, 1, 2);
	_selectXButton = new button;
	_selectXButton->init("X��", WINSIZEX - 200, 550, PointMake(0, 1), PointMake(0, 0), cbSelectX);
	_selectYbutton = new button;
	_selectYbutton->init("Y��", WINSIZEX - 100, 550, PointMake(0, 1), PointMake(0, 0), cbSelectY);

	//�� ������ ���� ��ư
	IMAGEMANAGER->addFrameImage("+1Button", L"image/buttonImg/+1Button.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("-1Button", L"image/buttonImg/-1Button.png", 60, 120, 1, 2);

	_increaseMap = std::move(bind(&mapTool::increaseMap, this));
	_decreaseMap = std::move(bind(&mapTool::decreaseMap, this));

	_increaseButton = new button;
	_increaseButton->init("+1Button", WINSIZEX - 150, 600, PointMake(0, 1), PointMake(0, 0), _decreaseMap);
	_decreaseButton = new button;
	_decreaseButton->init("-1Button", WINSIZEX - 150, 665, PointMake(0, 1), PointMake(0, 0), _increaseMap);

	//���� �̹���
	_sampleImg[0] = nullptr;
	_sampleImg[1] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_01], L"image/tile/tile_01.png", 240, 400, 6, 10);
	_sampleImg[2] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_02], L"image/tile/tile_02.png", 240, 400, 6, 10);
	_sampleImg[3] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_03], L"image/tile/tile_03.png", 240, 400, 6, 10);
	_sampleImg[4] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_04], L"image/tile/tile_04.png", 240, 400, 6, 10);
	_sampleImg[5] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_05], L"image/tile/tile_05.png", 240, 400, 6, 10);
	_sampleImg[6] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_06], L"image/tile/tile_06.png", 240, 400, 6, 10);
	_sampleImg[7] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_07], L"image/tile/tile_07.png", 240, 400, 6, 10);
	_sampleImg[8] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_08], L"image/tile/tile_08.png", 240, 400, 6, 10);
	_sampleImg[9] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_09], L"image/tile/tile_09.png", 240, 400, 6, 10);


	_samplePage = 1;
	CAMERA->init(0, 0, 5000, 5000);

	mapToolSetting();			//������ �⺻ Ÿ�ϵ��������� setting��

	TILEX = _reSizeX = MAP_WIDTH_NUM;
	TILEY = _reSizeY = MAP_HEIGHT_NUM;

	_isClick = false;

	//������ ����
	_pickSample.indX = 0;
	_pickSample.indY = 0;
	_pickSample.tileImgPage = 0;

	//����������
	_loopRect = { 0, 0, 1120, 840 };
	_loopX = 0.f;

	//�ʻ����� �������� X�� ������ �����߳�? �Ұ� �ʱ�ȭ
	_isSelectX = _isSelectY = false;
	_boolCountX = _boolCountY = 0;

	//Ÿ���� ���� ����Ҷ� �ʿ��� ������
	_pt.x = 0.f;
	_pt.y = 0.f;
	_getAngleF = 0.f;
	_calculateNum = 0;

	//Ÿ���� �巡�׷� ���� �����Ͽ� �׸� �� ����� ����
	_isShift = false;
	//��׶��� Ÿ���� ������?
	_isBackground = false;
	//������Ʈ ��ư�� ������?
	_isClickObj = false;
	_objSelectCount = 0;

	_pickSampleStartPointX = _pickSampleStartPointY = 0;
	_pickSampleEndPointX = _pickSampleEndPointY = 1;


	//�� ������ �� ���� ������
	//todo : ���߿� �����ϴ� ��ư, mapt Ÿ���� �����ϴ� ��ư�� ����� ���� �� �̹����� �ٲܰ�.
	_mapType = 0;

	IMAGEMANAGER->addFrameImage("map1", L"image/buttonImg/X��.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("map2", L"image/buttonImg/Y��.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("map3", L"image/buttonImg/X��.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("map4", L"image/buttonImg/Y��.png", 60, 120, 1, 2);

	//�����ư
	IMAGEMANAGER->addFrameImage("saveButton", L"image/buttonImg/Y��.png", 60, 120, 1, 2);

	_map1 = std::move(bind(&mapTool::map1, this));
	_map2 = std::move(bind(&mapTool::map2, this));
	_map3 = std::move(bind(&mapTool::map3, this));
	_map4 = std::move(bind(&mapTool::map4, this));
	//���� ����� �Լ����� ��
	_save = std::move(bind(&mapTool::save, this));

	_mapOne = new button;
	_mapOne->init("map1", 50, 770, PointMake(0, 1), PointMake(0, 0), _map1);
	_mapTwo = new button;
	_mapTwo->init("map2", 100, 770, PointMake(0, 1), PointMake(0, 0), _map2);
	_mapThree = new button;
	_mapThree->init("map3", 150, 770, PointMake(0, 1), PointMake(0, 0), _map3);
	_mapFour = new button;
	_mapFour->init("map4", 200, 770, PointMake(0, 1), PointMake(0, 0), _map4);

	//���� ��ư( �� ��ư�� ������ �ش� ���̽��� ������ ������ ��)
	_saveButton = new button;
	_saveButton->init("saveButton", 400, 770, PointMake(0, 1), PointMake(0, 0), _save);

	return S_OK;
}

void mapTool::update()
{
	_loopRect = { (float)CAMERA->getPosX(), (float)CAMERA->getPosY(), (float)CAMERA->getPosX() + 1120, (float)CAMERA->getPosY() + 840 };

	_loopX += 0.5f;
	CAMERA->mapToolMove();
	_sampleNextPageButton->update(WINSIZEX - 50, 490);
	_samplePrePageButton->update(WINSIZEX - 150, 490);
	_selectXButton->update(WINSIZEX - 200, 550);
	_selectYbutton->update(WINSIZEX - 100, 550);
	_increaseButton->update(WINSIZEX - 150, 600);
	_decreaseButton->update(WINSIZEX - 150, 665);
	_objButton->update(WINSIZEX - 250, 490);

	_mapOne->update(50, 770);
	_mapTwo->update(100, 770);
	_mapThree->update(150, 770);
	_mapFour->update(200, 770);
	_saveButton->update(400, 770);


	//���� ����ϴ� �Լ�
	calculateAngle();
	pickSample();
	drawMap();

	//_reSizeX = TILEX;
	//_reSizeY = TILEY;
}

void mapTool::release()
{

}

void mapTool::render()
{
	//��׶��� loopRender
	IMAGEMANAGER->loopRender("maptoolBackground", _loopRect, _loopX, 0);

	//���� �ѱ�� ��ư ���
	_sampleNextPageButton->render();
	_samplePrePageButton->render();
	//x��, y�� ���� ��ư ���
	_selectXButton->render();
	_selectYbutton->render();
	//Ÿ�� ������ �����ϴ� ��ư ���
	_increaseButton->render();
	_decreaseButton->render();
	//������Ʈ ��ư
	_objButton->render();
	//�� Ÿ�Ժ��� �����ϴ� ��ư ���
	_mapOne->render();
	_mapTwo->render();
	_mapThree->render();
	_mapFour->render();
	//�����ư
	_saveButton->render();

	//���� Ŭ���Ѱ��� sample Ÿ���� �׸��ºκ�
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			//X�� ī�޶� ������ ����� continue
			if (40 + (j * TILE_SIZE) - CAMERA->getPosX() < 40)
				continue;
			if (40 + ((j + 1) * TILE_SIZE) - CAMERA->getPosX() > CAMERA_SHOW_RANGE_W)
				continue;
			//Y�� ī�޶� ������ ����� continue
			if (40 + (i * TILE_SIZE) - CAMERA->getPosY() < 40)
				continue;
			if (40 + ((i + 1) * TILE_SIZE) - CAMERA->getPosY() > CAMERA_SHOW_RANGE_H)
				continue;
			//����� Ÿ�� ���
			if(_vvTile[i][j]->isBackground)
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->backgroundIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																									 , _vvTile[i][j]->backgroundX
																									 , _vvTile[i][j]->backgroundY);
			//�Ϲ�Ÿ�� ���
			IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->tileImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																							  , _vvTile[i][j]->terrainFrameX
																							  , _vvTile[i][j]->terrainFrameY);
			//������Ʈ ���
			if (_vvTile[i][j]->isObj)
			{
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->tileImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																								  , _vvTile[i][j]->terrainFrameX
																								  , _vvTile[i][j]->terrainFrameY);


				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->objImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																								 , _vvTile[i][j]->objectFrameX
																								 , _vvTile[i][j]->objectFrameY);
			}
			//��Ʈ���� ���
		}
	}

	//�� �׸��� ���� ��Ʈ�� �׸�
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//X�� ī�޶� ������ ����� continue
			if (40 + (j * TILE_SIZE) - CAMERA->getPosX() < 0)
				continue;
			if (40 + ((j + 1) * TILE_SIZE) - CAMERA->getPosX() > CAMERA_SHOW_RANGE_W)
				continue;
			//Y�� ī�޶� ������ ����� continue
			if (40 + (i * TILE_SIZE) - CAMERA->getPosY() < 0)
				continue;
			if (40 + ((i + 1) * TILE_SIZE) - CAMERA->getPosY() > CAMERA_SHOW_RANGE_H)
				continue;

			D2DMANAGER->drawRectangle(40 + j * TILE_SIZE, 40 + (i * TILE_SIZE),
									  40 + (j + 1) * TILE_SIZE, 40 + ((i + 1) * TILE_SIZE));
		}
	}

	//���� Ÿ�� �̹��� ���
	IMAGEMANAGER->findImage(SAMPLETILENAME[_samplePage])->render(CAMERA->getPosX() + WINSIZEX - 280, CAMERA->getPosY() + SAMPLE_DISTANCE_Y);

	//������ rect ���
	for (int i = 0; i < SAMPLE_HEIGHT_NUM; ++i)
	{
		for (int j = 0; j < SAMPLE_WIDTH_NUM; j++)
		{
			D2DMANAGER->drawRectangle(CAMERA->getPosX() + (WINSIZEX - 280) + (j * TILE_SIZE), CAMERA->getPosY() + SAMPLE_DISTANCE_Y + (i * TILE_SIZE),
									  CAMERA->getPosX() + (WINSIZEX - 280) + ((j + 1) * TILE_SIZE), CAMERA->getPosY() + SAMPLE_DISTANCE_Y + ((i + 1) * TILE_SIZE));
		}
	}
	
	if (_isClick)
	{
		IMAGEMANAGER->findImage(SAMPLETILENAME[_pickSample.tileImgPage])->frameRender(_ptMouse.x + 20, _ptMouse.y + 20, _pickSample.indX, _pickSample.indY, 0.5f);
	}
	WCHAR str[128];
	swprintf_s(str, L"mapType : %d", _mapType);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 500, 25);
	swprintf_s(str, L"select X�� : %d", _isSelectX);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 520);
	swprintf_s(str, L"select Y�� : %d", _isSelectY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 540);

	swprintf_s(str, L"TILEX : %d", TILEX);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 560, 30);
	swprintf_s(str, L"TILEY : %d", TILEY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 590, 30);

	swprintf_s(str, L"resizeX : %d", _reSizeX);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 620, 30);
	swprintf_s(str, L"resizeY : %d", _reSizeY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 650, 30);

	swprintf_s(str, L"������Ʈ��: %d", _isClickObj);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 680, 30);

	swprintf_s(str, L"saveStartPtX: %d", _pickSampleStartPointX);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 600, 25);
	swprintf_s(str, L"saveStartPtY: %d", _pickSampleStartPointY);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 630, 25);
	swprintf_s(str, L"saveEndPtX: %d", _pickSampleEndPointX);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 660, 25);
	swprintf_s(str, L"saveEndPtY: %d", _pickSampleEndPointY);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 690, 25);

	swprintf_s(str, L"isClick: %d", _isClick);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 720, 25);



}


//���� �ȵ�
//todo
void mapTool::calculateAngle()
{
	if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_calculateNum % 2 == 0)
			{
				_pt.x = _ptMouse.x;
				_pt.y = _ptMouse.y;
			}
			if (_calculateNum % 2 == 1)
			{

				_getAngleF = getAngle(_pt.x, _pt.y, _ptMouse.x, _ptMouse.y) * (180 / PI);
			}
			++_calculateNum;
		}
	}
}

//����Ÿ�� ���� �������� �ѱ�� �ݹ��Լ�
void mapTool::cbChangeNextSample()
{
	_samplePage++;
	if (_samplePage >= SAMPLE_TILE_IMAGEKEY_COUNT)
	{
		_samplePage = 1;
	}
	_isClick = false;
	_isBackground = false;
}
//����Ÿ�� ���� �������� �ѱ�� �ݹ��Լ�
void mapTool::cbChangePreSample()
{
	_samplePage--;
	if (_samplePage < 1)
	{
		_samplePage = SAMPLE_TILE_IMAGEKEY_COUNT - 1;
	}
	_isClick = false;
	_isBackground = false;

}

//X�� ����
void mapTool::cbSelectX()
{
	++_boolCountX;
	if (_boolCountX % 2 == 1)
	{
		_isSelectX = true;
	}
	else if (_boolCountX % 2 == 0)
	{
		_isSelectX = false;
	}
}
//Y�� ����
void mapTool::cbSelectY()
{
	++_boolCountY;
	if (_boolCountY % 2 == 1)
	{
		_isSelectY = true;
	}
	else if (_boolCountY % 2 == 0)
	{
		_isSelectY = false;
	}
}

void mapTool::map1()
{
	_mapType = MAP_TYPE_ONE;
	//��������� ����ִ°� ��������
	//����Ȱ� ������ ����Ȱ� ��������
	//load();		//�Ű������� ���� Ÿ�� ���� �޾ƿñ�..
}

void mapTool::map2()
{
	_mapType = MAP_TYPE_TWO;
}

void mapTool::map3()
{
	_mapType = MAP_TYPE_THREE;
}

void mapTool::map4()
{
	_mapType = MAP_TYPE_FOUR;
}

//ó���� ������ ���� �� Ÿ�� �ʱ�ȭ
void mapTool::mapToolSetting()
{
	for (int i = 0; i < MAP_HEIGHT_NUM; ++i)
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < MAP_WIDTH_NUM; ++j)
		{
			tagTile* tile = new tagTile;
			tile->backgroundIndex = 7;
			tile->backgroundX = NULL;
			tile->backgroundY = NULL;

			tile->tileImgIndex = 1;
			tile->terrainFrameX = NULL;
			tile->terrainFrameY = NULL;
			
			tile->objImgIndex = 1;
			tile->objectFrameX = NULL;
			tile->objectFrameY = NULL;

			tile->zOrderFrameX = NULL;
			tile->zOrderFrameY = NULL;
			tile->attr = TS_NONE;
			tile->isBackground = false;
			tile->isObj = false;
			tile->isZorder = false;

			vTile.push_back(tile);
		}
		_vvTile.push_back(vTile);
	}
}

//���� �����ϴ� �Լ�
void mapTool::pickSample()
{
	if (_ptMouse.x - CAMERA->getPosX() < SAMPLE_START_POSX)
		return;
	if (_ptMouse.y - CAMERA->getPosY() < SAMPLE_DISTANCE_Y)
		return;
	if (_ptMouse.x - CAMERA->getPosX() > SAMPLE_START_POSX + (SAMPLE_WIDTH_NUM * TILE_SIZE))
		return;
	if (_ptMouse.y - CAMERA->getPosY() > SAMPLE_DISTANCE_Y + (SAMPLE_HEIGHT_NUM * TILE_SIZE))
		return;

	int frameX = (_ptMouse.x - CAMERA->getPosX() - SAMPLE_START_POSX) / TILE_SIZE;
	int frameY = (_ptMouse.y - CAMERA->getPosY() - SAMPLE_DISTANCE_Y) / TILE_SIZE;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_isClick = true;
		_pickSampleStartPointX = frameX;
		_pickSampleStartPointY = frameY;
		switch (_samplePage)
		{
		case 1:
			//�ٴ�
			if ((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM) && ((frameY >= 0 && frameY < 4) || (frameY >= 6 && frameY < SAMPLE_HEIGHT_NUM)) ||
				(frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 1) && (frameY == 4 || frameY == 5))
			{
				// Ŭ���Ͽ� ������ ������ �����ϴ� ������ �־���
				_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_01;
				_pickSample.indX = frameX;
				_pickSample.indY = frameY;
				_pickSampleStartPointX = frameX;
				_pickSampleStartPointY = frameY;
				break;

		case 2:case 3:case 4:
			if ((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM) && (frameY >= 0 && frameY < SAMPLE_HEIGHT_NUM))
			{
				if (_samplePage == 2)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_02;
				else if (_samplePage == 3)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_03;
				else if (_samplePage == 4)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_04;

				_pickSample.indX = frameX;
				_pickSample.indY = frameY;
				_pickSampleStartPointX = frameX;
				_pickSampleStartPointY = frameY;
			}
			break;

		case 5:
			if ((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 1) && (frameY == 0 || frameY == 4 || frameY == 5) ||
				((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM) && ((frameY >= 1 && frameY < 4) || (frameY >= 6 && frameY < SAMPLE_HEIGHT_NUM))))
			{
				_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_05;

				_pickSample.indX = frameX;
				_pickSample.indY = frameY;
				_pickSampleStartPointX = frameX;
				_pickSampleStartPointY = frameY;
			}
			break;

		case 6:
			if ((frameX >= 0 && frameX < 4) && (frameY >= 0 && frameY < 3) ||
				(frameX >= 0 && frameX < 3) && (frameY == 3 || frameY == 4))
			{
				_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_06;

				_pickSample.indX = frameX;
				_pickSample.indY = frameY;
			
			}
			break;

		case 7: case 8: case 9:
			//���Ÿ��
			if ((frameX >= 0 && frameX < 5) && (frameY >= 0 && frameY < 5))
			{
				_isBackground = true;
				if (_samplePage == 7)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_07;
				if (_samplePage == 8)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_08;
				if (_samplePage == 9)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_09;

				_pickSample.indX = frameX;
				_pickSample.indY = frameY;
				
				_isBackground = true;
			}

		default:
			break;
			}
			//_isClick = true;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_pickSampleEndPointX = frameX + 1;
		if (_pickSampleEndPointX <= _pickSampleStartPointX) _pickSampleEndPointX + 1;
		_pickSampleEndPointY = frameY + 1;
		if (_pickSampleEndPointY <= _pickSampleStartPointY) _pickSampleEndPointY + 1;
	}
	//if ((_pickSampleEndPointX - _pickSampleStartPointX > 1) || (_pickSampleEndPointY - _pickSampleStartPointY > 1))
	//	_isDrag = true;
	//else _isDrag = false;

}
//�� �׸��� �Լ�
void mapTool::drawMap()
{
	if (_ptMouse.x - CAMERA->getPosX() > SAMPLE_START_POSX) return;
	if (_ptMouse.x > (TILEX + 1) * TILE_SIZE) return;
	if (_ptMouse.y > (TILEY + 1) * TILE_SIZE) return;
	if (_ptMouse.x - CAMERA->getPosX() < 40) return;
	if (_ptMouse.y - CAMERA->getPosY() < 40) return;

	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
		_isShift = true;
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT))
		_isShift = false;

	//�巡�׷� �׸���
	//���� ����
	if (_isShift)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < TILEY; ++i)
			{
				for (int j = 0; j < TILEX; ++j)
				{
					//if()
				}

			}

		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{


		}
	}
	//Ÿ�� ���� �׸���
	else
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (_isClickObj)
			{
				for (int i = 0; i < TILEY; ++i)
				{
					for (int j = 0; j < TILEX; ++j)
					{
						if (_ptMouse.x > (j + 1) * TILE_SIZE && _ptMouse.x < (j + 2) * TILE_SIZE
							&& _ptMouse.y >(i + 1) * TILE_SIZE && _ptMouse.y < (i + 2) * TILE_SIZE)
						{
							int drawAreaX = 0;
							int drawAreaY = 0;
							for (int ii = _pickSampleStartPointY; ii < _pickSampleEndPointY; ii++, drawAreaY++)
							{
								for (int jj = _pickSampleStartPointX; jj < _pickSampleEndPointX; jj++, drawAreaX++)
								{
									_vvTile[i + drawAreaY][j + drawAreaX]->objImgIndex = _pickSample.tileImgPage;
									_vvTile[i + drawAreaY][j + drawAreaX]->objectFrameX = _pickSample.indX + drawAreaX;
									_vvTile[i + drawAreaY][j + drawAreaX]->objectFrameY = _pickSample.indY + drawAreaY;
									_vvTile[i + drawAreaY][j + drawAreaX]->isObj = true;
								}
								drawAreaX = 0;
							}
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < TILEY; ++i)
				{
					for (int j = 0; j < TILEX; ++j)
					{
						if (_ptMouse.x > (j + 1) * TILE_SIZE && _ptMouse.x < (j + 2) * TILE_SIZE
							&& _ptMouse.y >(i + 1) * TILE_SIZE && _ptMouse.y < (i + 2) * TILE_SIZE)
						{
							int drawAreaX = 0;
							int drawAreaY = 0;
							for (int ii = _pickSampleStartPointY; ii < _pickSampleEndPointY; ii++, drawAreaY++)
							{
								for (int jj = _pickSampleStartPointX; jj < _pickSampleEndPointX; jj++, drawAreaX++)
								{
									_vvTile[i + drawAreaY][j + drawAreaX]->tileImgIndex = _pickSample.tileImgPage;
									_vvTile[i + drawAreaY][j + drawAreaX]->terrainFrameX = _pickSample.indX + drawAreaX;
									_vvTile[i + drawAreaY][j + drawAreaX]->terrainFrameY = _pickSample.indY + drawAreaY;
								}
								drawAreaX = 0;
							}
						}
					}
				}
			}
			if (_isBackground)
			{
				for (int i = 0; i < TILEY; ++i)
				{
					for (int j = 0; j < TILEX; ++j)
					{
						if (_ptMouse.x > (j + 1) * TILE_SIZE && _ptMouse.x < (j + 2) * TILE_SIZE
							&& _ptMouse.y >(i + 1) * TILE_SIZE && _ptMouse.y < (i + 2) * TILE_SIZE)
						{
							int drawAreaX = 0;
							int drawAreaY = 0;
							for (int ii = _pickSampleStartPointY; ii < _pickSampleEndPointY; ii++, drawAreaY++)
							{
								for (int jj = _pickSampleStartPointX; jj < _pickSampleEndPointX; jj++, drawAreaX++)
								{
									_vvTile[i + drawAreaY][j + drawAreaX]->backgroundIndex = _pickSample.tileImgPage;
									_vvTile[i + drawAreaY][j + drawAreaX]->backgroundX = _pickSample.indX + drawAreaX;
									_vvTile[i + drawAreaY][j + drawAreaX]->backgroundY = _pickSample.indY + drawAreaY;
									_vvTile[i + drawAreaY][j + drawAreaX]->isBackground = true;
								}
								drawAreaX = 0;
							}
						}
					}
				}
			}
			//�Ϲ� Ÿ��
			//for (int i = 0; i < TILEY; ++i)
			//{
			//	for (int j = 0; j < TILEX; ++j)
			//	{
			//		if (_ptMouse.x > (j + 1) * TILE_SIZE && _ptMouse.x < (j + 2) * TILE_SIZE
			//			&& _ptMouse.y >(i + 1) * TILE_SIZE && _ptMouse.y < (i + 2) * TILE_SIZE)
			//		{
			//			int drawAreaX = 0;
			//			int drawAreaY = 0;
			//			for (int ii = _pickSampleStartPointY; ii < _pickSampleEndPointY; ii++, drawAreaY++)
			//			{
			//				for (int jj = _pickSampleStartPointX; jj < _pickSampleEndPointX; jj++, drawAreaX++)
			//				{
			//					_vvTile[i + drawAreaY][j + drawAreaX]->tileImgIndex = _pickSample.tileImgPage;
			//					_vvTile[i + drawAreaY][j + drawAreaX]->terrainFrameX = _pickSample.indX + drawAreaX;
			//					_vvTile[i + drawAreaY][j + drawAreaX]->terrainFrameY = _pickSample.indY + drawAreaY;
			//				}
			//				drawAreaX = 0;
			//					
			//			}
			//		}
			//	}
			//}
		}
		
	}

}

void mapTool::save()
{



}

void mapTool::load()
{
}

//�Ӽ� �����ϴ� �Լ�
void mapTool::setAttribute(UINT samplePage, UINT frameX, UINT frameY)
{
	DWORD storeAttr;
	switch (_samplePage)
	{
	case 0:
		//�ٴ�
		if ((frameX == 1 && frameY == 0) ||
			((frameX >= 2 && frameX < SAMPLE_WIDTH_NUM) && frameY == 1) ||
			(frameX == 0 || frameX == 1) && (frameY == 2 || frameY == 3) ||
			(frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 2) && frameY == 4 ||
			(frameX == 3 || frameX == 4) && frameY == 6)
		{

		}

		//���

		//õ��
		//if ((frameX >= 2 && frameX < SAMPLE_WIDTH_NUM) && frameY == 0) ||
		//	(frameX) && () || )


		//��
		//��
		//��Ʈ����

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;

	default:
		break;
	}

}

//X�� ����
void mapTool::increaseX()
{
	for (int i = 0; i < TILEY; ++i)
	{
		//Ÿ��Ÿ���̶�� ���ο� ������ _vvTile[i]�� back()�� ����
		tagTile* targetTile = _vvTile[i].back();
		_vvTile[i].pop_back();

		SAFE_DELETE(targetTile);
	}
	TILEX--;
}
//Y�� ����
void mapTool::increaseY()
{
	for (int i = TILEX - 1; i >= 0; --i)
	{
		//������ ����
		delete _vvTile.back()[i];
		//������ �ּ� ����
		_vvTile.back()[i] = nullptr;
	}
	_vvTile.pop_back();
	TILEY--;
}
//X�� ����
void mapTool::decreaseX()
{
	for (int i = 0; i < TILEY; ++i)
	{
		tagTile* newTile = new tagTile;

		newTile->backgroundIndex = 7;
		newTile->backgroundX = NULL;
		newTile->backgroundY = NULL;

		newTile->tileImgIndex = 1;
		newTile->terrainFrameX = NULL;
		newTile->terrainFrameY = NULL;
		
		newTile->objImgIndex = 1;
		newTile->objectFrameX = NULL;
		newTile->objectFrameY = NULL;

		newTile->zOrderFrameX = NULL;
		newTile->zOrderFrameY = NULL;
		newTile->attr = TS_NONE;

		newTile->isBackground = false;
		newTile->isObj = false;
		newTile->isZorder = false;
		_vvTile[i].push_back(newTile);
	}
	++TILEX;
}
//Y�� ����
void mapTool::decreaseY()
{
	vector<tagTile*> vTile;
	for (int i = 0; i < TILEX; ++i)
	{
		tagTile* newTile = new tagTile;

		newTile->backgroundIndex = 7;
		newTile->backgroundX = NULL;
		newTile->backgroundY = NULL;

		newTile->tileImgIndex = 1;
		newTile->terrainFrameX = NULL;
		newTile->terrainFrameY = NULL;

		newTile->objImgIndex = 1;
		newTile->objectFrameX = NULL;
		newTile->objectFrameY = NULL;

		newTile->zOrderFrameX = NULL;
		newTile->zOrderFrameY = NULL;
		newTile->attr = TS_NONE;
		
		newTile->isBackground = false;
		newTile->isObj = false;
		newTile->isZorder = false;

		vTile.push_back(newTile);
	}
	_vvTile.push_back(vTile);
	++TILEY;
}

//�� ���� map Size�� �������� �� �ҷ��� �Լ�
void mapTool::increaseMap()
{
	//X�� ���ý�
	if (_isSelectX && TILEX > 2)
	{
		increaseX();
	}
	//Y�� ���ý�
	if (_isSelectY && TILEY > 2)
	{
		increaseY();
	}
}

//�� ���� map Size�� �������� �� �ҷ��� �Լ�
void mapTool::decreaseMap()
{
	//X�� ���ý�
	if (_isSelectX)
	{
		decreaseX();
	}
	//Y�� ���ý�
	if (_isSelectY)
	{
		decreaseY();
	}
}

//������Ʈ ��ư�� ������ �� �ݹ� �Լ��� ���Կ��� �� �Լ�
void mapTool::selectObj()
{
	if (_objSelectCount % 2 == 0)
		_isClickObj = true;
	else if (_objSelectCount % 2 == 1)
		_isClickObj = false;
	_objSelectCount++;
}

