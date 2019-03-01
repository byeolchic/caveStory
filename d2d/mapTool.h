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

#define SAMPLE_DISTANCE_Y		50			//샘플타일 시작점 간격줌

#define SAMPLE_WIDTH_NUM	6
#define SAMPLE_HEIGHT_NUM	10
#define SAMPLE_START_POSX	(WINSIZEX - (TILE_SIZE * SAMPLE_WIDTH_NUM + TILE_SIZE))

#define CAMERA_SHOW_RANGE_W	(19 * TILE_SIZE)		//카메라 범위 X축
#define CAMERA_SHOW_RANGE_H (17 * TILE_SIZE)		//카메라 범위 Y축

static button*		_sampleNextPageButton;
static button*		_samplePrePageButton;
static button*		_increaseButton;
static button*		_decreaseButton;
static button*		_selectXButton;
static button*		_selectYbutton;
static button*		_objButton;

static bool			_isSelectX;			//x축 증감을 선택했냐?
static bool			_isSelectY;			//y축 증감을 선택했냐?

static UINT			TILEX;				//맵의 전체 타일 가로 개수
static UINT			TILEY;				//맵의 전체 타일 세로 개수

static int			_boolCountX;			//toggle키로 만들때 사용할 변수
static int			_boolCountY;

static int			_samplePage;
static bool			_isClick;			//샘플 타일을 클릭했으면

struct tagPickSample
{
	UINT tileImgPage;
	int indX;
	int indY;
};


class mapTool :	public gameNode
{
private:
	POINTF						_pt;				//각도 계산하는 용도의 _pt
	float						_getAngleF;			//계산된 각도 저장하는 변수
	int							_calculateNum;		//각도 계산할때 첫번째 클릭, 두번째 클릭 구분할 int 변수
	D2D1_RECT_F					_loopRect;			//루프 렌더 할 때 필요한 렉트
	float						_loopX;				//루프 도는 속도

	image*						_sampleImg[SAMPLE_TILE_IMAGEKEY_COUNT];
	
	vector<vector<tagTile*>>	_vvTile;

	UINT						_reSizeX;			//맵 사이즈 조정 후 그 사이즈를 저장할 변수
	UINT						_reSizeY;			//맵 사이즈 조정 후 그 사이즈를 저장할 변수

	tagPickSample				_pickSample;		//선택한 샘플의 인덱스번호를 계산해서 넣어줄 변수

	bool						_isShift;			//shift 키를 누른 상태냐?
	bool						_isClickObj;		//object 버튼을 눌렀냐?
	UINT						_objSelectCount;	//오브젝트 활성화 됐는지 체크할 카운트할 변수



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

	void mapToolSetting();		//맵툴의 기본 타일들 세팅하는 함수
	
	void pickSample();			//샘플 타일을 선택하는 함수
	void drawMap();				//선택한 샘플을 맵에 그리는 함수
	
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

