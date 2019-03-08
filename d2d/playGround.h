#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "townScene.h"
#include "playerTestScene.h"



class playGround : public gameNode
{
private:
	int		_count;
	HCURSOR _cursor1;
	HCURSOR _cursor2;

	

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void cursor();

};