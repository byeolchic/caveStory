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

#define SAMPLE_DISTANCE_Y		50			//샘플타일 시작점 간격줌

#define SAMPLE_WIDTH_NUM	6
#define SAMPLE_HEIGHT_NUM	10
#define SAMPLE_START_POSX	(WINSIZEX - (TILE_SIZE * SAMPLE_WIDTH_NUM + TILE_SIZE))

#define CAMERA_SHOW_RANGE_W	(19 * TILE_SIZE)		//카메라 범위 X축
#define CAMERA_SHOW_RANGE_H (17 * TILE_SIZE)		//카메라 범위 Y축

static bool			_isSelectX;			//x축 증감을 선택했냐?
static bool			_isSelectY;			//y축 증감을 선택했냐?

static UINT			TILEX;				//맵의 전체 타일 가로 개수
static UINT			TILEY;				//맵의 전체 타일 세로 개수

static int			_boolCountX;			//toggle키로 만들때 사용할 변수
static int			_boolCountY;

static int			_samplePage;
static bool			_isClick;			//샘플 타일을 클릭했으면
static bool			_isBackground;		//백그라운드의타일을 선택했을때 필요한 편수

//맵 타입의 개수
static UINT						_mapType;								//맵의 타입



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
	
	//저장할 때 사용할 버튼
	//맵의 타입을 고르는 버튼
	button*		_mapOne;
	button*		_mapTwo;
	button*		_mapThree;
	button*		_mapFour;
	button*		_mapFive;
	//저장버튼
	button*		_saveButton;
	button*		_loadButton;
	
	POINTF						_pt;									//각도 계산하는 용도의 _pt
	float						_getAngleF;								//계산된 각도 저장하는 변수
	int							_calculateNum;							//각도 계산할때 첫번째 클릭, 두번째 클릭 구분할 int 변수
	D2D1_RECT_F					_loopRect;								//루프 렌더 할 때 필요한 렉트
	float						_loopX;									//루프 도는 속도

	image*						_sampleImg[SAMPLE_TILE_IMAGEKEY_COUNT];
	
	vector<vector<tagTile*>>	_vvTile;

	UINT						_reSizeX;								//맵 사이즈 조정 후 그 사이즈를 저장할 변수
	UINT						_reSizeY;								//맵 사이즈 조정 후 그 사이즈를 저장할 변수

	tagPickSample				_pickSample;							//선택한 샘플의 인덱스번호를 계산해서 넣어줄 변수

	bool						_isShift;								//shift 키를 누른 상태냐?
	bool						_isClickObj;							//object 버튼을 눌렀냐?
	UINT						_objSelectCount;						//오브젝트 활성화 됐는지 체크할 카운트할 변수

	UINT						_pickSampleStartPointX;					//sample 범위 선택 할 때 필요한 변수
	UINT						_pickSampleStartPointY;					//sample 범위 선택 할 때 필요한 변수
	UINT						_pickSampleEndPointX;					//sample 범위 선택 할 때 필요한 변수
	UINT						_pickSampleEndPointY;					//sample 범위 선택 할 때 필요한 변수

	//세이브 로드 할때 사용하는 변수임
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

	void mapToolSetting();		//맵툴의 기본 타일들 세팅하는 함수
	
	void pickSample();			//샘플 타일을 선택하는 함수
	void drawMap();				//선택한 샘플을 맵에 그리는 함수
	
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

