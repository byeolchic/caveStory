#pragma once
//#define SAMPLE_NUM			9
#define TILE_SIZE			40

//TILE STATE							Ÿ���� �Ӽ�
#define	TS_NONE					0X00000000UL
#define TS_BACK					0X00000001UL		//���Ÿ��
#define TS_UNMOVE				0X00000002UL		//��� ���ϴ� Ÿ��
#define TS_WALL					0X00000004UL		//��
#define TS_SLOPE				0X00000008UL		//����
#define TS_WATER				0X00000010UL		//��
#define TS_DIALOGUE				0X00000020UL		//���̾�αװ� �ߴ� ��

//#define TS_WATER_SLOPE			0X00000020	//������ ����
#define TS_CEILING				0X00000020UL		//õ��
#define TS_ZORDER				0X00000040UL		//��Ʈ������ tile
#define TS_THORN_BUSH			0X00000080UL		//������ �ٷ� �״� ����
//#define TS_CHAIN				0X00000100UL		//��罽
#define TS_POTAL				0X00000200UL		//��Ż
#define TS_DOOR					0X00000400UL		//��

//============= << ������ ������Ʈ�� ��쿡�� �ʿ� ����� frame���� ����ϵ��� �غ��� >> ===============
#define TS_FRAME				0X00100000UL		//�������� �ִ� tile ��
#define TS_BOX					0X00200000UL		//����
#define TS_DOOR					0X00400000UL		//���� �ִ� ��
#define TS_LIFE_CAPSULE			0X00800000UL		//������ ĸ��
#define TS_LIFE_CHARGE			0X01000000UL		//������ ������
#define TS_SAVE					0X02000000UL		//���̺� ������Ʈ



enum MAP_TYPE
{
	//MAP_TYPE_TOWN,
	//MAP_TYPE_GUN_PLACE,
	//MAP_TYPE_CEMETRY,
	//MAP_TYPE_POWER_ROOM
	MAP_TYPE_NONE,
	MAP_TYPE_ONE,
	MAP_TYPE_TWO,
	MAP_TYPE_THREE,
	MAP_TYPE_FOUR,
	MAP_TYPE_FIVE,


	MAP_TYPE_COUNT
};

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
		//angle(NULL)
	{};
	~tagTile() {};
public:
	UINT backgroundIndex;	//��׶����� �̹��� �ε���
	UINT backgroundX;		//��׶��� frameX
	UINT backgroundY;		//��׶��� frameY

	UINT tileImgIndex;		//����Ÿ���� �ε������� ���� �����ؾ� ���� �������� �ѱ涧 ���� �ٲ�� ���� ����
	UINT terrainFrameX;		//�ϴ� 0���� �ʱ�ȭ
	UINT terrainFrameY;		//�ϴ� 0���� �ʱ�ȭ

	UINT objImgIndex;		//������Ʈ�� �̹��� �ε���
	UINT objectFrameX;		//�ϴ� 0���� �ʱ�ȭ
	UINT objectFrameY;		//�ϴ� 0���� �ʱ�ȭ


	UINT zOrderFrameY;		//�ϴ� 0���� �ʱ�ȭ
	UINT zOrderFrameX;		//�ϴ� 0���� �ʱ�ȭ
	DWORD attr;				//�ϴ� 0���� �ʱ�ȭ

	//float	angle;			//�ϴ� 0���� �ʱ�ȭ
	bool isBackground;		//��׶����
	bool isObj;				//������Ʈ��?
	bool isZorder;			//��Ʈ������?

	void setTile(tagTile tile)
	{
		if (tile.backgroundIndex > 0)
			backgroundIndex = tile.backgroundIndex;
		backgroundX = tile.backgroundX;
		backgroundY = tile.backgroundY;
		if (tile.tileImgIndex > 0)
			tileImgIndex = tile.tileImgIndex;
		terrainFrameX = tile.terrainFrameX;
		terrainFrameY = tile.terrainFrameY;
		if (tile.objImgIndex > 0)
			objImgIndex = tile.objImgIndex;
		objectFrameX = tile.objectFrameX;
		objectFrameY = tile.objectFrameY;

		zOrderFrameX = tile.zOrderFrameX;
		zOrderFrameY = tile.zOrderFrameY;
		attr = tile.attr;

		isBackground = tile.isBackground;
		isObj = tile.isObj;
		isZorder = tile.isZorder;

	}


};