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
	_playerAction = RIGHT;
	animationSet();
	_animation->start();
	

	//_centerX = ; (20, 13) 인덱스에서 시작함
	_centerX = 20 * 40 + 20;
	_centerY = 13 * 40 + 20;
	
	_playerRC = { (float)(_centerX - PLAYER_WIDTH / 2)
				,(float)(_centerY - PLAYER_HEIGHT / 2)
				,(float)(_centerX + PLAYER_WIDTH / 2)
				,(float)(_centerY + PLAYER_HEIGHT / 2)};

	_isLeft = false;
	_isRight = false;
	_isIdle = true;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;
	
	inputKey();

	_playerRC = { (float)(_centerX - PLAYER_WIDTH / 2)
				,(float)(_centerY - PLAYER_HEIGHT / 2)
				,(float)(_centerX + PLAYER_WIDTH / 2)
				,(float)(_centerY + PLAYER_HEIGHT / 2) };
	KEYANIMANAGER->update(_aniKey);
}

void player::render()
{
	D2DMANAGER->drawRectangle(_playerRC);
	//맨 첫시작에 렌더할때는 
	if(!_isLeft && !_isRight && _isIdle)
		IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX(_playerRC.left, _playerRC.top, _animation);

	//왼쪽 방향의 액션일 때
	if ((_isLeft && _isIdle) || _isLeft)
		IMAGEMANAGER->findImage(_imgKey)->aniRender(_playerRC.left, _playerRC.top, _animation);
	//오른쪽 방향의 액션일 때
	if ((_isRight && _isIdle) || _isRight)
		IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX(_playerRC.left, _playerRC.top, _animation);
}

void player::inputKey()
{
	//움직이는 키
	//왼쪽 움직임
	

	//만약에 포탈 앞에서 아래키를누르면 씬이동(->이건 맵에서) todo
	//오른쪽 움직임
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) 
	{
		_isLeft = false;
		_isIdle = false;
		if(!(_playerAction == DOWN_RIGHT || _playerAction == UP_RIGHT))
			_centerX += _speed;
		_playerAction = MOVE_RIGHT;
		animationSet();
		if (!_isRight)
			_animation->start();
		_isRight = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_isIdle = true;
		_playerAction = RIGHT;
		animationSet();
		_animation->start();
	}

	//위를 바라보는 키 누르면
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_playerAction == LEFT || _playerAction == MOVE_LEFT)
		{
			_playerAction = UP_LEFT;
			animationSet();
		}
		if (_playerAction == RIGHT || _playerAction == MOVE_RIGHT)
		{
			_playerAction = UP_RIGHT;
			animationSet();
		}
		//if (_playerAction == JUMP_LEFT)
		//{
		//	_
		//}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_playerAction == UP_LEFT) 
		{
			_playerAction = LEFT;
			animationSet();
		}
		if (_playerAction == UP_RIGHT)
		{
			_playerAction = RIGHT;
			animationSet();
		}
	}

	//아래방향 키 누르면
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//애니메이션 관련 세팅
		if (_playerAction == LEFT || _playerAction == MOVE_LEFT)
		{
			_playerAction = DOWN_LEFT;
			animationSet();
		}
		if (_playerAction == RIGHT || _playerAction == MOVE_RIGHT)
		{
			_playerAction = DOWN_RIGHT;
			animationSet();
		}
		// 아이템이나 문 앞에서 눌렀을때 실행문
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_playerAction == LEFT || _playerAction == DOWN_LEFT)
		{
			_playerAction = LEFT;
			animationSet();
		}
		if (_playerAction == RIGHT || _playerAction == DOWN_RIGHT)
		{
			_playerAction = RIGHT;
			animationSet();
		}
	}

	//아래의 각 상태에서 X버튼과 Z버튼을 누르면
	switch (_playerAction)
	{
	case LEFT:		//왼쪽 아이들
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_isRight = false;
			_isIdle = false;
			if (!(_playerAction == DOWN_LEFT || _playerAction == UP_LEFT))
				_centerX -= _speed;
			_playerAction = MOVE_LEFT;
			animationSet();
			if (!_isLeft)
				_animation->start();
			_isLeft = true;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_isIdle = true;
			_playerAction = LEFT;
			animationSet();
			_animation->start();
		}



		if (KEYMANAGER->isStayKeyDown('X'))
		{
			_playerAction = JUMP_LEFT;
			animationSet();
			_animation->start();
		}
		//공격
		if (KEYMANAGER->isOnceKeyDown('Z'))  
			_playerAction = ATK_LEFT;
		break;
	case RIGHT:
		if (KEYMANAGER->isStayKeyDown('X'))
		{
			_playerAction = JUMP_RIGHT;
			animationSet();
			_animation->start();
		}
		//공격
		if (KEYMANAGER->isOnceKeyDown('Z'))
			_playerAction = ATK_RIGHT;
		break;
	case UP_LEFT:
		break;
	case UP_RIGHT:
		break;
	case DOWN_LEFT:
		break;
	case DOWN_RIGHT:
		break;
	case MOVE_LEFT:
		break;
	case MOVE_RIGHT:
		break;
	case ATK_LEFT:
		break;
	case ATK_RIGHT:
		break;
	case UP_ATK_LEFT:
		break;
	case UP_ATK_RIGHT:
		break;
	case JUMP_ATK_LEFT:
		break;
	case JUMP_ATK_RIGHT:
		break;
	case FALLING_ATK_LEFT:
		break;
	case FALLING_ATK_RIGHT:
		break;
	case DOWN_ATK_LEFT:
		break;
	case DOWN_ATK_RIGHT:
		break;
	case JUMP_LEFT:
		//키에서 손을 땠을 때
		if (KEYMANAGER->isOnceKeyUp('X'))
		{	
			_playerAction = LEFT_FALLING;
			animationSet();
			_animation->start();	
		}
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{

		}
		break;
	case JUMP_RIGHT:
		break;
	case JUMP_UP_ATK_LEFT:
		break;
	case JUMP_UP_ATK_RIGHT:
		break;
	case FALLING_UP_ATK_LEFT:
		break;
	case FALLING_UP_ATK_RIGHT:
		break;
	case LEFT_FALLING:
		break;
	case RIGHT_FALLING:
		break;
	case DIR_COUNT:
		break;
	default:
		break;
	}


	//공격키 & 점프키
	switch (_playerAction)
	{
	case LEFT:
		//점프
		//if (KEYMANAGER->isStayKeyDown('X'))
		//{
		//	_playerAction = JUMP_LEFT;
		//	animationSet();
		//	_animation->start();
		//}
		////공격
		//if (KEYMANAGER->isOnceKeyDown('Z'))  _playerAction = ATK_LEFT; 
		//break;
	case UP_LEFT:
		if (KEYMANAGER->isOnceKeyDown('X')) { _playerAction = JUMP_LEFT; }
		if (KEYMANAGER->isOnceKeyDown('Z')) _playerAction = UP_ATK_LEFT; 
		break;
	case UP_RIGHT:
		if (KEYMANAGER->isOnceKeyDown('X')) { _playerAction = JUMP_RIGHT; }
		if (KEYMANAGER->isOnceKeyDown('Z'))	_playerAction = UP_ATK_RIGHT;
		break;

	case RIGHT:
		if (KEYMANAGER->isOnceKeyDown('X')) { _playerAction = JUMP_RIGHT; }
		if (KEYMANAGER->isOnceKeyDown('Z')) _playerAction = ATK_RIGHT; 
		break;
	case DOWN_LEFT:
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_playerAction = JUMP_LEFT;
		}
		if (KEYMANAGER->isOnceKeyDown('Z') && (_playerAction == JUMP_LEFT || _playerAction == JUMP_RIGHT)) 
		{
			if (_playerAction == JUMP_LEFT)
				_playerAction = DOWN_ATK_LEFT;
			if (_playerAction == JUMP_RIGHT)
				_playerAction = DOWN_ATK_RIGHT;
		}
		break;
	case DOWN_RIGHT:
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			if (_playerAction == RIGHT)
				_playerAction = JUMP_RIGHT;
		}

		break;
	case JUMP_LEFT:
		////키에서 손을 땠을 때
		//if (KEYMANAGER->isOnceKeyUp('X'))
		//{
		//	if (_playerAction == JUMP_LEFT)
		//	{
		//		_playerAction = LEFT_FALLING;
		//		animationSet();
		//		_animation->start();
		//	}
		//}
		//중력 값이 점프 파워를 0으로 만들었을 때도
		//떨어지는 모션이 나와야함.
		//TODO
		break;
	case LEFT_FALLING:
		//다떨어지고나서 바닥에 찾기하면 LEFT 상태로 바꿔야함.

		break;

	default:
		break;
	}

}

void player::animationSet()
{
	_imgKey = "quote";
	_aniKey = "quoteAni";

	int left[] = { 0 };
	int upLeft[] = { 7 };
	int downLeft[] = { 8 };
	int moveLeft[] = { 0, 1, 2, 3 };
	int jumpLeft[] = { 3 };


	int downAtkLeft[] = { 9 };


	int fallingLeft[] = { 4 };

	int upAtkLeft[] = { 7 };
	int jumpUpAtkLeft[] = { 5 };
	int fallingUpAtkLeft[] = { 6 };

	//int jumpUpAtkLeft[] = {};




	
	IMAGEMANAGER->addFrameImage(_imgKey, L"image/quote.png", 440, 40, 11, 1);

	KEYANIMANAGER->addAnimationType(_aniKey);
	switch (_playerAction)
	{
	case LEFT:
		KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "left", _imgKey, left, 1, 6, false);
		_animation = KEYANIMANAGER->findAnimation(_aniKey, "left");
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
	}
	//switch (_playerAction)
	//{
	//case LEFT:				//왼쪽 아이들
	//	
	//	break;	
	//case UP_LEFT:			//왼쪽에서 위를 볼 때
	//	
	//	break;
	//case UP_RIGHT:			//오른쪽에서 위를 볼 때
	//	
	//	break;
	//case RIGHT:				//오른쪽 아이들
	//	
	//	break;
	//case DOWN_LEFT:			//왼쪽에서 배경을 바라볼 때
	//	
	//	break;
	//case DOWN_RIGHT:		//오른쪽에서 배경을 바라볼 때
	//	
	//	break;
	//case MOVE_LEFT:			//왼쪽으로 움직일 때
	//	
	//	break;
	//case MOVE_RIGHT:		//오른쪽으로 움직일 때
	//	
	//	break;
	//case ATK_LEFT:			//왼쪽 공격
	//	
	//	break;
	//case UP_ATK_LEFT:


	//	break;
	//case UP_ATK_RIGHT:
	//	break;
	//case ATK_RIGHT:
	//	
	//	break;
	//case DOWN_ATK_LEFT:
	//	
	//case DOWN_ATK_RIGHT:
	//	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "downAtkLeft", _imgKey, downAtkLeft, 1, 1, true);
	//	_animation = KEYANIMANAGER->findAnimation(_aniKey, "downAtkLeft");
	//	break;
	//case JUMP_LEFT:
	//	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpLeft", _imgKey, jumpLeft, 1, 1, true);
	//	_animation = KEYANIMANAGER->findAnimation(_aniKey, "jumpLeft");
	//	break;
	//case JUMP_RIGHT:
	//	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "jumpLeft", _imgKey, jumpLeft, 1, 1, true);
	//	_animation = KEYANIMANAGER->findAnimation(_aniKey, "jumpLeft");
	//	break;
	//case LEFT_FALLING:
	//	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "fallingLeft", _imgKey, fallingLeft, 1, 1, true);
	//	_animation = KEYANIMANAGER->findAnimation(_aniKey, "fallingLeft");
	//	break;
	//case RIGHT_FALLING:
	//	KEYANIMANAGER->addArrayFrameAnimation(_aniKey, "fallingLeft", _imgKey, fallingLeft, 1, 1, true);
	//	_animation = KEYANIMANAGER->findAnimation(_aniKey, "fallingLeft");
	//	break;
	//case DIR_COUNT:
	//	break;
	//default:
	//	break;
	//}

	//_animation = KEYANIMANAGER->findAnimation(_aniKey, "left");
	//_animation->start();
}
