#include "stdafx.h"
#include "playerTestScene.h"


playerTestScene::playerTestScene()
{
}


playerTestScene::~playerTestScene()
{
}

HRESULT playerTestScene::init()
{
	_player = new player;
	_player->init();


	return S_OK;
}

void playerTestScene::release()
{
	_player->release();
}

void playerTestScene::update()
{
	_player->update();
}

void playerTestScene::render()
{
	_player->render();
}
