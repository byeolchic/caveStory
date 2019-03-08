#include "stdafx.h"
#include "bossMap.h"


bossMap::bossMap()
{
}


bossMap::~bossMap()
{
}

void bossMap::portalLoad()
{
	tagPortal* tempPortal = nullptr;

	tempPortal->x = 15;
	tempPortal->y = 13;
	tempPortal->nextScene = "townScene";
	tempPortal->nextX = 22;
	tempPortal->nextY = 32;
	//todo	  
	tempPortal->nexDir = 0;
	//일단 0으로 모두맞추지만 나중에 플레이어를 완성하고나면 플레이어가 보던 방향으로 나오게 해야함
	_portal.push_back(tempPortal);
}

