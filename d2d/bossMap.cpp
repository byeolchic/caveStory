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
	//�ϴ� 0���� ��θ������� ���߿� �÷��̾ �ϼ��ϰ��� �÷��̾ ���� �������� ������ �ؾ���
	_portal.push_back(tempPortal);
}

