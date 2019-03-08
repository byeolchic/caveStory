#pragma once
#include "mapData.h"
class storeZoneMap :public mapData
{
public:
	storeZoneMap();
	~storeZoneMap();
	
	void portalLoad() override;
};

