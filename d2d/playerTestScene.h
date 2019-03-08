#pragma once
#include "player.h"
class playerTestScene : public gameNode
{
private:
	player* _player;


public:
	playerTestScene();
	~playerTestScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

