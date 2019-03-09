#pragma once
#include "gameNode.h"

#define	 PLAYER_WIDTH	26
#define	 PLAYER_HEIGHT	36

#define  PLAYER_SPEED	200.f
#define  JUMP_POWER		350.f	
#define  GRAVITY		350.f



enum PLAYER_STATE
{
	IDLE,
	MOVE,		
	JUMP,		
	ATK,

	STATE_COUNT
};
enum PLAYER_DIRECTION
{
	LEFT,
	RIGHT,
	TOP,
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
//	//아래 키 누른채로 공격
//	DOWN_ATK_LEFT,
//	DOWN_ATK_RIGHT,
//
//	JUMP_LEFT,
//	JUMP_RIGHT,
//	
//	//위 누른채로 공격
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

	D2D1_RECT_F			_playerRC;		//쿼트 렉트
	float				_centerX;
	float				_centerY;
	float				_speed;

	float				_jumpPower;
	float				_gravity;

	
	PLAYER_STATE		_playerState;		//쿼트의 상태 enum
	PLAYER_STATE		_prePlayerState;		//이전의 상태를 저장할 enum 변수

	PLAYER_DIRECTION	_prePlayerDir;		//이전의 방향을 저장할 enum 변수
	PLAYER_DIRECTION	_playerDir;			//쿼트의 방향
	JUMP_STATE			_jumpState;			//점프했을 때 상태
	UINT				_tileX;				//쿼트가 현재 위치하고있는 타일의 번호
	UINT				_tileY;				//쿼트가 현재 위치하고있는 타일의 번호
		
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

	void moveLeft();
	void moveRight();
	void jump();


	void setMapDataMemoryAdressLink(mapData* map) { _map = map; }

	float getPosX() { return _centerX; }
	float getPosY() { return _centerY; }


};



