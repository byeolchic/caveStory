#pragma once
#include "mapData.h"
class townMap :
	public mapData
{
private:
	//vector<tagPortal*> _portal;
public:
	townMap();
	~townMap();

	void portalLoad() override;
};

