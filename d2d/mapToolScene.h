#pragma once
#include "gameNode.h"
#include "mapTool.h"


class mapToolScene : public gameNode
{
private:
	mapTool* _mapTool;
public:
	mapToolScene();
	~mapToolScene();

	HRESULT init();
	void update();
	void release();
	void render();
		
};

