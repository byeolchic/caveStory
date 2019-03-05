#pragma once
#include "gameNode.h"
#include "button.h"
#include "tileNode.h"
#include <functional>

#define TILE_SIZE			40
#define BACKGROUND_IDX_NUM	5
#define BACKGROUND_SIZE		(TILE_SIZE	* BACKGROUND_IDX_NUM)

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

static bool			_isSelectX;			//x�� ������ �����߳�?
static bool			_isSelectY;			//y�� ������ �����߳�?

static UINT			TILEX;				//���� ��ü Ÿ�� ���� ����
static UINT			TILEY;				//���� ��ü Ÿ�� ���� ����

static int			_boolCountX;			//toggleŰ�� ���鶧 ����� ����
static int			_boolCountY;

static int			_samplePage;
static bool			_isClick;			//���� Ÿ���� Ŭ��������
static bool			_isBackground;		//��׶�����Ÿ���� ���������� �ʿ��� ���

//�� Ÿ���� ����
static UINT						_mapType;								//���� Ÿ��



struct tagPickSample
{
	UINT tileImgPage;
	int indX;
	int indY;
};


class mapTool :	public gameNode
{
private:
	button*		_sampleNextPageButton;
	button*		_samplePrePageButton;
	button*		_increaseButton;
	button*		_decreaseButton;
	button*		_selectXButton;
	button*		_selectYbutton;
	button*		_objButton;
	
	//������ �� ����� ��ư
	//���� Ÿ���� ���� ��ư
	button*		_mapOne;
	button*		_mapTwo;
	button*		_mapThree;
	button*		_mapFour;
	button*		_mapFive;
	//�����ư
	button*		_saveButton;
	button*		_loadButton;
	
	POINTF						_pt;									//���� ����ϴ� �뵵�� _pt
	float						_getAngleF;								//���� ���� �����ϴ� ����
	int							_calculateNum;							//���� ����Ҷ� ù��° Ŭ��, �ι�° Ŭ�� ������ int ����
	D2D1_RECT_F					_loopRect;								//���� ���� �� �� �ʿ��� ��Ʈ
	float						_loopX;									//���� ���� �ӵ�

	image*						_sampleImg[SAMPLE_TILE_IMAGEKEY_COUNT];
	
	vector<vector<tagTile*>>	_vvTile;

	UINT						_reSizeX;								//�� ������ ���� �� �� ����� ������ ����
	UINT						_reSizeY;								//�� ������ ���� �� �� ����� ������ ����

	tagPickSample				_pickSample;							//������ ������ �ε�����ȣ�� ����ؼ� �־��� ����

	bool						_isShift;								//shift Ű�� ���� ���³�?
	bool						_isClickObj;							//object ��ư�� ������?
	UINT						_objSelectCount;						//������Ʈ Ȱ��ȭ �ƴ��� üũ�� ī��Ʈ�� ����

	UINT						_pickSampleStartPointX;					//sample ���� ���� �� �� �ʿ��� ����
	UINT						_pickSampleStartPointY;					//sample ���� ���� �� �� �ʿ��� ����
	UINT						_pickSampleEndPointX;					//sample ���� ���� �� �� �ʿ��� ����
	UINT						_pickSampleEndPointY;					//sample ���� ���� �� �� �ʿ��� ����

	//���̺� �ε� �Ҷ� ����ϴ� ������
	map<MAP_TYPE, string> _mapSizeNames;
	map<MAP_TYPE, string> _mapDataNames;
	
	
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
	
	DWORD setAttribute(string samplePage, UINT frameX, UINT frameY);

	function<void(void)> _increaseMap;
	function<void(void)> _decreaseMap;
	void increaseX();
	void increaseY();
	void decreaseX();
	void decreaseY();

	function<void(void)> _selectObj;
	void selectObj();

	function<void(void)> _map1;
	function<void(void)> _map2;
	function<void(void)> _map3;
	function<void(void)> _map4;
	function<void(void)> _map5;
	void map1();
	void map2();
	void map3();
	void map4();
	void map5();

	function<void(void)> _save;
	void save();
	function<void(void)> _load;
	void load();


	void increaseMap();
	void decreaseMap();
	
	void fileNameSet();



};

