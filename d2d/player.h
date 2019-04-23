#pragma once
#include "gameNode.h"

#define	 PLAYER_WIDTH	26
#define	 PLAYER_HEIGHT	36

#define  PLAYER_SPEED	200.f
#define  JUMP_POWER		650.f	
#define  GRAVITY		348.f



enum PLAYER_STATE
{
	IDLE,
	MOVE,
	JUMP,
	ATK,
	JUMP_MOVE,

	STATE_COUNT
};
enum PLAYER_DIRECTION
{
	LEFT,
	RIGHT,
	LEFT_TOP,
	RIGHT_TOP,
	BOTTOM,

	DIRECTION_COUNT
};
enum JUMP_STATE
{
	JUMP_RISE,
	JUMP_FALL,

	JUMP_STATE_COUNT
};
//enum PLAYER_ACTION
//{
//	IDLE,
//
//	UP_LEFT,
//	UP_RIGHT,
//	DOWN_LEFT,
//	DOWN_RIGHT,
//
//	MOVE_LEFT,
//	MOVE_RIGHT,
//
//	ATK_LEFT,
//	ATK_RIGHT,
//
//	UP_ATK_LEFT,
//	UP_ATK_RIGHT,
//	JUMP_ATK_LEFT,
//	JUMP_ATK_RIGHT,
//	FALLING_ATK_LEFT,
//	FALLING_ATK_RIGHT,
//
//	//�Ʒ� Ű ����ä�� ����
//	DOWN_ATK_LEFT,
//	DOWN_ATK_RIGHT,
//
//	JUMP_LEFT,
//	JUMP_RIGHT,
//	
//	//�� ����ä�� ����
//	JUMP_UP_ATK_LEFT,
//	JUMP_UP_ATK_RIGHT,
//	FALLING_UP_ATK_LEFT,
//	FALLING_UP_ATK_RIGHT,
//
//	LEFT_FALLING,
//	RIGHT_FALLING,
//
//	DIR_COUNT
//};
//
//enum DIR
//{
//	LEFT,
//	RIGHT,
//	UP,
//	DOWN
//};
//enum JUMP
//{
//	RISE,
//	FALLING
//
//
//};
//
//enum ATK
//{
//
//};

class mapData;
class player : public gameNode
{
	mapData*			_map;

	animation*			_animation;
	
	const char*			_imgKey;
	const char*			_aniKey;

	D2D1_RECT_F			_playerRC;		//��Ʈ ��Ʈ
	D2D1_RECT_F			_probeRcLeft;
	D2D1_RECT_F			_probeRcTop;
	D2D1_RECT_F			_probeRcRight;
	D2D1_RECT_F			_probeRcBottom;



	float				_posX;
	float				_posY;
	float				_plLeft;
	float				_plTop;
	float				_speed;

	float				_slopeAngle;
	float				_jumpPower;
	float	_tempColY;
	float				_gravity;

	UINT				_tileX;				//��Ʈ�� ���� ��ġ�ϰ��ִ� Ÿ���� ��ȣ
	UINT				_tileY;				//��Ʈ�� ���� ��ġ�ϰ��ִ� Ÿ���� ��ȣ
	
	PLAYER_STATE		_playerState;		//��Ʈ�� ���� enum
	//PLAYER_STATE		_prePlayerState;	//������ ���¸� ������ enum ����

	//PLAYER_DIRECTION	_prePlayerDir;		//������ ������ ������ enum ����
	PLAYER_DIRECTION	_playerDir;			//��Ʈ�� ����
	JUMP_STATE			_jumpState;			//�������� �� ����
	bool				_haveSignal;		//Ű�� �ԷµǾ��ִ� �������� üũ�� �Һ���
	
	//bool				_isLeft;
	//bool				_isRight;	
	//bool				_isIdle;

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void inputKey();
	void animationSet();
	void aniStart(string aniKey);

	void gravity();
	void collisionHead();
	void jump();


	void setMapDataMemoryAdressLink(mapData* map) { _map = map; }

	float getPosX() { return _plLeft; }
	float getPosY() { return _plTop; }


};



