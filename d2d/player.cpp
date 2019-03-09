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
	_prePlayerState = IDLE;

	_playerDir = RIGHT;
	_prePlayerDir = RIGHT;
	
	_jumpState = JUMP_RISE;

	_tileX = 20;
	_tileY = 13;
	_centerX = _tileX * 40;
	_centerY = _tileY * 40 ;
	
	_playerRC = { (float)_centerX 
				,(float)_centerY
				,(float)(_centerX + PLAYER_WIDTH)
				,(float)(_centerY + PLAYER_HEIGHT)};

	_jumpPower = 0;
	_gravity = GRAVITY;
	
	
	animationSet();
	

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	
	_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;
	
	inputKey();
	if (_playerState == JUMP || _prePlayerState == JUMP)
		jump();
	animationSet();

	_playerRC = { (float)_centerX
				,(float)_centerY
				,(float)(_centerX + PLAYER_WIDTH)
				,(float)(_centerY + PLAYER_HEIGHT) };
	KEYANIMANAGER->update(_aniKey);
}

void player::render()
{
	D2DMANAGER->drawRectangle(_playerRC);
	
	if (_playerDir == LEFT ||_prePlayerDir == LEFT)
		IMAGEMANAGER->findImage(_imgKey)->aniRender( (_playerRC.left + ((_playerRC.right - _playerRC.left) /2 ))- (IMAGEMANAGER->findImage(_imgKey)->GetFrameWidth() / 2)
													,(_playerRC.top + ((_playerRC.bottom - _playerRC.top) / 2 ))- (IMAGEMANAGER->findImage(_imgKey)->GetFrameHeight() / 2)
													,_animation);
	
	else if (_playerDir == RIGHT || _prePlayerDir == RIGHT)
		IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX((_playerRC.left + ((_playerRC.right - _playerRC.left) / 2)) - (IMAGEMANAGER->findImage(_imgKey)->GetFrameWidth() / 2)
															, (_playerRC.top + ((_playerRC.bottom - _playerRC.top) / 2)) - (IMAGEMANAGER->findImage(_imgKey)->GetFrameHeight() / 2)
															, _animation);

	WCHAR str[128];
	swprintf_s(str, L"centerY: %f", _centerY);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 450, 25, RGB(255, 255, 255));
	swprintf_s(str, L"Jump Power: %f", _jumpPower);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 500, 25,RGB(255, 255 , 255));
	//맨 첫시작에 렌더할때는 
	//if(!_isLeft && !_isRight && _isIdle)
	//	IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX(_playerRC.left, _playerRC.top, _animation);
	//
	////왼쪽 방향의 액션일 때
	//if ((_isLeft && _isIdle) || _isLeft)
	//	IMAGEMANAGER->findImage(_imgKey)->aniRender(_playerRC.left, _playerRC.top, _animation);
	////오른쪽 방향의 액션일 때
	//if ((_isRight && _isIdle) || _isRight)
	//	IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX(_playerRC.left, _playerRC.top, _animation);
}

void player::inputKey()
{
	//움직이는 키
	switch (_playerState)
	{
	case IDLE:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) 
		{
			_playerState = MOVE;
			_playerDir = LEFT; 
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_playerState = MOVE;
			_playerDir = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP)) 
		{
			_prePlayerDir = _playerDir;
			_playerDir = TOP; 
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) 
		{ 
			_prePlayerDir = _playerDir; 
			_playerDir = BOTTOM; 
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}
		//점프키
		if (KEYMANAGER->isStayKeyDown('X'))
		{
			_playerState = JUMP;
			_jumpState = JUMP_RISE;
			_jumpPower = JUMP_POWER;
			
			//만약에 점프 파워가 중력에 의해 0이 되면 
			//if(){_jumpState = JUMP_FALL;}
		}
		if (KEYMANAGER->isOnceKeyUp('X'))
		{
			_jumpState = JUMP_FALL;
		}
		break;
	case MOVE:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) 
		{
			_playerState = MOVE; 
			_playerDir = LEFT; 
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) 
		{ 
			_playerState = MOVE;	
			_playerDir = RIGHT; 
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP)) 
		{
			_prePlayerDir = _playerDir;
			_playerDir = TOP; 
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) 
		{
			_prePlayerDir = _playerDir;
			_playerDir = BOTTOM; 
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_DOWN)) 
		{ 
			_playerState = IDLE; 
			if (_prePlayerDir == LEFT) _playerDir = LEFT; 
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT; 
		}
		//점프키
		if (KEYMANAGER->isStayKeyDown('X'))
		{
			_playerState = JUMP;
			_jumpState = JUMP_RISE;
			
			//만약에 점프 파워가 중력에 의해 0이 되면 
			//if(){_jumpState = JUMP_FALL;}
		}
		if (KEYMANAGER->isOnceKeyUp('X'))
		{
			_jumpState = JUMP_FALL;
		}
		break;
	case JUMP:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_prePlayerState = JUMP;
			_playerState = MOVE;
			_playerDir = LEFT;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_prePlayerState = JUMP;
			_playerState = MOVE;
			_playerDir = RIGHT;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_prePlayerDir = _playerDir;
			_playerDir = TOP;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_prePlayerDir = _playerDir;
			_playerDir = BOTTOM;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_playerState = IDLE;
			if (_prePlayerDir == LEFT) _playerDir = LEFT;
			else if (_prePlayerDir == RIGHT) _playerDir = RIGHT;
		}
		
		break;
	case ATK:
		break;
	
	default:
		break;
	}

	moveLeft();
	moveRight();
	/*if (_playerDir == LEFT && _playerState == MOVE && _playerDir != RIGHT) {  }
	else if (_playerDir == RIGHT && _playerState == MOVE && _playerDir != LEFT) {  }*/


	//if (_playerDir == TOP || _playerDir == BOTTOM)
	//{
	//	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	//	{
	//		//이전 방향이 왼쪽이냐 오른쪽이냐에 따라서 현재 설정할 플레이어의 방향이 달라짐
	//		_playerState = IDLE;
	//		_playerDir = _prePlayerDir;
	//		/*if (_prePlayerDir == LEFT)
	//			_playerDir = LEFT;
	//		if (_prePlayerDir == RIGHT)
	//			_playerDir = RIGHT;*/
	//	}
	//	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	//	{
	//		_playerState = IDLE;
	//		_playerDir = _prePlayerDir;
	//	}
	//}


	//왼쪽
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	moveLeft();
	//	_prePlayerState = _playerState;
	//	_playerState = MOVE;
	//	_prePlayerDir = _playerDir;
	//	_playerDir = LEFT;
	//}
	//if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	//{
	//	_playerState = IDLE;
	//	_playerDir = LEFT;
	//}
	////오른쪽
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	moveRight();
	//	_prePlayerState = _playerState;
	//	_playerState = MOVE;
	//	_prePlayerDir = _playerDir;
	//	_playerDir = RIGHT;
	//}
	//if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	//{
	//	_playerState = IDLE;
	//	_playerDir = RIGHT;
	//}
	////위쪽 바라보기
	//if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//	_prePlayerState = _playerState;
	//	_prePlayerDir = _playerDir;

	//	_playerState = IDLE;
	//	_playerDir = TOP;
	//}
	//
	////아래키
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//	_prePlayerState = _playerState;
	//	_prePlayerDir = _playerDir;
	//	//만약에 이전 방향이 왼쪽이고 현재 방향이 BOTTOM 이면 왼쪽에서 벽보는 이미지가 나와야함
	//	_playerDir = BOTTOM;
	//	//1. 점프가 아닐 때는 벽을 봄(움직이는 중이거나 아이들 상태였을 때)
	//	if (_playerState == MOVE || _playerState == IDLE)
	//	{
	//		_playerState = IDLE;
	//		// 1-1.만약에 포탈이 있으면 씬 전환

	//		//1-2.만약에 아이템이 있으면 아이템을 주움
	//	}
	//	//보류
	//	/*
	//	//2. 점프일 때는 아래방향으로 팔을내림
	//	//if (_playerState == JUMP)
	//	//{
	//	//
	//	//}
	//	// 3. 공격일 때는 아래방향으로 총을 쏨
	//	//if(_playerState == ATK)
	//	//{
	//	//	//_playerDir
	//	//}
	//	*/
	//}
	//
	////공격키
	//if (KEYMANAGER->isOnceKeyDown('Z'))
	//{
	//	_prePlayerState = _playerState;
	//	//_prePlayerDir = _playerDir;

	//	_playerState = ATK;
	//}
	//if (KEYMANAGER->isOnceKeyUp('Z'))
	//{
	//	_playerState = _prePlayerState;
	//	//_playerDir
	//}
	////점프키
	//if (KEYMANAGER->isOnceKeyDown('X'))
	//{
	//	_playerState = JUMP;
	//	_jumpState = JUMP_RISE;
	//	//만약에 점프 파워가 중력에 의해 0이 되면 
	//	//if(){_jumpState = JUMP_FALL;}
	//}
	//if (KEYMANAGER->isOnceKeyUp('X'))
	//{
	//	_jumpState = JUMP_FALL;
	//}

	

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
	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "moveLeft", _imgKey, moveLeft, 4, 6, true);
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
	

	/*
	int downLeft[] = { 8 };
	int upLeft[] = { 7 };
	int jumpLeft[] = { 3 };
	int downAtkLeft[] = { 9 };
	int fallingLeft[] = { 4 };
	//int upAtkLeft[] = { 7 };
	int jumpUpAtkLeft[] = { 5 };
	int fallingUpAtkLeft[] = { 6 };
	switch (_playerState)
	{
	case IDLE:
		if (_playerDir == LEFT)
		{
			KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "left", _imgKey, left, 1, 6, false);
			_animation = KEYANIMANAGER->findAnimation(_aniKey, "left");
		}
		if (_playerDir == RIGHT)
		{
			KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "left", _imgKey, left, 1, 6, false);
			_animation = KEYANIMANAGER->findAnimation(_aniKey, "left");
		}
		if (_playerDir == TOP)
		{
			KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "upLeft", _imgKey, upLeft, 1, 6, false);
			_animation = KEYANIMANAGER->findAnimation(_aniKey, "upLeft");
		}
		if (_playerDir == BOTTOM)
		{
			KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "downLeft", _imgKey, downLeft, 1, 6, false);
			_animation = KEYANIMANAGER->findAnimation(_aniKey, "downLeft");
		}
		break;
	case MOVE:
		if (_playerDir == LEFT)
		{
			KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "moveLeft", _imgKey, moveLeft, 4, 6, false);
			_animation = KEYANIMANAGER->findAnimation(_aniKey, "moveLeft");
		}
		if (_playerDir == RIGHT)
		{
			KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "moveLeft", _imgKey, moveLeft, 4, 6, false);
			_animation = KEYANIMANAGER->findAnimation(_aniKey, "moveLeft");
		}
		if (_playerDir == TOP)
		{
			KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "upLeft", _imgKey, upLeft, 1, 6, false);
			_animation = KEYANIMANAGER->findAnimation(_aniKey, "upLeft");
		}
		if (_playerDir == BOTTOM)
		{
			KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "downLeft", _imgKey, downLeft, 1, 6, false);
			_animation = KEYANIMANAGER->findAnimation(_aniKey, "downLeft");
		}
		break;
	case JUMP:
		break;
	case ATK:
		break;
	case STATE_COUNT:
		break;
	default:
		break;
	}*/

	
	
	

	/*switch (_playerAction)
	{
	case LEFT:
		
	case RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "left", _imgKey, left, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "left");
		break;
	case UP_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "upLeft", _imgKey, upLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "upLeft");
		break;
	case UP_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "upLeft", _imgKey, upLeft, 1, 6, true);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "upLeft");
		break;
		break;
	case DOWN_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "downLeft", _imgKey, downLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "downLeft");
		break;
	case DOWN_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "downLeft", _imgKey, downLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "downLeft");
		break;
	case MOVE_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "moveLeft", _imgKey, moveLeft, 4, 5, true);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "moveLeft");
		break;
	case MOVE_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "moveLeft", _imgKey, moveLeft, 4, 5, true);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "moveLeft");
		break;

	case ATK_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "left", _imgKey, left, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "left");
		break;
	case ATK_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "left", _imgKey, left, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "left");
		break;
	case UP_ATK_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "upAtkLeft", _imgKey, upAtkLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "upAtkLeft");
		break;
	case UP_ATK_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "upAtkLeft", _imgKey, upAtkLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "upAtkLeft");
		break;
	case JUMP_ATK_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpLeft", _imgKey, jumpLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "jumpLeft");
		break;
	case JUMP_ATK_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpLeft", _imgKey, jumpLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "jumpLeft");
		break;
	case FALLING_ATK_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "fallingLeft", _imgKey, fallingLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "fallingLeft");
		break;
	case FALLING_ATK_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "fallingLeft", _imgKey, fallingLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "fallingLeft");
		break;
	
	case DOWN_ATK_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "downAtkLeft", _imgKey, downAtkLeft, 1, 1, true);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "downAtkLeft");
		break;
	case DOWN_ATK_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "downAtkLeft", _imgKey, downAtkLeft, 1, 1, true);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "downAtkLeft");
		break;
	case JUMP_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpLeft", _imgKey, jumpLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "jumpLeft");
		break;
	case JUMP_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpLeft", _imgKey, jumpLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "jumpLeft");
		break;
	case JUMP_UP_ATK_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpUpAtkLeft", _imgKey, jumpUpAtkLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "jumpUpAtkLeft");
		break;	
	case JUMP_UP_ATK_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpUpAtkLeft", _imgKey, jumpUpAtkLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "jumpUpAtkLeft");
		break;
	case FALLING_UP_ATK_LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "fallingUpAtkLeft", _imgKey, fallingUpAtkLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "fallingUpAtkLeft");
		break;
	case FALLING_UP_ATK_RIGHT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "fallingUpAtkLeft", _imgKey, fallingUpAtkLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "fallingUpAtkLeft");
		break;
	
	case LEFT_FALLING:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "fallingLeft", _imgKey, fallingLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "fallingLeft");
		break;
	case RIGHT_FALLING:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "fallingLeft", _imgKey, fallingLeft, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "fallingLeft");
		break;
	
	default:
		break;
	}*/
	

	//_animation = KEYANIMANAGER->findAnimation(_aniKey, "left");
	//_animation->start();
}

void player::aniStart(string aniKey)
{
	_animation = KEYANIMANAGER->findAnimation(_aniKey, aniKey);
	_animation->start();
}

void player::moveLeft()
{
	int probeFloorX = _playerRC.bottom / TILE_SIZE;
	int probeFloorY = _playerRC.bottom / TILE_SIZE;

	if ((_playerState == MOVE && _playerDir == LEFT) || (_prePlayerState == JUMP && _playerDir == LEFT))
	{
		_centerX -= _speed;
		//if (_map->getTile())
		{
		
		}

	}
	
}

void player::moveRight()
{
	/*if (_playerState != MOVE)
		return;*/
	if((_playerState == MOVE && _playerDir == RIGHT) ||(_prePlayerState == JUMP && _playerDir == RIGHT))
		_centerX += _speed;
}


void player::jump()
{
	//플레이어가 점프를 하면
	
	if (_playerState == JUMP)
	{
		//플레이어의 Y좌표를 점프 파워만큼 옮김

		//if (_jumpPower <= 0)
		//{
			_centerY -= TIMEMANAGER->getElapsedTime() * _jumpPower;

		//}
		//else if(_jumpPower > 0)
		//{
		//	_centerY -= TIMEMANAGER->getElapsedTime() * _jumpPower;
		//}
		_jumpPower -= TIMEMANAGER->getElapsedTime() * _gravity;
		//_gravity *= TIMEMANAGER->getElapsedTime();
		//점프를 시작한 순간부터 파워를 점점 깎아서 0으로 만들고
		

	}



}
