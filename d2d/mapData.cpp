#include "stdafx.h"
#include "mapData.h"
//#include	"player.h"



mapData::mapData()
{
}


mapData::~mapData()
{
}

HRESULT mapData::init(const char * mapSizeFileName, const char * mapFileName)
{
	//_player = new player;
	//_player->init();
	////_player->setMapDataMemoryAdressLink()
	_rangeStartX = _rangeStartY = _rangeMaxX = _rangeMaxY = 0;
	load(mapSizeFileName, mapFileName);
	_portal.clear();

	_saveFrameCount = 0;
	_saveFrameImgIndX = 0;
	_saveFrameImgIdxY = 0;

	_lifeChargeFramCount = 0;
	_lifeChargeFrameIndxX = 0;
	_lifeChargeFrameIndxY = 0;

	_boxFrameCount = 0;
	_boxFrameIndX = 0;
	_boxFrameindY = 0;

	_lifeCapsuleFrameCount = 0;
	_lifeCapsuleIndX = 0;
	_lifeCapsuleIndY = 0;
	return S_OK;
}

void mapData::release()
{
}

void mapData::update()
{
	frameUpdate();
	_rangeStartX = _player->getPosX();
	_rangeStartY = _player->getPosY();
	//카메라 범위바깥 쪽에 있는 맵 타일 들은 출력하지 않기 위해서 그 범위 변수를 재조정 한다.
	_rangeStartY = CAMERA->getPosY() / TILE_SIZE;
	if (_rangeStartY < 0) _rangeStartY = 0;
	_rangeMaxY = ((CAMERA->getPosY() + WINSIZEY) / TILE_SIZE) + 1;
	if (_rangeMaxY >= TILEY) _rangeMaxY = TILEY - 1;

	_rangeStartX = CAMERA->getPosX() / TILE_SIZE;
	if (_rangeStartX < 0) _rangeStartX = 0;
	_rangeMaxX = ((CAMERA->getPosX() + WINSIZEX) / TILE_SIZE) + 1;
	if (_rangeMaxX >= TILEX) _rangeMaxX = TILEX - 1;
}

void mapData::render()
{
	for (; _rangeStartY < _rangeMaxY; ++_rangeStartY)
	{
		for (; _rangeStartX < _rangeMaxX; ++_rangeStartX)
		{
			if (SAMPLETILENAME[_vvTile[_rangeStartY][_rangeStartX]->tileImgIndex] != "none")
			{
				//배경 타일 렌더
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[_rangeStartY][_rangeStartX]->backgroundIndex])->frameRender(_rangeStartX * TILE_SIZE
																														  , _rangeStartY * TILE_SIZE
																														  , _vvTile[_rangeStartY][_rangeStartX]->backgroundX
																														  , _vvTile[_rangeStartY][_rangeStartX]->backgroundY);
				
				//일반 타일 렌더
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[_rangeStartY][_rangeStartX]->tileImgIndex])->frameRender(_rangeStartX * TILE_SIZE
																														, _rangeStartY * TILE_SIZE
																														, _vvTile[_rangeStartY][_rangeStartX]->terrainFrameX
																														, _vvTile[_rangeStartY][_rangeStartX]->terrainFrameY);
				
				//오브젝트 타일 렌더
				IMAGEMANAGER->findImage(SAMPLETILENAME[_vvTile[_rangeStartY][_rangeStartX]->objImgIndex])->frameRender(_rangeStartX * TILE_SIZE
																														, _rangeStartY * TILE_SIZE
																														, _vvTile[_rangeStartY][_rangeStartX]->objectFrameX
																														, _vvTile[_rangeStartY][_rangeStartX]->objectFrameY);
				
				if ((_vvTile[_rangeStartY][_rangeStartX]->attr & TS_SAVE) == TS_SAVE)
				{
					IMAGEMANAGER->findImage("saveFrame")->frameRender(_rangeStartX * TILE_SIZE, _rangeStartY * TILE_SIZE, _saveFrameImgIndX, _saveFrameImgIdxY);
				}
				if ((_vvTile[_rangeStartY][_rangeStartX]->attr & TS_LIFE_CHARGE) == TS_LIFE_CHARGE)
				{
					IMAGEMANAGER->findImage("lifeChargeFrame")->frameRender(_rangeStartX * TILE_SIZE, _rangeStartY * TILE_SIZE, _lifeChargeFrameIndxX, _lifeChargeFrameIndxY);
				}
				if ((_vvTile[_rangeStartY][_rangeStartX]->attr & TS_BOX) == TS_BOX)
				{
					IMAGEMANAGER->findImage("boxFrame")->frameRender(_rangeStartX * TILE_SIZE, _rangeStartY * TILE_SIZE, _boxFrameIndX, _boxFrameindY);
				}
				//if ((_vvTile[_rangeStartX][_rangeStartY]->attr & TS_LIFE_CAPSULE) == TS_LIFE_CAPSULE)
				//{
				//	IMAGEMANAGER->findImage("lifeCapsule")->frameRender(_rangeStartX * TILE_SIZE, _rangeStartY * TILE_SIZE, _lifeCapsuleIndX, _lifeCapsuleIndY);
				//}
			}
		}
		_rangeStartX = CAMERA->getPosX() / TILE_SIZE;
		if (_rangeStartX < 0) _rangeStartX = 0;
	}
	_rangeStartY = CAMERA->getPosY() / TILE_SIZE;
	if (_rangeStartY < 0) _rangeStartY = 0;

}

void mapData::frameUpdate()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if ((_vvTile[i][j]->attr & TS_SAVE) == TS_SAVE)
			{
				_saveFrameCount++;
				if (_saveFrameCount % 5 == 0)
				{
					_saveFrameImgIdxY = 0;
					_saveFrameImgIndX++;
					if (_saveFrameImgIndX > 7)	_saveFrameImgIndX = 0;
				}
			}
			if ((_vvTile[i][j]->attr & TS_LIFE_CHARGE) == TS_LIFE_CHARGE)
			{
				_lifeChargeFramCount++;
				if (_lifeChargeFramCount % 200 < 50)
				{
					_lifeChargeFrameIndxY = 0;
					_lifeChargeFrameIndxX = 0;
				}
				else if (_lifeChargeFramCount % 200 >= 50 && _lifeChargeFramCount % 200 < 100)
				{
					_lifeChargeFrameIndxY = 0;
					_lifeChargeFrameIndxX = 1;
				}
				else if (_lifeChargeFramCount % 200 >= 100 && _lifeChargeFramCount % 200 < 150)
				{
					_lifeChargeFrameIndxY = 0;
					_lifeChargeFrameIndxX = 2;
				}
				else if (_lifeChargeFramCount % 200 >= 150 && _lifeChargeFramCount % 200 < 200)
				{
					_lifeChargeFrameIndxY = 0;
					_lifeChargeFrameIndxX = 3;
				}
			}
			if ((_vvTile[i][j]->attr & TS_BOX) == TS_BOX)
			{
				_boxFrameCount++;
				if (_boxFrameCount % 85 < 50)
				{
					_boxFrameindY = 0;
					_boxFrameIndX = 0;
				}
				else if (_boxFrameCount % 85 >= 50 && _boxFrameCount % 85 < 65)
				{
					_boxFrameindY = 0;
					_boxFrameIndX = 1;
				}
				else if (_boxFrameCount % 85 >= 65 && _boxFrameCount % 85 < 85)
				{
					_boxFrameindY = 0;
					_boxFrameIndX = 2;
				}
			}
			if ((_vvTile[i][j]->attr & TS_LIFE_CAPSULE) == TS_LIFE_CAPSULE)
			{
				_lifeCapsuleFrameCount++;
				if (_lifeCapsuleFrameCount % 10 == 0)
				{
					_lifeCapsuleIndY = 0;
					_lifeCapsuleIndX++;
					if (_lifeCapsuleIndX > 1)	_lifeCapsuleIndX = 0;
				}
			}
		}
	}
}

void mapData::load(const char * mapSizeFileName, const char * mapFileName)
{
	_vvTile.clear();

	HANDLE file;
	DWORD read;

	char mapSize[128] = { 0, };

	file = CreateFile(mapSizeFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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
		if (mapSize[i] == NULL) break;
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

	tagTile* tile = new tagTile[TILEX * TILEY];
	ZeroMemory(tile, sizeof(tagTile) * (TILEX * TILEY));

	HANDLE file2;
	DWORD read2;

	file2 = CreateFile(mapFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file2, tile, sizeof(tagTile) * TILEX * TILEY, &read2, NULL);

	CloseHandle(file2);

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			_vvTile[i][j] = &tile[j + i * TILEX];
		}
	}
}

void mapData::portalLoad()
{



}
