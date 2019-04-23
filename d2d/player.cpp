#include "stdafx.h"
#include "player.h"
#include "mapData.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{

	//세분화한 플레이어의 상태 변수
	_playerState = IDLE;
	//_prePlayerState = IDLE;

	_playerDir = RIGHT;
	//_prePlayerDir = RIGHT;
	
	_jumpState = JUMP_RISE;

	_tileX = 20;
	_tileY = 8;
	_plLeft = _tileX * TILE_SIZE + ((TILE_SIZE - PLAYER_WIDTH) / 2);
	_plTop = _tileY * TILE_SIZE + ((TILE_SIZE - PLAYER_HEIGHT)/ 2);
	
	_playerRC = { (float)_plLeft
				, (float)_plTop
				, (float)_plLeft + (PLAYER_WIDTH)
				, (float)_plTop + (PLAYER_HEIGHT) };
	//타일 검사할 때 사용할 rect
	_probeRcLeft = { (float)_playerRC.left - TILE_SIZE
					,(float)_playerRC.bottom - TILE_SIZE
					,(float)_playerRC.left
					,(float)_playerRC.bottom };
	_probeRcTop = { (float)_playerRC.left
					,(float)_playerRC.top - TILE_SIZE
					,(float)_playerRC.left + TILE_SIZE
					,(float)_playerRC.top };
	_probeRcRight = { (float)_playerRC.right
					,(float)_playerRC.bottom - TILE_SIZE
					,(float)_playerRC.right + TILE_SIZE
					,(float)_playerRC.bottom };
	_probeRcBottom = { (float)_playerRC.left
					,(float)_playerRC.bottom
					,(float)_playerRC.left + TILE_SIZE
					,(float)_playerRC.bottom + TILE_SIZE };
	_jumpPower = JUMP_POWER;
	_slopeAngle = 0.f;
	_gravity = GRAVITY;
	_posX = _plLeft + (PLAYER_WIDTH / 2);
	_posY = _plTop + (PLAYER_HEIGHT / 2);
	
	animationSet();
	

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;
	_posX = _plLeft + (PLAYER_WIDTH / 2);
	_posY = _plTop + (PLAYER_HEIGHT / 2);

	gravity();
	inputKey();
	jump();		//_playerState == jump 일 때 함수

	_playerRC = { (float)_plLeft
				, (float)_plTop
				, (float)_plLeft + (PLAYER_WIDTH)
				, (float)_plTop + (PLAYER_HEIGHT) };
	//타일 검사할 때 사용할 rect
	_probeRcLeft = { (float)_playerRC.left - TILE_SIZE
					,(float)_playerRC.bottom - TILE_SIZE
					,(float)_playerRC.left
					,(float)_playerRC.bottom };
	_probeRcTop = { (float)_playerRC.left
					,(float)_playerRC.top - TILE_SIZE
					,(float)_playerRC.left + TILE_SIZE
					,(float)_playerRC.top };
	_probeRcRight = { (float)_playerRC.right
					,(float)_playerRC.bottom - TILE_SIZE
					,(float)_playerRC.right + TILE_SIZE
					,(float)_playerRC.bottom };
	_probeRcBottom = { (float)_playerRC.left
					,(float)_playerRC.bottom
					,(float)_playerRC.left + TILE_SIZE
					,(float)_playerRC.bottom + TILE_SIZE };

	_tileX = _plLeft / 40;
	_tileY = _plTop / 40;

	
	KEYANIMANAGER->update(_aniKey);
}

void player::render()
{
	D2DMANAGER->drawRectangle(RGB(0, 0, 255), _playerRC);
	//D2DMANAGER->drawRectangle(RGB(0,0,255), _probeRcLeft);
	//D2DMANAGER->drawRectangle(RGB(0,0,255), _probeRcTop);
	//D2DMANAGER->drawRectangle(RGB(0,0,255), _probeRcRight);
	//D2DMANAGER->drawRectangle(RGB(0,0,255), _probeRcBottom);

	//D2DMANAGER->drawRectangle(RGB(0, 0, 255), (_tileX) * TILE_SIZE, _tileY * TILE_SIZE, (_tileX + 1) * TILE_SIZE, (_tileY + 1)* TILE_SIZE);

	////플레이어 왼쪽의 rect
	//D2DMANAGER->drawRectangle(RGB(0, 0, 255), (_tileX - 1 )* TILE_SIZE, _tileY * TILE_SIZE, _tileX * TILE_SIZE, (_tileY + 1) * TILE_SIZE);
	//
	////플레이어 아래의 rect
	//D2DMANAGER->drawRectangle(RGB(0,0,255), _tileX * TILE_SIZE, (_tileY + 1) * TILE_SIZE, (_tileX + 1) * TILE_SIZE, (_tileY + 2) * TILE_SIZE);
	
	/*if (_playerDir == LEFT ||_prePlayerDir == LEFT)*/
	if (_playerDir == LEFT)
		IMAGEMANAGER->findImage(_imgKey)->aniRender( (_playerRC.left + ((_playerRC.right - _playerRC.left) /2 ))- (IMAGEMANAGER->findImage(_imgKey)->GetFrameWidth() / 2)
													,(_playerRC.top + ((_playerRC.bottom - _playerRC.top) / 2 ))- (IMAGEMANAGER->findImage(_imgKey)->GetFrameHeight() / 2)
													,_animation);
	
	/*else if (_playerDir == RIGHT || _prePlayerDir == RIGHT)*/
	else if (_playerDir == RIGHT)
		IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX((_playerRC.left + ((_playerRC.right - _playerRC.left) / 2)) - (IMAGEMANAGER->findImage(_imgKey)->GetFrameWidth() / 2)
															, (_playerRC.top + ((_playerRC.bottom - _playerRC.top) / 2)) - (IMAGEMANAGER->findImage(_imgKey)->GetFrameHeight() / 2)
															, _animation);

	WCHAR str[128];
	int temp1 = _probeRcLeft.left / TILE_SIZE;
	int temp2 = _probeRcLeft.top / TILE_SIZE;
	int tempPt1 = _ptMouse.x / TILE_SIZE;
	int tempPt2 = _ptMouse.y / TILE_SIZE;
	swprintf_s(str, L"mouse 위치의 tileX: %d", tempPt1);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 330, 25, RGB(255, 255, 255));
	swprintf_s(str, L"mouse 위치의 tileY: %d", tempPt2);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 360, 25, RGB(255, 255, 255));

	swprintf_s(str, L"probe Left X: %d", temp1);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 390, 25, RGB(0, 0, 255));
	swprintf_s(str, L"probe Left Y: %d", temp2);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 420, 25, RGB(0, 0, 255));

	swprintf_s(str, L"player Left: %f", _plLeft);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 450, 25, RGB(255, 255, 255));
	swprintf_s(str, L"Player Top: %f", _plTop);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 480, 25,RGB(255, 255 , 255));
	if (_playerState == MOVE && _playerDir == RIGHT)
	{
		swprintf_s(str, L"MOVE RIGHT");
		D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 510, 25, RGB(255, 255, 255));
	}
	if (_playerState == MOVE && _playerDir == LEFT)
	{
		swprintf_s(str, L"MOVE LEFT");
		D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 540, 25, RGB(255, 255, 255));
	}
	swprintf_s(str, L"ATTR : %d", _map->getTile(_tileX, _tileY)->attr );
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 570, 25, RGB(255, 255, 255));

}

void player::inputKey()
{
	int posXInd = _posX / TILE_SIZE;
	int posYInd = _posY / TILE_SIZE;

	int leftInd = _playerRC.left / TILE_SIZE;
	int rightInd = _playerRC.right / TILE_SIZE;
	int topInd = _playerRC.top / TILE_SIZE;
	int bottomInd = _playerRC.bottom / TILE_SIZE;
	if (((_map->getTile((UINT)leftInd, (UINT)topInd)->attr & TS_UNMOVE) == TS_UNMOVE) &&
		((_map->getTile((UINT)posXInd, (UINT)bottomInd)->attr	& TS_UNMOVE) != TS_UNMOVE))
	{
		_plTop += _gravity;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (posXInd == leftInd)
		{
			if ((_map->getTile((UINT)leftInd, (UINT)topInd)->attr & TS_UNMOVE) != TS_UNMOVE)
			{
				_plLeft -= _speed;
			}
		}
		if (posXInd != leftInd)
		{
			if ((_map->getTile((UINT)leftInd, (UINT)topInd)->attr & TS_UNMOVE) != TS_UNMOVE)
			{
				_plLeft -= _speed;
			}
		}
		//if (((_map->getTile((UINT)((_playerRC.left +1) / TILE_SIZE), (UINT)(_playerRC.top / TILE_SIZE))->attr & TS_UNMOVE) == TS_UNMOVE))
		//{
		//	_plLeft += _speed;
		//}
		//if (((_map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.top / TILE_SIZE))->attr & TS_SLOPE) == TS_SLOPE))
		//{
		//
		//}
		//_plLeft -= _speed;
		//if (_playerState == JUMP )
		//{
		//	//_playerState == JUMP_MOVE;
		//}
		if(_playerState != JUMP)
		{
			_playerState = MOVE;
			aniStart("moveLeft");
		}
		_playerDir = LEFT;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		aniStart("left");
		_playerState = IDLE;
		_playerDir = LEFT;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (((_map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.top / TILE_SIZE))->attr  & TS_UNMOVE) == TS_UNMOVE))
		{
			_plLeft -= _speed;
		}
		_plLeft += _speed;
		
		if(_playerState != JUMP)
		{
			_playerState = MOVE;
			aniStart("moveLeft");
		}
		
		_playerDir = RIGHT;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		aniStart("left");
		_playerState = IDLE;
		_playerDir = RIGHT;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_jumpPower = JUMP_POWER;
		if (_playerState == JUMP)
			_jumpPower = 0;
		_playerState = JUMP;
		_jumpState = JUMP_RISE;
		aniStart("jumpRiseLeft");
	}
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		_jumpState = JUMP_FALL;
	}

	//위를 바라보면
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//if (_playerState == MOVE || _playerState == IDLE)
		//{
			aniStart("lookUpIdle");
			
		//}
		//if (_playerState == JUMP)
		//{
		//
		//}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{

	}
	//아래키를 누르면
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{

	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{

	}
}

void player::animationSet()
{
	_imgKey = "quote";
	_aniKey = "quoteAni";

	IMAGEMANAGER->addFrameImage(_imgKey, L"image/quote.png", 440, 40, 11, 1);
	KEYANIMANAGER->addAnimationType(_aniKey);

	int left[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "left", _imgKey, left, 1, 6, false);
	int moveLeft[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "moveLeft", _imgKey, moveLeft, 4, 6, false);
	int jumpRiseLeft[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpRiseLeft", _imgKey, jumpRiseLeft, 1, 6, false);
	int jumpFallLeft[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpFallLeft", _imgKey, jumpFallLeft, 1, 6, false);
	int jumpRiseLookUpLeft[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpRiseLookUpLeft", _imgKey, jumpRiseLookUpLeft, 1, 6, false);
	int jumpFallLookUpLeft[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpFallLookUpLeft", _imgKey, jumpFallLookUpLeft, 1, 6, false);
	int jumpLookDownLeft[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpLookDownLeft", _imgKey, jumpLookDownLeft, 1, 6, false);
	int lookUpIdle[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "lookUpIdle", _imgKey, lookUpIdle, 1, 6, false);
	int lookDownIdle[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "lookDownIdle", _imgKey, lookDownIdle, 1, 6, false);

	aniStart("left");


}

void player::aniStart(string aniKey)
{
	_animation = KEYANIMANAGER->findAnimation(_aniKey, aniKey);
	_animation->start();
}



void player::gravity()
{
	DWORD leftBottomAttr = _map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr;
	DWORD rightBottomAttr = _map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr;
	int temp1 = _playerRC.left / TILE_SIZE;
	int temp2 = _playerRC.right / TILE_SIZE;
	//플레이어가 딱 한 타일에 들어있을 때
	if (temp1 == temp2)
	{
		//만약에 플레이어의 바닥 면이 비어있으면 중력을 받음
		if (((leftBottomAttr & TS_UNMOVE) != TS_UNMOVE) &&
			((rightBottomAttr & TS_UNMOVE) != TS_UNMOVE))
		{
			for (int i = 0; i < 300; ++i)
			{
				_gravity = TIMEMANAGER->getElapsedTime() * (GRAVITY + 0.1 * i);
			}
			_plTop += _gravity;
		}
		//왼쪽이나 오른쪽의 바닥 중 하나라도 unmove 속성이 있으면 중력 X
		if (((leftBottomAttr & TS_UNMOVE) == TS_UNMOVE) ||
			((rightBottomAttr & TS_UNMOVE) == TS_UNMOVE))
		{
			_gravity = 0;
			_playerState = IDLE;
		}
	}
	//플레이어가 두 타일에 걸쳐있을 때
	if (temp1 != temp2)
	{
		if (((leftBottomAttr & TS_UNMOVE) != TS_UNMOVE) &&
			((rightBottomAttr & TS_UNMOVE) != TS_UNMOVE))
		{
			for (int i = 0; i < 300; ++i)
			{
				_gravity = TIMEMANAGER->getElapsedTime() * (GRAVITY + 0.1 * i);
			}
			_plTop += _gravity;
		}
		//왼쪽이나 오른쪽의 바닥 중 하나라도 unmove 속성이 있으면 중력 X
		if (((leftBottomAttr & TS_UNMOVE) == TS_UNMOVE) &&
			((rightBottomAttr & TS_UNMOVE) == TS_UNMOVE))
		{
			_gravity = 0;
			_playerState = IDLE;

		}
	}
	
	//DWORD leftTopAttr = _map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.top / TILE_SIZE))->attr;
	//DWORD rightTopAttr = _map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.top / TILE_SIZE))->attr;

	//DWORD leftBottomAttr = _map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr;
	//DWORD rightBottomAttr = _map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr;
	////만약에 플레이어의 밑면이 바닥과 닿아있으면 _gravity 는 0
	//if (((_map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr & TS_UNMOVE) == TS_UNMOVE) &&
	//	((_map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr & TS_UNMOVE) == TS_UNMOVE))
	//{
	//	_playerState = IDLE;
	//}
	////바닥과 닿아있지 않으면 _gravity 를 받고 밑으로 떨어짐
	//if ((_playerRC.left / TILE_SIZE == _playerRC.right / TILE_SIZE) &&
	//	(leftBottomAttr & TS_UNMOVE) == TS_UNMOVE && (leftTopAttr & TS_UNMOVE) == TS_UNMOVE)
	//{
	//	_jumpPower = 0;
	//	_jumpState = JUMP_FALL;
	//	aniStart("jumpFallLeft");
	//}


	//if (((_map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr & TS_UNMOVE) != TS_UNMOVE) &&
	//	((_map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr & TS_UNMOVE) != TS_UNMOVE))
	//{
	//	for (int i = 0; i < 300; ++i)
	//	{
	//		_gravity = TIMEMANAGER->getElapsedTime() * (GRAVITY + 0.1 * i);
	//	}
	//	_plTop += _gravity;
	//}
}

void player::collisionHead()
{

}

void player::jump()
{
	//맵의 속성을 대입
	DWORD leftTopAttr = _map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.top / TILE_SIZE))->attr;
	DWORD rightTopAttr = _map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.top / TILE_SIZE))->attr;

	DWORD leftBottomAttr = _map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr;
	DWORD rightBottomAttr = _map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.bottom / TILE_SIZE))->attr;
	//플레이어가 점프를 하면
	if (_playerState == JUMP || _playerState == JUMP_MOVE)
	{
		//플레이어의 윗면이 UNMOVE에 닿으면
		if ((_playerRC.left/ TILE_SIZE == _playerRC.right / TILE_SIZE) &&
			((_map->getTile((UINT)(_playerRC.left / TILE_SIZE), (UINT)(_playerRC.top / TILE_SIZE))->attr & TS_UNMOVE) == TS_UNMOVE) ||
			((_map->getTile((UINT)(_playerRC.right / TILE_SIZE), (UINT)(_playerRC.top  / TILE_SIZE))->attr  & TS_UNMOVE) == TS_UNMOVE))
		{
			_jumpPower = 0;
			_jumpState = JUMP_FALL;
			aniStart("jumpFallLeft");
		}
		if ((_playerRC.left / TILE_SIZE == _playerRC.right / TILE_SIZE) &&
			(leftBottomAttr & TS_UNMOVE) == TS_UNMOVE && (leftTopAttr & TS_UNMOVE) == TS_UNMOVE)
		{
			_jumpPower = 0;
			_jumpState = JUMP_FALL;
			aniStart("jumpFallLeft");
		}
		
	
		_plTop -= TIMEMANAGER->getElapsedTime() * _jumpPower;
		for (int i = 0; i < 300; ++i)
		{
			_gravity = TIMEMANAGER->getElapsedTime() * (GRAVITY + 0.1 * i);
		}
		_jumpPower -= _gravity;
	
		if (_jumpPower < 0)
		{
			_jumpState = JUMP_FALL;
			aniStart("jumpFallLeft");
		}
	
	}
}
