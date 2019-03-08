#include "stdafx.h"
#include "cemetryMap.h"


cemetryMap::cemetryMap()
{
}


cemetryMap::~cemetryMap()
{
}

void cemetryMap::portalLoad()
{
	tagPortal* tempPortal = nullptr;

	tempPortal->x = 2;
	tempPortal->y = 12;
	tempPortal->nextScene = "townScene";
	tempPortal->nextX = 64;
	tempPortal->nextY = 12;
	//todo	  
	tempPortal->nexDir = 0;
	//일단 0으로 모두맞추지만 나중에 플레이어를 완성하고나면 플레이어가 보던 방향으로 나오게 해야함
	_portal.push_back(tempPortal);
}

