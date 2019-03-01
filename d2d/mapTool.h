#pragma once
#include "gameNode.h"
#include "button.h"
#include "tileNode.h"
#include <functional>

#define TILE_SIZE			40

#define MAP_WIDTH_NUM		10
#define MAP_HEIGHT_NUM		10

#define MAP_WIDTH_SIZE		(TILE_SIZE * MAP_WIDTH_NUM)
#define MAP_HEIGHT_SIZE		(TILE_SIZE * MAP_HEIGHT_NUM)

#define SAMPLE_DISTANCE_Y		50			//����Ÿ�� ������ ������

#define SAMPLE_WIDTH_NUM	6
#define SAMPLE_HEIGHT_NUM	10
#define SAMPLE_START_POSX	(WINSIZEX - (TILE_SIZE * SAMPLE_WIDTH_NUM + TILE_SIZE))

#define CAMERA_SHOW_RANGE_W	(19 * TILE_SIZE)		//ī�޶� ���� X��
#define CAMERA_SHOW_RANGE_H (17 * TILE_SIZE)		//ī�޶� ���� Y��

static button*		_sampleNextPageButton;
static button*		_samplePrePageButton;
static button*		_increaseButton;
static button*		_decreaseButton;
static button*		_selectXButton;
static button*		_selectYbutton;
static button*		_objButton;

static bool			_isSelectX;			//x�� ������ �����߳�?
static bool			_isSelectY;			//y�� ������ �����߳�?

static UINT			TILEX;				//���� ��ü Ÿ�� ���� ����
static UINT			TILEY;				//���� ��ü Ÿ�� ���� ����

static int			_boolCountX;			//toggleŰ�� ���鶧 ����� ����
static int			_boolCountY;

static int			_samplePage;
static bool			_isClick;			//���� Ÿ���� Ŭ��������

struct tagPickSample
{
	UINT tileImgPage;
	int indX;
	int indY;
};


class mapTool :	public gameNode
{
private:
	POINTF						_pt;				//���� ����ϴ� �뵵�� _pt
	float						_getAngleF;			//���� ���� �����ϴ� ����
	int							_calculateNum;		//���� ����Ҷ� ù��° Ŭ��, �ι�° Ŭ�� ������ int ����
	D2D1_RECT_F					_loopRect;			//���� ���� �� �� �ʿ��� ��Ʈ
	float						_loopX;				//���� ���� �ӵ�

	image*						_sampleImg[SAMPLE_TILE_IMAGEKEY_COUNT];
	
	vector<vector<tagTile*>>	_vvTile;

	UINT						_reSizeX;			//�� ������ ���� �� �� ����� ������ ����
	UINT						_reSizeY;			//�� ������ ���� �� �� ����� ������ ����

	tagPickSample				_pickSample;		//������ ������ �ε�����ȣ�� ����ؼ� �־��� ����

	bool						_isShift;			//shift Ű�� ���� ���³�?
	bool						_isClickObj;		//object ��ư�� ������?
	UINT						_objSelectCount;	//������Ʈ Ȱ��ȭ �ƴ��� üũ�� ī��Ʈ�� ����



public:
	mapTool();
	~mapTool();

	HRESULT init();
	void update();
	void release();
	void render();
	void calculateAngle();

	static void cbChangeNextSample();
	static void cbChangePreSample();

	static void cbSelectX();
	static void cbSelectY();

	void mapToolSetting();		//������ �⺻ Ÿ�ϵ� �����ϴ� �Լ�
	
	void pickSample();			//���� Ÿ���� �����ϴ� �Լ�
	void drawMap();				//������ ������ �ʿ� �׸��� �Լ�
	
	void save();				
	void load();				


	void setAttribute(UINT samplePage, UINT frameX, UINT frameY);

	function<void(void)> _increaseMap;
	function<void(void)> _decreaseMap;

	function<void(void)> _selectObj;

	void increaseX();
	void increaseY();
	void decreaseX();
	void decreaseY();

	void increaseMap();
	void decreaseMap();

	void selectObj();


};

