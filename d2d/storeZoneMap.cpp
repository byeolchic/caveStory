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
	//�ϴ� 0���� ��θ������� ���߿� �÷��̾ �ϼ��ϰ��� �÷��̾ ���� �������� ������ �ؾ���
	_portal.push_back(tempPortal);

}


