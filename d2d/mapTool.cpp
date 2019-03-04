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
	//맵툴 입시 백그라운드
	IMAGEMANAGER->addImage("maptoolBackground", L"image/tile/mapToolBackground2.png", 1250, 840);

	//이전, 다음 버튼
	IMAGEMANAGER->addFrameImage("nextButton", L"image/buttonImg/nextButton.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("preButton", L"image/buttonImg/preButton.png", 60, 120, 1, 2);

	_sampleNextPageButton = new button;
	_sampleNextPageButton->init("nextButton", WINSIZEX - 50, 490, PointMake(0, 1), PointMake(0, 0), cbChangeNextSample);
	_samplePrePageButton = new button;
	_samplePrePageButton->init("preButton", WINSIZEX - 150, 490, PointMake(0, 1), PointMake(0, 0), cbChangePreSample);

	//오브젝트 버튼
	IMAGEMANAGER->addFrameImage("objectButton", L"image/buttonImg/objectButton.png", 100, 120, 1, 2);
	_selectObj = std::move(bind(&mapTool::selectObj, this));
	_objButton = new button;
	_objButton->init("objectButton", WINSIZEX - 280, 490, PointMake(0, 1), PointMake(0, 0), _selectObj);

	//맵 x축, y축 버튼
	IMAGEMANAGER->addFrameImage("X축", L"image/buttonImg/X축.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("Y축", L"image/buttonImg/Y축.png", 60, 120, 1, 2);
	_selectXButton = new button;
	_selectXButton->init("X축", WINSIZEX - 200, 550, PointMake(0, 1), PointMake(0, 0), cbSelectX);
	_selectYbutton = new button;
	_selectYbutton->init("Y축", WINSIZEX - 100, 550, PointMake(0, 1), PointMake(0, 0), cbSelectY);

	//맵 사이즈 증감 버튼
	IMAGEMANAGER->addFrameImage("+1Button", L"image/buttonImg/+1Button.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("-1Button", L"image/buttonImg/-1Button.png", 60, 120, 1, 2);

	_increaseMap = std::move(bind(&mapTool::increaseMap, this));
	_decreaseMap = std::move(bind(&mapTool::decreaseMap, this));

	_increaseButton = new button;
	_increaseButton->init("+1Button", WINSIZEX - 150, 600, PointMake(0, 1), PointMake(0, 0), _decreaseMap);
	_decreaseButton = new button;
	_decreaseButton->init("-1Button", WINSIZEX - 150, 665, PointMake(0, 1), PointMake(0, 0), _increaseMap);

	//샘플 이미지
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

	mapToolSetting();			//맵툴의 기본 타일들의정보를 setting함

	TILEX = _reSizeX = MAP_WIDTH_NUM;
	TILEY = _reSizeY = MAP_HEIGHT_NUM;

	_isClick = false;

	//선택한 샘플
	_pickSample.indX = 0;
	_pickSample.indY = 0;
	_pickSample.tileImgPage = 1;

	//루프렌더용
	_loopRect = { 0, 0, 1120, 840 };
	_loopX = 0.f;

	//맵사이즈 조정에서 X축 증감을 선택했냐? 불값 초기화
	_isSelectX = _isSelectY = false;
	_boolCountX = _boolCountY = 0;

	//타일의 각도 계산할때 필요한 변수들
	_pt.x = 0.f;
	_pt.y = 0.f;
	_getAngleF = 0.f;
	_calculateNum = 0;

	//타일을 드래그로 범위 지정하여 그릴 때 사용할 변수
	_isShift = false;
	//백그라운드 타일을 눌렀냐?
	_isBackground = false;
	//오브젝트 버튼을 눌렀냐?
	_isClickObj = false;
	_objSelectCount = 0;

	_pickSampleStartPointX = _pickSampleStartPointY = 0;
	_pickSampleEndPointX = _pickSampleEndPointY = 1;


	//맵 저장할 때 쓰일 변수들
	//todo : 나중에 저장하는 버튼, mapt 타입을 선택하는 버튼을 만들고 나서 그 이미지로 바꿀것.
	_mapType = 0;

	IMAGEMANAGER->addFrameImage("map1", L"image/buttonImg/X축.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("map2", L"image/buttonImg/Y축.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("map3", L"image/buttonImg/X축.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("map4", L"image/buttonImg/Y축.png", 60, 120, 1, 2);
	//저장버튼
	IMAGEMANAGER->addFrameImage("saveButton", L"image/buttonImg/X축.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("loadButton", L"image/buttonImg/Y축.png", 60, 120, 1, 2);

	_map1 = std::move(bind(&mapTool::map1, this));
	_map2 = std::move(bind(&mapTool::map2, this));
	_map3 = std::move(bind(&mapTool::map3, this));
	_map4 = std::move(bind(&mapTool::map4, this));
	//저장 기능을 함수대입 함
	_save = std::move(bind(&mapTool::save, this));
	//불러오기 기능을 함수대입 함
	_load = std::move(bind(&mapTool::load, this));

	_mapOne = new button;
	_mapOne->init("map1", 50, 750, PointMake(0, 1), PointMake(0, 0), _map1);
	_mapTwo = new button;
	_mapTwo->init("map2", 100, 750, PointMake(0, 1), PointMake(0, 0), _map2);
	_mapThree = new button;
	_mapThree->init("map3", 150, 750, PointMake(0, 1), PointMake(0, 0), _map3);
	_mapFour = new button;
	_mapFour->init("map4", 200, 750, PointMake(0, 1), PointMake(0, 0), _map4);

	//저장 버튼( 이 버튼을 눌러야 해당 케이스에 정보가 저장이 됨)
	_saveButton = new button;
	_saveButton->init("saveButton", 400, 770, PointMake(0, 1), PointMake(0, 0), _save);
	//불러오기 버튼
	_loadButton = new button;
	_loadButton->init("loadButton", 400, 800, PointMake(0, 1), PointMake(0, 0), _load);

	fileNameSet();
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

	_mapOne->update(50, 750);
	_mapTwo->update(100, 750);
	_mapThree->update(150, 750);
	_mapFour->update(200, 750);
	_saveButton->update(400, 750);
	_loadButton->update(400, 800);


	//각도 계산하는 함수
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
	//백그라운드 loopRender
	IMAGEMANAGER->loopRender("maptoolBackground", _loopRect, _loopX, 0);

	//샘플 넘기는 버튼 출력
	_sampleNextPageButton->render();
	_samplePrePageButton->render();
	//x축, y축 선택 버튼 출력
	_selectXButton->render();
	_selectYbutton->render();
	//타일 사이즈 조정하는 버튼 출력
	_increaseButton->render();
	_decreaseButton->render();
	//오브젝트 버튼
	_objButton->render();
	//맵 타입별로 저장하는 버튼 출력
	_mapOne->render();
	_mapTwo->render();
	_mapThree->render();
	_mapFour->render();
	//저장버튼
	_saveButton->render();
	//불러오기버튼
	_loadButton->render();
	//맵을 클릭한곳에 sample 타일을 그리는부분
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			//X축 카메라 범위를 벗어나면 continue
			if (40 + (j * TILE_SIZE) - CAMERA->getPosX() < 40)
				continue;
			if (40 + ((j + 1) * TILE_SIZE) - CAMERA->getPosX() > CAMERA_SHOW_RANGE_W)
				continue;
			//Y축 카메라 범위를 벗어나면 continue
			if (40 + (i * TILE_SIZE) - CAMERA->getPosY() < 40)
				continue;
			if (40 + ((i + 1) * TILE_SIZE) - CAMERA->getPosY() > CAMERA_SHOW_RANGE_H)
				continue;
			//배경인 타일 출력
			if(_vvTile[i][j]->isBackground)
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->backgroundIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																									 , _vvTile[i][j]->backgroundX
																									 , _vvTile[i][j]->backgroundY);
			//일반타일 출력
			IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->tileImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																							  , _vvTile[i][j]->terrainFrameX
																							  , _vvTile[i][j]->terrainFrameY);
			//오브젝트 출력
			if (_vvTile[i][j]->isObj)
			{
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->tileImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																								  , _vvTile[i][j]->terrainFrameX
																								  , _vvTile[i][j]->terrainFrameY);


				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->objImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																								 , _vvTile[i][j]->objectFrameX
																								 , _vvTile[i][j]->objectFrameY);
			}
			//제트오더 출력
		}
	}

	//맵 그리는 쪽의 렉트를 그림
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//X축 카메라 범위를 벗어나면 continue
			if (40 + (j * TILE_SIZE) - CAMERA->getPosX() < 0)
				continue;
			if (40 + ((j + 1) * TILE_SIZE) - CAMERA->getPosX() > CAMERA_SHOW_RANGE_W)
				continue;
			//Y축 카메라 범위를 벗어나면 continue
			if (40 + (i * TILE_SIZE) - CAMERA->getPosY() < 0)
				continue;
			if (40 + ((i + 1) * TILE_SIZE) - CAMERA->getPosY() > CAMERA_SHOW_RANGE_H)
				continue;

			D2DMANAGER->drawRectangle(40 + j * TILE_SIZE, 40 + (i * TILE_SIZE),
									  40 + (j + 1) * TILE_SIZE, 40 + ((i + 1) * TILE_SIZE));
		}
	}

	//샘플 타일 이미지 출력
	IMAGEMANAGER->findImage(SAMPLETILENAME[_samplePage])->render(CAMERA->getPosX() + WINSIZEX - 280, CAMERA->getPosY() + SAMPLE_DISTANCE_Y);

	//샘플쪽 rect 출력
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
	swprintf_s(str, L"select X축 : %d", _isSelectX);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 520);
	swprintf_s(str, L"select Y축 : %d", _isSelectY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 540);

	swprintf_s(str, L"TILEX : %d", TILEX);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 560, 30);
	swprintf_s(str, L"TILEY : %d", TILEY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 590, 30);

	swprintf_s(str, L"경사 타일의 각도: %f", _getAngleF);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 620, 30);
	/*swprintf_s(str, L"resizeY : %d", _reSizeY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 650, 30);*/

	swprintf_s(str, L"오브젝트냐: %d", _isClickObj);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 680, 30);

	/*swprintf_s(str, L"saveStartPtX: %d", _pickSampleStartPointX);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 600, 25);
	swprintf_s(str, L"saveStartPtY: %d", _pickSampleStartPointY);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 630, 25);
	swprintf_s(str, L"saveEndPtX: %d", _pickSampleEndPointX);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 660, 25);
	swprintf_s(str, L"saveEndPtY: %d", _pickSampleEndPointY);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 690, 25);*/

	swprintf_s(str, L"isClick: %d", _isClick);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 130, CAMERA->getPosY() + 720, 25);



}


//아직 안됨
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

//샘플타일 다음 페이지로 넘기는 콜백함수
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
//샘플타일 이전 페이지로 넘기는 콜백함수
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

//X축 선택
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
//Y축 선택
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

	for (int i = TILEY - 1; i >= 0; i--)
	{
		for (int j = TILEX - 1; j >= 0; j--)
		{
			if (_vvTile[i][j])
			{
				SAFE_DELETE(_vvTile[i][j]);
				_vvTile[i].pop_back();
			}
		}
		_vvTile.pop_back();
	}
	for (int i = 0; i < TILEY; ++i)
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < TILEX; ++j)
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

void mapTool::map2()
{
	_mapType = MAP_TYPE_TWO;
	for (int i = TILEY - 1; i >= 0; i--)
	{
		for (int j = TILEX - 1; j >= 0; j--)
		{
			if (_vvTile[i][j])
			{
				SAFE_DELETE(_vvTile[i][j]);
				_vvTile[i].pop_back();
			}
		}
		_vvTile.pop_back();
	}
	for (int i = 0; i < TILEY; ++i)
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < TILEX; ++j)
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

void mapTool::map3()
{
	_mapType = MAP_TYPE_THREE;
	for (int i = TILEY - 1; i >= 0; i--)
	{
		for (int j = TILEX - 1; j >= 0; j--)
		{
			if (_vvTile[i][j])
			{
				SAFE_DELETE(_vvTile[i][j]);
				_vvTile[i].pop_back();
			}
		}
		_vvTile.pop_back();
	}
	for (int i = 0; i < TILEY; ++i)
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < TILEX; ++j)
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

void mapTool::map4()
{
	_mapType = MAP_TYPE_FOUR;
	for (int i = TILEY - 1; i >= 0; i--)
	{
		for (int j = TILEX - 1; j >= 0; j--)
		{
			if (_vvTile[i][j])
			{
				SAFE_DELETE(_vvTile[i][j]);
				_vvTile[i].pop_back();
			}
		}
		_vvTile.pop_back();
	}
	for (int i = 0; i < TILEY; ++i)
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < TILEX; ++j)
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

//처음에 생성한 맵의 빈 타일 초기화
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

//샘플 선택하는 함수
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
			//바닥
			if ((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM) && ((frameY >= 0 && frameY < 4) || (frameY >= 6 && frameY < SAMPLE_HEIGHT_NUM)) ||
				(frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 1) && (frameY == 4 || frameY == 5))
			{
				// 클릭하여 선택한 샘플을 저장하는 변수에 넣어줌
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
			//배경타일
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
//맵 그리는 함수
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

	//드래그로 그리기
	//아직 보류
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
	//타일 각각 그리기
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
			//일반 타일
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
	{
		HANDLE file;
		DWORD write;

		char mapSize[128];
		sprintf_s(mapSize, "%d, %d", TILEX, TILEY);
		file = CreateFile(_mapSizeNames[(MAP_TYPE)_mapType].c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, mapSize, strlen(mapSize), &write, NULL);

		CloseHandle(file);
	
		tagTile* tile = new tagTile[TILEX * TILEY];
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				tile[j + i * TILEX] = *_vvTile[i][j];
			}
		}

		/*
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			tile[j + i * TILEX] = *_vvTile[i][j];

			//마을맵의 포탈 정보 입력
			if (mapCase == 1)		//마을의 포탈
			{
				//필드로 가는 포탈
				_vvTile[8][7]->attr |= ATTR_POTAL;
				_vvTile[9][7]->attr |= ATTR_POTAL;
				_vvTile[10][7]->attr |= ATTR_POTAL;

				//집으로 가는 포탈
				_vvTile[15][23]->attr |= ATTR_POTAL;

				//오박사 실험실 포탈
				_vvTile[16][36]->attr |= ATTR_POTAL;

				//상점으로 이동하는 포탈
				_vvTile[26][38]->attr |= ATTR_POTAL;

				//센터로 이동하는 포탈
				_vvTile[26][33]->attr |= ATTR_POTAL;

				//체육관으로 이동하는 포탈
				_vvTile[26][26]->attr |= ATTR_POTAL;

			}
			//플레이어 집의 포탈 정보 입력
			if (mapCase == 2)
			{
				//마을로 이동하는 포탈
				_vvTile[15][15]->attr |= ATTR_POTAL;
			}
			//오박사 연구소의 포탈정보 입력
			if (mapCase == 3)
			{
				//마을로 이동하는 포탈
				_vvTile[21][16]->attr |= ATTR_POTAL;
			}
			//상점의 포탈정보 입력
			if (mapCase == 4)
			{
				//마을로 이동하는 포탈
				_vvTile[14][14]->attr |= ATTR_POTAL;
			}
			//포켓몬센터의 포탈정보 입력
			if (mapCase == 5)
			{
				//마을로 이동하는 포탈
				_vvTile[15][17]->attr |= ATTR_POTAL;
			}
			//체육관의 포탈정보 입력
			if (mapCase == 6)
			{
				//마을로 이동하는 포탈
				_vvTile[21][16]->attr |= ATTR_POTAL;
			}
			//필드의 포탈정보 입력
			if (mapCase == 7)
			{
				//마을로 이동하는 포탈
				_vvTile[42][47]->attr |= ATTR_POTAL;
				_vvTile[42][48]->attr |= ATTR_POTAL;
				_vvTile[42][49]->attr |= ATTR_POTAL;
				_vvTile[42][50]->attr |= ATTR_POTAL;
				//동굴로 이동하는 포탈
				_vvTile[15][52]->attr |= ATTR_POTAL;
			}
			//동굴의 포탈정보 입력
			if (mapCase == 8)
			{
				//필드로 가는 포탈
				_vvTile[40][31]->attr |= ATTR_POTAL;
			}
		}
	}
	*/
		HANDLE file2;
		DWORD write2;
		file2 = CreateFile(_mapDataNames[(MAP_TYPE)_mapType].c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
		WriteFile(file2, tile, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	
		CloseHandle(file2);
	
		delete[] tile;
	}
}

void mapTool::load()
{
	//if (!sizeFileExists(_mapSizeNames) && !dataFileExists(_mapDataNames))
	//	return;

	for (int i = TILEY - 1; i >= 0; i--)
	{
		for (int j = TILEX - 1; j >= 0; j--)
		{
			if (_vvTile[i][j])
			{
				SAFE_DELETE(_vvTile[i][j]);
				_vvTile[i].pop_back();
			}
		}
		_vvTile.pop_back();
	}

	_vvTile.clear();

	HANDLE file;
	DWORD read;
	char mapSize[128] = { 0, };

	file = CreateFile(_mapSizeNames[(MAP_TYPE)_mapType].c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, mapSize, 128, &read, NULL);
	CloseHandle(file);

	string mapX, mapY;
	mapX.clear();
	mapY.clear();
	bool x = true;
	for (int i = 0; i < strlen(mapSize); ++i)
	{
		if (mapSize[i] == ',')
		{
			x = false;
			continue;
		}
		if (mapSize[i] == NULL)
			break;
		if (x)
		{
			mapX += mapSize[i];
		}
		else
		{
			mapY += mapSize[i];
		}
	}

	TILEX = stoi(mapX);
	TILEY = stoi(mapY);
	_vvTile.resize(TILEY);

	for (int i = 0; i < TILEY; ++i)
	{
		_vvTile[i].resize(TILEX);
	}

	tagTile* tile = (tagTile*)malloc(sizeof(tagTile) * TILEX * TILEY);
	ZeroMemory(tile, sizeof(tagTile) * (TILEX * TILEY));

	HANDLE file2;
	DWORD read2;

	file2 = CreateFile(_mapDataNames[(MAP_TYPE)_mapType].c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file2, tile, sizeof(tagTile) * TILEX * TILEY, &read2, NULL);

	CloseHandle(file2);

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			_vvTile[i][j] = new tagTile;
			_vvTile[i][j]->setTile(tile[j + i * TILEX]);
		}
	}
	//delete[] tile;
}

//속성 세팅하는 함수
void mapTool::setAttribute(UINT samplePage, UINT frameX, UINT frameY)
{
	DWORD storeAttr;
	storeAttr = TS_NONE;
	switch (_samplePage)
	{
	case 0:
		//플레이어가 통과 못하는 타일
		if ((frameX == 0 || frameX == 1) && (frameY >= 2 && frameY < 5))
		{
			storeAttr |= TS_UNMOVE;
		}
		//경사길 타일(각도 계산한 함수와 어떻게 연동할지 고민좀 해보자아)
		if ((frameX >= 2 && frameX < SAMPLE_WIDTH_NUM) && (frameY == 0 || frameY == 3 || frameY == 4))
		{
			storeAttr |= TS_SLOPE;
			if (frameY == 0)
			{
				storeAttr |= TS_WATER;
				storeAttr |= TS_ZORDER;
			}
			if (frameY == 3)
			{
				storeAttr |= TS_CEILING;
			}
		}
		if ((frameX >= 2 && frameX < SAMPLE_WIDTH_NUM) && (frameY == 1 || frameY == 2))
		{
			storeAttr |= TS_WATER;
			storeAttr |= TS_ZORDER;
		}
		//zorder
		if (((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 2) && (frameY == 5 || frameY == 6) )||
			((frameX == 4 ||frameX == 5) && (frameY == 7 || frameY == 8)))
		{
			storeAttr |= TS_ZORDER;
		}
		//가시
		if ((frameX == 4 || frameX == 5) && (frameY == 5 || frameY == 6))
		{
			storeAttr |= TS_THORN_BUSH;
		}
		//포탈
		if (frameX == 1 && frameY == 8)
		{
			storeAttr |= TS_POTAL;
		}
		break;
	case 1:
		if (((frameX == 0 || frameX == 1) && (frameY == 0 || frameY == 2)) ||
			((frameX == SAMPLE_WIDTH_NUM - 1 && frameY == 3)) ||
			((frameX >= 1 && frameX <= 3) && (frameY == 8)))
		{
			storeAttr |= TS_UNMOVE;
		}
		if ((frameX >= 2 && frameX < SAMPLE_WIDTH_NUM) && (frameY == 0 || frameY == 2))
		{
			storeAttr |= TS_SLOPE;
			if (frameY == 0)
				storeAttr |= TS_CEILING;
		}
		if ((((frameX >= 0 && frameX < 3) || frameX == SAMPLE_WIDTH_NUM - 1) && frameY == 1) ||
			(frameX == 0 && frameY == 3) ||
			((frameX == 1 || frameX == 2) && frameY == 7) ||
			((frameX == SAMPLE_WIDTH_NUM - 2 || frameX == SAMPLE_WIDTH_NUM - 1) && frameY == 7) ||
			(frameX == SAMPLE_WIDTH_NUM - 1 && (frameY == 8 ||frameY == 9)))
		{
			storeAttr |= TS_ZORDER;
		}
		if (frameX == 1 && frameY == 6)
		{
			storeAttr |= TS_POTAL;
		}
		break;
	case 2:
		if (((frameX >= 0 && frameX < 3) && frameY == 0) ||
			((frameX == 2 || frameX == 3) && (frameY == 2 ||frameY == 3)))
		{
			storeAttr |= TS_UNMOVE;
		}
		if ((frameX == SAMPLE_WIDTH_NUM - 2 || frameX == SAMPLE_WIDTH_NUM - 1) && frameY == 1)
		{
			storeAttr == TS_DIALOGUE;
		}
		if (((frameX == SAMPLE_WIDTH_NUM - 2 || frameX == SAMPLE_WIDTH_NUM - 1) && (frameY == 2 || frameY == 3)) ||
			((frameX == 1 || frameX == 2 || frameX == 4 || frameX == 5) && (frameY >= 6 && frameY <= 8)))
		{
			storeAttr |= TS_SLOPE;
			storeAttr |= TS_ZORDER;
			if (frameY == 8)
				storeAttr |= TS_CEILING;
			if ((frameX >= 1 && frameX < SAMPLE_WIDTH_NUM - 1) && (frameY == 6 || frameY == 7))
			{
				storeAttr |= TS_WATER;
			}
		}
		if (frameX == 3 && (frameY == 6 || frameY == 7 || frameY == 8))
		{
			storeAttr |= TS_WATER;
		}
		if ((frameX >= 0 && frameX <= 2) && (frameY == 4 || frameY == 5) ||
			(frameX == 2 && frameY == 1) ||
			(frameX == 0 && frameY == 6))
		{
			storeAttr |= TS_ZORDER;
		}
		break;
	case 3:
	
		break;
	case 4:
		if ((frameX >= 2 && frameX <= 4) && (frameY >= 5 && frameY <= 7))
		{
			storeAttr |= TS_UNMOVE;
		}
		if ((frameX == 2 || frameX == 3) && (frameY == 8 || frameY == 9))
		{
			storeAttr |= TS_ZORDER;
		}
		if (frameX == SAMPLE_WIDTH_NUM - 1 && frameY == 9)
			storeAttr |= TS_POTAL;
		break;
	case 5:
		if((frameX == 0 || frameX == 1) &&(frameY == 3 || frameY == 4))
		{
			storeAttr |= TS_UNMOVE;
		}
		if (frameX == 2 && frameY == 2)
			storeAttr |= TS_DOOR;
		if (((frameX == 2 && frameX == 3) && frameY == 0) ||
			(frameX == 3 && (frameY == 1 || frameY == 2)))
		{
			storeAttr |= TS_FRAME;
		}

		break;
	case 6:
		if ((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 2) && (frameY >= 0 && frameY < 5))
		{
			storeAttr |= TS_BACK;
		}

		break;
	case 7:
		if ((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 2) && (frameY >= 0 && frameY < 5))
		{
			storeAttr |= TS_BACK;
		}
		break;
	case 8:
		if ((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 2) && (frameY >= 0 && frameY < 5))
		{
			storeAttr |= TS_BACK;
		}
		break;

	default:
		break;
	}

}

//X축 감소
void mapTool::increaseX()
{
	for (int i = 0; i < TILEY; ++i)
	{
		//타겟타일이라는 새로운 변수에 _vvTile[i]의 back()을 대입
		tagTile* targetTile = _vvTile[i].back();
		_vvTile[i].pop_back();

		SAFE_DELETE(targetTile);
	}
	TILEX--;
}
//Y축 감소
void mapTool::increaseY()
{
	for (int i = TILEX - 1; i >= 0; --i)
	{
		//데이터 삭제
		delete _vvTile.back()[i];
		//포인터 주소 삭제
		_vvTile.back()[i] = nullptr;
	}
	_vvTile.pop_back();
	TILEY--;
}
//X축 증가
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
//Y축 증가
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

//각 축의 map Size를 조정했을 때 불러올 함수
void mapTool::increaseMap()
{
	//X축 선택시
	if (_isSelectX && TILEX > 2)
	{
		increaseX();
	}
	//Y축 선택시
	if (_isSelectY && TILEY > 2)
	{
		increaseY();
	}
}

//각 축의 map Size를 조정했을 때 불러올 함수
void mapTool::decreaseMap()
{
	//X축 선택시
	if (_isSelectX)
	{
		decreaseX();
	}
	//Y축 선택시
	if (_isSelectY)
	{
		decreaseY();
	}
}

void mapTool::fileNameSet()
{
	_mapSizeNames.insert(make_pair(MAP_TYPE_NONE, "data/testMapSize.map"));
	_mapDataNames.insert(make_pair(MAP_TYPE_NONE, "data/testMapData.map"));

	_mapSizeNames.insert(make_pair(MAP_TYPE_ONE, "data/mapTypeOneMapSize.map"));
	_mapDataNames.insert(make_pair(MAP_TYPE_ONE, "data/mapTypeOneMapData.map"));

	_mapSizeNames.insert(make_pair(MAP_TYPE_TWO, "data/mapTypeTwoMapSize.map"));
	_mapDataNames.insert(make_pair(MAP_TYPE_TWO, "data/mapTypeTwoMapData.map"));

	_mapSizeNames.insert(make_pair(MAP_TYPE_THREE, "data/mapTypeThreeMapSize.map"));
	_mapDataNames.insert(make_pair(MAP_TYPE_THREE, "data/mapTypeThreeMapData.map"));

	_mapSizeNames.insert(make_pair(MAP_TYPE_FOUR, "data/mapTypeFourMapSize.map"));
	_mapDataNames.insert(make_pair(MAP_TYPE_FOUR, "data/mapTypeFourMapData.map"));
}


//오브젝트 버튼을 눌렀을 때 콜백 함수에 대입연산 될 함수
void mapTool::selectObj()
{
	if (_objSelectCount % 2 == 0)
		_isClickObj = true;
	else if (_objSelectCount % 2 == 1)
		_isClickObj = false;
	_objSelectCount++;
}

