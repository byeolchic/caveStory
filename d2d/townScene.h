#pragma once
#include "gameNode.h"
#include "townMap.h"


class townScene :
	public gameNode
{
private:
	mapData* _townMap;
	player* _player;
public:
	townScene();
	~townScene();


	HRESULT init();
	void release();
	void update();
	void render();
};

