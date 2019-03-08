#include "stdafx.h"
#include "townMap.h"


townMap::townMap()
{
}


townMap::~townMap()
{
}

void townMap::portalLoad()
{
	tagPortal* tempPortal = nullptr;
	{
		//저장소 입구
		tempPortal->x = 32;
		tempPortal->y = 13;
		tempPortal->nextScene = "storeZoneScene";
		tempPortal->nextX = 7;
		tempPortal->nextY = 8;
		//todo	  
		tempPortal->nexDir = 0;
		//일단 0으로 모두맞추지만 나중에 플레이어를 완성하고나면 플레이어가 보던 방향으로 나오게 해야함
		_portal.push_back(tempPortal);
	}
	{
		//아서의 묘지입구
		tempPortal->x = 64;
		tempPortal->y = 12;
		tempPortal->nextScene = "cemetryScene";
		tempPortal->nextX = 2;
		tempPortal->nextY = 12;
		//todo	  
		tempPortal->nexDir = 0;
		//일단 0으로 모두맞추지만 나중에 플레이어를 완성하고나면 플레이어가 보던 방향으로 나오게 해야함
		_portal.push_back(tempPortal);
	}
	{
		//보스가 있는 맵
		tempPortal->x = 22;
		tempPortal->y = 32;
		tempPortal->nextScene = "bossMapScene";
		tempPortal->nextX = 15;
		tempPortal->nextY = 13;
		//todo	  
		tempPortal->nexDir = 0;
		//일단 0으로 모두맞추지만 나중에 플레이어를 완성하고나면 플레이어가 보던 방향으로 나오게 해야함
		_portal.push_back(tempPortal);
	}
}







