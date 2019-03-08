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
	

	//_centerX = ; (20, 13) �ε������� ������
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
	//�� ù���ۿ� �����Ҷ��� 
	if(!_isLeft && !_isRight && _isIdle)
		IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX(_playerRC.left, _playerRC.top, _animation);

	//���� ������ �׼��� ��
	if ((_isLeft && _isIdle) || _isLeft)
		IMAGEMANAGER->findImage(_imgKey)->aniRender(_playerRC.left, _playerRC.top, _animation);
	//������ ������ �׼��� ��
	if ((_isRight && _isIdle) || _isRight)
		IMAGEMANAGER->findImage(_imgKey)->aniRenderReverseX(_playerRC.left, _playerRC.top, _animation);
}

void player::inputKey()
{
	//�����̴� Ű
	//���� ������
	

	//���࿡ ��Ż �տ��� �Ʒ�Ű�������� ���̵�(->�̰� �ʿ���) todo
	//������ ������
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

	//���� �ٶ󺸴� Ű ������
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

	//�Ʒ����� Ű ������
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//�ִϸ��̼� ���� ����
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
		// �������̳� �� �տ��� �������� ���๮
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

	//�Ʒ��� �� ���¿��� X��ư�� Z��ư�� ������
	switch (_playerAction)
	{
	case LEFT:		//���� ���̵�
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
		//����
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
		//����
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
		//Ű���� ���� ���� ��
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


	//����Ű & ����Ű
	switch (_playerAction)
	{
	case LEFT:
		//����
		//if (KEYMANAGER->isStayKeyDown('X'))
		//{
		//	_playerAction = JUMP_LEFT;
		//	animationSet();
		//	_animation->start();
		//}
		////����
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
		////Ű���� ���� ���� ��
		//if (KEYMANAGER->isOnceKeyUp('X'))
		//{
		//	if (_playerAction == JUMP_LEFT)
		//	{
		//		_playerAction = LEFT_FALLING;
		//		animationSet();
		//		_animation->start();
		//	}
		//}
		//�߷� ���� ���� �Ŀ��� 0���� ������� ����
		//�������� ����� ���;���.
		//TODO
		break;
	case LEFT_FALLING:
		//�ٶ��������� �ٴڿ� ã���ϸ� LEFT ���·� �ٲ����.

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
	//case LEFT:				//���� ���̵�
	//	
	//	break;	
	//case UP_LEFT:			//���ʿ��� ���� �� ��
	//	
	//	break;
	//case UP_RIGHT:			//�����ʿ��� ���� �� ��
	//	
	//	break;
	//case RIGHT:				//������ ���̵�
	//	
	//	break;
	//case DOWN_LEFT:			//���ʿ��� ����� �ٶ� ��
	//	
	//	break;
	//case DOWN_RIGHT:		//�����ʿ��� ����� �ٶ� ��
	//	
	//	break;
	//case MOVE_LEFT:			//�������� ������ ��
	//	
	//	break;
	//case MOVE_RIGHT:		//���������� ������ ��
	//	
	//	break;
	//case ATK_LEFT:			//���� ����
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
