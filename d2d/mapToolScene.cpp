#include "stdafx.h"
#include "mapToolScene.h"


mapToolScene::mapToolScene()
{
}


mapToolScene::~mapToolScene()
{
}

HRESULT mapToolScene::init()
{
	_mapTool = new mapTool;
	_mapTool->init();


	return S_OK;
}

void mapToolScene::update()
{
	_mapTool->update();

}

void mapToolScene::release()
{
	_mapTool->release();

}

void mapToolScene::render()
{
	_mapTool->render();
}
