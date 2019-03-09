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

	//����ȭ�� �÷��̾��� ���� ����
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
	//�� ù���ۿ� �����Ҷ��� 
	//if(!_isLeft && !_isRight && _isIdle)
	//	IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX(_playerRC.left, _playerRC.top, _animation);
	//
	////���� ������ �׼��� ��
	//if ((_isLeft && _isIdle) || _isLeft)
	//	IMAGEMANAGER->findImage(_imgKey)->aniRender(_playerRC.left, _playerRC.top, _animation);
	////������ ������ �׼��� ��
	//if ((_isRight && _isIdle) || _isRight)
	//	IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX(_playerRC.left, _playerRC.top, _animation);
}

void player::inputKey()
{
	//�����̴� Ű
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
		//����Ű
		if (KEYMANAGER->isStayKeyDown('X'))
		{
			_playerState = JUMP;
			_jumpState = JUMP_RISE;
			_jumpPower = JUMP_POWER;
			
			//���࿡ ���� �Ŀ��� �߷¿� ���� 0�� �Ǹ� 
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
		//����Ű
		if (KEYMANAGER->isStayKeyDown('X'))
		{
			_playerState = JUMP;
			_jumpState = JUMP_RISE;
			
			//���࿡ ���� �Ŀ��� �߷¿� ���� 0�� �Ǹ� 
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
	//		//���� ������ �����̳� �������̳Ŀ� ���� ���� ������ �÷��̾��� ������ �޶���
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


	//����
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
	////������
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
	////���� �ٶ󺸱�
	//if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//	_prePlayerState = _playerState;
	//	_prePlayerDir = _playerDir;

	//	_playerState = IDLE;
	//	_playerDir = TOP;
	//}
	//
	////�Ʒ�Ű
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//	_prePlayerState = _playerState;
	//	_prePlayerDir = _playerDir;
	//	//���࿡ ���� ������ �����̰� ���� ������ BOTTOM �̸� ���ʿ��� ������ �̹����� ���;���
	//	_playerDir = BOTTOM;
	//	//1. ������ �ƴ� ���� ���� ��(�����̴� ���̰ų� ���̵� ���¿��� ��)
	//	if (_playerState == MOVE || _playerState == IDLE)
	//	{
	//		_playerState = IDLE;
	//		// 1-1.���࿡ ��Ż�� ������ �� ��ȯ

	//		//1-2.���࿡ �������� ������ �������� �ֿ�
	//	}
	//	//����
	//	/*
	//	//2. ������ ���� �Ʒ��������� ��������
	//	//if (_playerState == JUMP)
	//	//{
	//	//
	//	//}
	//	// 3. ������ ���� �Ʒ��������� ���� ��
	//	//if(_playerState == ATK)
	//	//{
	//	//	//_playerDir
	//	//}
	//	*/
	//}
	//
	////����Ű
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
	////����Ű
	//if (KEYMANAGER->isOnceKeyDown('X'))
	//{
	//	_playerState = JUMP;
	//	_jumpState = JUMP_RISE;
	//	//���࿡ ���� �Ŀ��� �߷¿� ���� 0�� �Ǹ� 
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
	//�÷��̾ ������ �ϸ�
	
	if (_playerState == JUMP)
	{
		//�÷��̾��� Y��ǥ�� ���� �Ŀ���ŭ �ű�

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
		//������ ������ �������� �Ŀ��� ���� ��Ƽ� 0���� �����
		

	}



}
