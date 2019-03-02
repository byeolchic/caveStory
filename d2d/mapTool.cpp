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
	//=====================================<< 할 일 >>==========================================
	//	오브젝트 버튼 만들기

	//맵툴 입시 백그라운드
	IMAGEMANAGER->addImage("maptoolBackground", L"image/tile/mapToolBackground2.png", 1250, 840);

	//이전, 다음 버튼
	IMAGEMANAGER->addFrameImage("nextButton", L"image/buttonImg/nextButton.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("preButton", L"image/buttonImg/preButton.png", 60, 120, 1, 2);
	
	_sampleNextPageButton = new button;
	_sampleNextPageButton->init("nextButton", WINSIZEX - 90, 490, PointMake(0, 1), PointMake(0, 0), cbChangeNextSample);
	_samplePrePageButton = new button;
	_samplePrePageButton->init("preButton", WINSIZEX - 190, 490, PointMake(0, 1), PointMake(0, 0), cbChangePreSample);
	
	//맵 x축, y축 버튼
	IMAGEMANAGER->addFrameImage("X축", L"image/buttonImg/X축.png", 60, 120, 1, 2);
	IMAGEMANAGER->addFrameImage("Y축", L"image/buttonImg/Y축.png", 60, 120, 1, 2);
	_selectXButton = new button;
	_selectXButton->init("X축", WINSIZEX - 200, 550, PointMake(0, 1), PointMake(0, 0),cbSelectX);
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

	//오브젝트 버튼
	IMAGEMANAGER->addFrameImage("objectButton", L"image/buttonImg/objectButton.png", 100, 120, 1, 2);
	_selectObj = std::move(bind(&mapTool::selectObj, this));
	_objButton = new button;
	_objButton->init("objectButton", WINSIZEX - 300, 490, PointMake(0, 1), PointMake(0, 0), _selectObj);


	//샘플 이미지
	_sampleImg[0] = nullptr;
	_sampleImg[1] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_01], L"image/tile/tile_01.png", 240, 400, 6, 10);
	_sampleImg[2] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_02], L"image/tile/tile_02.png", 240, 400, 6, 10);
	_sampleImg[3] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_03], L"image/tile/tile_03.png", 240, 400, 6, 10);
	_sampleImg[4] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_04], L"image/tile/tile_04.png", 240, 400, 6, 10);
	_sampleImg[5] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_05], L"image/tile/tile_05.png", 240, 400, 6, 10);
	_sampleImg[6] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_06], L"image/tile/tile_06.png", 240, 400, 6, 10);
	_sampleImg[7] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_07], L"image/tile/tile_07.png", 224, 210, 6, 10);
	_sampleImg[8] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_08], L"image/tile/tile_08.png", 224, 210, 6, 10);
	_sampleImg[9] = IMAGEMANAGER->addFrameImage(SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_09], L"image/tile/tile_09.png", 224, 210, 6, 10);

	

	_samplePage = 1;
	CAMERA->init(0, 0, 5000, 5000);

	mapToolSetting();			//맵툴의 기본 타일들의정보를 setting함

	TILEX = _reSizeX = MAP_WIDTH_NUM;
	TILEY = _reSizeY = MAP_HEIGHT_NUM;

	_isClick = false;

	_pickSample.indX = 0;
	_pickSample.indY = 0;
	_pickSample.tileImgPage = 0;

	//루프렌더용
	_loopRect = { 0, 0, 1120, 840 };
	_loopX = 0.f;

	//맵사이즈 조정에서 X축 증감을 선택했냐? 불값 초기화
	_isSelectX = _isSelectY= false;
	_boolCountX = _boolCountY = 0;

	//타일의 각도 계산할때 필요한 변수들
	_pt.x = 0.f;
	_pt.y = 0.f;
	_getAngleF = 0.f;
	_calculateNum = 0;

	//타일을 드래그로 범위 지정하여 그릴 때 사용할 변수
	_isShift = false;
	
	//오브젝트 버튼을 눌렀냐?
	_isClickObj = false;
	_objSelectCount = 0;


	return S_OK;
}

void mapTool::update()
{
	_loopRect = { (float)CAMERA->getPosX(), (float)CAMERA->getPosY(), (float)CAMERA->getPosX() + 1120, (float)CAMERA->getPosY() + 840 };

	_loopX += 0.5f;
	CAMERA->mapToolMove();
	_sampleNextPageButton->update(WINSIZEX - 90, 490);
	_samplePrePageButton->update(WINSIZEX - 190, 490);
	_selectXButton->update(WINSIZEX - 200, 550);
	_selectYbutton->update(WINSIZEX - 100, 550);
	_increaseButton->update(WINSIZEX - 150, 600);
	_decreaseButton->update(WINSIZEX - 150, 665);
	_objButton->update(WINSIZEX - 300, 490);

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
			if (!_isClickObj)
			{
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->tileImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																								  , _vvTile[i][j]->terrainFrameX
																								  , _vvTile[i][j]->terrainFrameY);
			}
			else
			{
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->tileImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																								  , _vvTile[i][j]->objectFrameX
																								  , _vvTile[i][j]->objectFrameY);
			}
			IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[i][j]->tileImgIndex])->frameRender(40 + j * TILE_SIZE, 40 + i * TILE_SIZE
																							  , _vvTile[i][j]->objectFrameX
																							  , _vvTile[i][j]->objectFrameY);
		}
	}

	//맵 그리는 쪽의 렉트를 그리는 부분
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


	//샘플 타일 출력
	IMAGEMANAGER->findImage(SAMPLETILENAME[_samplePage])->render(CAMERA->getPosX() + WINSIZEX - 280, CAMERA->getPosY() + SAMPLE_DISTANCE_Y);
	
	//샘플쪽 rect 출력
	if ((_samplePage < 6 ))
	{
		for (int i = 0; i < SAMPLE_HEIGHT_NUM; ++i)
		{
			for (int j = 0; j < SAMPLE_WIDTH_NUM; j++)
			{
				D2DMANAGER->drawRectangle(CAMERA->getPosX() + (WINSIZEX - 280) + (j * TILE_SIZE), CAMERA->getPosY() + SAMPLE_DISTANCE_Y + (i * TILE_SIZE),
					CAMERA->getPosX() + (WINSIZEX - 280) + ((j + 1) * TILE_SIZE), CAMERA->getPosY() + SAMPLE_DISTANCE_Y + ((i + 1) * TILE_SIZE));
			}
		}
	}
	if (_isClick)
	{
		IMAGEMANAGER->findImage(SAMPLETILENAME[_pickSample.tileImgPage])->frameRender(_ptMouse.x + 20, _ptMouse.y + 20, _pickSample.indX, _pickSample.indY, 0.5f);
	}
	WCHAR str[128];
	swprintf_s(str, L"angle : %f", _getAngleF);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 500);
	swprintf_s(str, L"select X축 : %d", _isSelectX);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 520);
	swprintf_s(str, L"select Y축 : %d", _isSelectY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 540);

	swprintf_s(str, L"TILEX : %d", TILEX);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 560, 30);
	swprintf_s(str, L"TILEY : %d", TILEY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 590, 30);

	swprintf_s(str, L"resizeX : %d", _reSizeX);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 620, 30);
	swprintf_s(str, L"resizeY : %d", _reSizeY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 650, 30);
	
	swprintf_s(str, L"오브젝트냐: %d", _isClickObj);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 680, 30);

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

void mapTool::mapToolSetting()
{
	for (int i = 0; i < MAP_HEIGHT_NUM; ++i)
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < MAP_WIDTH_NUM; ++j)
		{
			tagTile* tile = new tagTile;

			tile->tileImgIndex = 1;
			tile->terrainFrameX = NULL;
			tile->terrainFrameY = NULL;
			tile->objectFrameX = NULL;
			tile->objectFrameY = NULL;
			tile->zOrderFrameX = NULL;	
			tile->zOrderFrameY = NULL;	
			tile->attr = TS_NONE;
			tile->isObj = false;
			tile->isZorder = false;

			vTile.push_back(tile);
		}
		_vvTile.push_back(vTile);
	}
}

void mapTool::pickSample()
{
	if (_ptMouse.x - CAMERA->getPosX() < SAMPLE_START_POSX)
		return;
	if (_ptMouse.y - CAMERA->getPosY() < SAMPLE_DISTANCE_Y)
		return;
	if (_ptMouse.x - CAMERA->getPosX() > SAMPLE_START_POSX + (SAMPLE_WIDTH_NUM * TILE_SIZE))
		return;
	if(_ptMouse.y - CAMERA->getPosY() > SAMPLE_DISTANCE_Y + (SAMPLE_HEIGHT_NUM * TILE_SIZE))
	   return;

	int frameX = (_ptMouse.x - CAMERA->getPosX() - SAMPLE_START_POSX) / TILE_SIZE;
	int frameY = (_ptMouse.y - CAMERA->getPosY() - SAMPLE_DISTANCE_Y) / TILE_SIZE;

	int backX = (_ptMouse.x - CAMERA->getPosX() - SAMPLE_START_POSX) / 224;			//백그라운드는 사이즈가 달라서 변수 따로 만들었어여
	int backY = (_ptMouse.y - CAMERA->getPosY() - SAMPLE_DISTANCE_Y) / 210;						//frame은 없는 이미지에여
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
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
			}
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
			}
			break;

		case 5:
			if ((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 1) && (frameY == 0 || frameY == 4 || frameY == 5) ||
				((frameX >= 0 && frameX < SAMPLE_WIDTH_NUM) && ((frameY >= 1 && frameY < 4) || (frameY >= 6 && frameY < SAMPLE_HEIGHT_NUM))))
			{
				_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_05;
				_pickSample.indX = frameX;
				_pickSample.indY = frameY;
			}
			break;

		case 6:
			if ((frameX == 0 || frameX == 1) && (frameY >= 0 && frameY <= 4))
			{
				_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_06;
				_pickSample.indX = frameX;
				_pickSample.indY = frameY;
			}
			break;

		case 7: case 8: case 9:
			if (backX == 0 && backY == 0)
			{
				if (_samplePage == 7)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_07;
				else if (_samplePage == 8)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_08;
				else if (_samplePage == 9)
					_pickSample.tileImgPage = SAMPLE_TILE_IMAGEKEY_09;
				_pickSample.indX = backX;
				_pickSample.indY = backY;
			}

		default:
			break;
		}
		_isClick = true;
	}
}

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
	
	////드래그로 그리기
	////아직 보류
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
			for (int i = 0; i < TILEY; ++i)
			{
				for (int j = 0; j < TILEX; ++j)
				{
					if (_ptMouse.x > (j + 1) * TILE_SIZE && _ptMouse.x < (j + 2) * TILE_SIZE
						&& _ptMouse.y > (i + 1) * TILE_SIZE && _ptMouse.y < (i + 2) * TILE_SIZE)
					{
						if (!_isClickObj)
						{
							_vvTile[i][j]->tileImgIndex = _pickSample.tileImgPage;
							_vvTile[i][j]->terrainFrameX = _pickSample.indX;
							_vvTile[i][j]->terrainFrameY = _pickSample.indY;
							_vvTile[i][j]->objectFrameX = _pickSample.indX;
							_vvTile[i][j]->objectFrameY = _pickSample.indY;
						}
						else
						{
							_vvTile[i][j]->objectFrameX = _pickSample.indX;
							_vvTile[i][j]->objectFrameY = _pickSample.indY;
						}
					}
				}
			}
		}
	}

}

void mapTool::save()
{



}

void mapTool::load()
{
}

//속성 세팅하는 함수
void mapTool::setAttribute(UINT samplePage, UINT frameX, UINT frameY)
{
	DWORD storeAttr;
	switch (_samplePage)
	{
	case 0:
		//바닥
		if ((frameX == 1 && frameY == 0) ||
			((frameX >= 2 && frameX < SAMPLE_WIDTH_NUM) && frameY == 1) ||
			(frameX == 0 || frameX == 1) && (frameY == 2 || frameY == 3) ||
			(frameX >= 0 && frameX < SAMPLE_WIDTH_NUM - 2) && frameY == 4 ||
			(frameX == 3 || frameX == 4) && frameY == 6)
		{

		}

		//경사

		//천장
		//if ((frameX >= 2 && frameX < SAMPLE_WIDTH_NUM) && frameY == 0) ||
		//	(frameX) && () || )


		//물
		//벽
		//제트오더

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

		newTile->tileImgIndex = 1;
		newTile->terrainFrameX = NULL;
		newTile->terrainFrameY = NULL;
		newTile->objectFrameX = NULL;
		newTile->objectFrameY = NULL;
		newTile->zOrderFrameX = NULL;
		newTile->zOrderFrameY = NULL;
		newTile->attr = TS_NONE;
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
		newTile->tileImgIndex = 1;
		newTile->terrainFrameX = NULL;
		newTile->terrainFrameY = NULL;
		newTile->objectFrameX = NULL;
		newTile->objectFrameY = NULL;
		newTile->zOrderFrameX = NULL;
		newTile->zOrderFrameY = NULL;
		newTile->attr = TS_NONE;
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
	if (_isSelectX && TILEX > 2 )
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

//오브젝트 버튼을 눌렀을 때 콜백 함수에 대입연산 될 함수
void mapTool::selectObj()
{
	if (_objSelectCount % 2 == 0)
		_isClickObj = true;
	else if (_objSelectCount % 2 == 1)
		_isClickObj = false;
	_objSelectCount++;
}

