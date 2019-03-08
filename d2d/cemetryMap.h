#pragma once
#include "mapData.h"
class cemetryMap :
	public mapData
{
public:
	cemetryMap();
	~cemetryMap();

	void portalLoad() override;
};

