#pragma once
#include "gameNode.h"

#define	 PLAYER_WIDTH	26
#define	 PLAYER_HEIGHT	36

#define  PLAYER_SPEED	200.f




class mapData;

enum PLAYER_ACTION
{
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,

	MOVE_LEFT,
	MOVE_RIGHT,

	ATK_LEFT,
	ATK_RIGHT,

	UP_ATK_LEFT,
	UP_ATK_RIGHT,
	JUMP_ATK_LEFT,
	JUMP_ATK_RIGHT,
	FALLING_ATK_LEFT,
	FALLING_ATK_RIGHT,



	//아래 키 누른채로 공격
	DOWN_ATK_LEFT,
	DOWN_ATK_RIGHT,

	JUMP_LEFT,
	JUMP_RIGHT,
	
	//위 누른채로 공격
	JUMP_UP_ATK_LEFT,
	JUMP_UP_ATK_RIGHT,
	FALLING_UP_ATK_LEFT,
	FALLING_UP_ATK_RIGHT,

	LEFT_FALLING,
	RIGHT_FALLING,

	DIR_COUNT
};

class player : public gameNode
{
	animation*			_animation;
	
	const char*			_imgKey;
	const char*			_aniKey;


	mapData*			_map;
	D2D1_RECT_F			_playerRC;		//쿼트 렉트

	float				_centerX;
	float				_centerY;

	float				_speed;
	
	PLAYER_ACTION		_playerAction;		//쿼트의 액션 enum
	bool				_isLeft;
	bool				_isRight;
	bool				_isIdle;

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void inputKey();
	void animationSet();
	//void jump();


	void setMapDataMemoryAdressLink(mapData* map) { _map = map; }

	float getPosX() { return _centerX; }
	float getPosY() { return _centerY; }


};

