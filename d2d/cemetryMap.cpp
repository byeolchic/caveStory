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
	//�ϴ� 0���� ��θ������� ���߿� �÷��̾ �ϼ��ϰ��� �÷��̾ ���� �������� ������ �ؾ���
	_portal.push_back(tempPortal);
}

