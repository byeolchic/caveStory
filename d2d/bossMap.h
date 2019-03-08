#pragma once
#include "mapData.h"
class bossMap :
	public mapData
{
public:
	bossMap();
	~bossMap();

	void portalLoad() override;
};

