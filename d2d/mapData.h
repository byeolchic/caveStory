#pragma once
#include	"tileNode.h"
#include	"player.h"
class mapData 
{
public:
	struct tagPortal
	{
		UINT x;
		UINT y;
		string nextScene;
		UINT nextX;
		UINT nextY;

		int nexDir;			//이동후 쿼트가 바라볼 방향 (만약 왼쪽 : 1, 오른쪽 : 2)
	};

protected:

	UINT						TILEX;					//불러올 맵의 타일 사이즈
	UINT						TILEY;					//불러올 맵의 타일 사이즈
	
	vector<vector<tagTile*>>	_vvTile;				//맵의 정보를 담을 이중벡터
	player*						_player;				//쿼트

	UINT						_rangeStartX;			//렌더시 보여주는 범위 만큼만 렌더하기 위해서 넣은 범위 변수(시작)
	UINT						_rangeStartY;			//렌더시 보여주는 범위 만큼만 렌더하기 위해서 넣은 범위 변수(시작)
	UINT						_rangeMaxX;				//렌더시 보여주는 범위 만큼만 렌더하기 위해서 넣은 범위 변수(끝)
	UINT						_rangeMaxY;				//렌더시 보여주는 범위 만큼만 렌더하기 위해서 넣은 범위 변수(끝)

	vector<tagPortal*>					_portal;

	//프레임을 출력할때 필요한 변수들
	int						_saveFrameCount;				//프레임 이미지들 간격 주는 변수
	int						_saveFrameImgIndX;				//프레임 번호 X
	int						_saveFrameImgIdxY;				//프레임 번호 Y

	int						_lifeChargeFramCount;
	int						_lifeChargeFrameIndxX;
	int						_lifeChargeFrameIndxY;

	int						_boxFrameCount;
	int						_boxFrameIndX;
	int						_boxFrameindY;

	int						_lifeCapsuleFrameCount;
	int						_lifeCapsuleIndX;
	int						_lifeCapsuleIndY;



public:
	mapData();
	~mapData();
	virtual HRESULT init();
	virtual HRESULT init(const char * mapSizeFileName, const char * mapFileName);
	virtual void release();
	virtual void update();
	virtual void render();

	void frameUpdate();
	void load(const char * mapSizeFileName, const char * mapFileName);
	virtual void portalLoad();
	
	tagTile* getTile(UINT x, UINT y) { return _vvTile[x][y]; }

	//링크
	virtual void setPlayerMemoryAdressLink(player* p) { _player = p; }

};

