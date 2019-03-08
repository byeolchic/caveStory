#include "stdafx.h"
#include "storeZoneMap.h"


storeZoneMap::storeZoneMap()
{
}


storeZoneMap::~storeZoneMap()
{
}

void storeZoneMap::portalLoad()
{
	tagPortal* tempPortal = nullptr;

	tempPortal->x = 7;
	tempPortal->y = 8;
	tempPortal->nextScene = "townScene";
	tempPortal->nextX = 32;
	tempPortal->nextY = 13;
	//todo	  
	tempPortal->nexDir = 0;
	//일단 0으로 모두맞추지만 나중에 플레이어를 완성하고나면 플레이어가 보던 방향으로 나오게 해야함
	_portal.push_back(tempPortal);

}


