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
		//����� �Ա�
		tempPortal->x = 32;
		tempPortal->y = 13;
		tempPortal->nextScene = "storeZoneScene";
		tempPortal->nextX = 7;
		tempPortal->nextY = 8;
		//todo	  
		tempPortal->nexDir = 0;
		//�ϴ� 0���� ��θ������� ���߿� �÷��̾ �ϼ��ϰ��� �÷��̾ ���� �������� ������ �ؾ���
		_portal.push_back(tempPortal);
	}
	{
		//�Ƽ��� �����Ա�
		tempPortal->x = 64;
		tempPortal->y = 12;
		tempPortal->nextScene = "cemetryScene";
		tempPortal->nextX = 2;
		tempPortal->nextY = 12;
		//todo	  
		tempPortal->nexDir = 0;
		//�ϴ� 0���� ��θ������� ���߿� �÷��̾ �ϼ��ϰ��� �÷��̾ ���� �������� ������ �ؾ���
		_portal.push_back(tempPortal);
	}
	{
		//������ �ִ� ��
		tempPortal->x = 22;
		tempPortal->y = 32;
		tempPortal->nextScene = "bossMapScene";
		tempPortal->nextX = 15;
		tempPortal->nextY = 13;
		//todo	  
		tempPortal->nexDir = 0;
		//�ϴ� 0���� ��θ������� ���߿� �÷��̾ �ϼ��ϰ��� �÷��̾ ���� �������� ������ �ؾ���
		_portal.push_back(tempPortal);
	}
}







