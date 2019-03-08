#include "stdafx.h"
#include "townScene.h"


townScene::townScene()
{
}


townScene::~townScene()
{
}

HRESULT townScene::init()
{
	CAMERA->init(0, 0, 960, 640);
	_player = new player;
	_player->init();
	_townMap = new townMap;
	_townMap->init("data/mapTypeOneMapSize.map", "data/mapTypeOneMapData.map");

	_player->setMapDataMemoryAdressLink(_townMap);
	_townMap->setPlayerMemoryAdressLink(_player);
	return S_OK;
}

void townScene::release()
{
	_townMap->release();
}

void townScene::update()
{
	_townMap->update();
	_player->update();
	//todo
	CAMERA->move(_player->getPosX(), _player->getPosY());

}

void townScene::render()
{
	_townMap->render();
	_player->render();
}
