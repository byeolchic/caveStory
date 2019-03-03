#pragma once
//#define SAMPLE_NUM			9

//TILE STATE							타일의 속성
#define	TS_NONE					0X00000000
#define TS_BACK					0X00000001		// 배경타일
#define TS_FLOOR				0X00000002		// 바닥
#define TS_WALL					0X00000004		// 벽
#define TS_SLOPE				0X00000008		// 경사길
#define TS_WATER				0X00000010		// 물
//#define TS_WATER_SLOPE			0X00000020		// 물에서 경사길
#define TS_CEILING				0X00000020		// 천장
#define TS_ZORDER				0X00000040		// 제트오더용 tile
#define TS_THORN_BUSH			0X00000080		// 닿으면 바로 죽는 덤불
#define TS_CHAIN				0X00000100		// 쇠사슬
#define TS_POTAL				0X00000200		// 포탈


//============= << 프레임 오브젝트의 경우에는 맵에 찍고나서 frame으로 출력하도록 해보자 >> ===============
#define TS_FRAME				0X00100000		//프레임이 있는 tile 들
#define TS_BOX					0X00200000		//상자
#define TS_DOOR					0X00400000		//눈이 있는 문
#define TS_LIFE_CAPSULE			0X00800000		//라이프 캡슐
#define TS_LIFE_CHARGE			0X01000000		//라이프 충전기
#define TS_SAVE					0X02000000		//세이브 오브젝트


enum SAMPLE_TILE_IMAGE_KEY
{
	SAMPLE_TILE_NONE,
	SAMPLE_TILE_IMAGEKEY_01,
	SAMPLE_TILE_IMAGEKEY_02,
	SAMPLE_TILE_IMAGEKEY_03,
	SAMPLE_TILE_IMAGEKEY_04,
	SAMPLE_TILE_IMAGEKEY_05,
	SAMPLE_TILE_IMAGEKEY_06,
	SAMPLE_TILE_IMAGEKEY_07,
	SAMPLE_TILE_IMAGEKEY_08,
	SAMPLE_TILE_IMAGEKEY_09,
	
	SAMPLE_TILE_IMAGEKEY_COUNT

};

static string  SAMPLETILENAME[SAMPLE_TILE_IMAGEKEY_COUNT] = { "none", "tile_01", "tile_02", "tile_03", "tile_04", "tile_05","tile_06","tile_07","tile_08","tile_09" };

typedef class tagTile
{
public:
	tagTile() :
				backgroundIndex(NULL),
				backgroundX(NULL),
				backgroundY(NULL),

				tileImgIndex(1),
				terrainFrameX(NULL),
				terrainFrameY(NULL),

				objImgIndex(NULL),
				objectFrameX(NULL),
				objectFrameY(NULL),
		
				zOrderFrameX(NULL),
				zOrderFrameY(NULL),
				attr(NULL)
	{};
	~tagTile() {};
public:
	UINT backgroundIndex;	//백그라운드의 이미지 인덱스
	UINT backgroundX;		//백그라운드 frameX
	UINT backgroundY;		//백그라운드 frameY

	UINT tileImgIndex;		//샘플타일의 인덱스까지 같이 저장해야 샘플 페이지를 넘길때 같이 바뀌는 일이 없당
	UINT terrainFrameX;		//일단 0으로 초기화
	UINT terrainFrameY;		//일단 0으로 초기화
	
	UINT objImgIndex;		//오브젝트의 이미지 인덱스
	UINT objectFrameX;		//일단 0으로 초기화
	UINT objectFrameY;		//일단 0으로 초기화
	
	UINT zOrderFrameY;		//일단 0으로 초기화
	UINT zOrderFrameX;		//일단 0으로 초기화
	DWORD attr;				//일단 0으로 초기화

	bool isBackground;		//백그라운드냐
	bool isObj;				//오브젝트냐?
	bool isZorder;			//제트오더냐?
};