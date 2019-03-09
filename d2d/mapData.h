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

		int nexDir;			//�̵��� ��Ʈ�� �ٶ� ���� (���� ���� : 1, ������ : 2)
	};

protected:

	UINT						TILEX;					//�ҷ��� ���� Ÿ�� ������
	UINT						TILEY;					//�ҷ��� ���� Ÿ�� ������
	
	vector<vector<tagTile*>>	_vvTile;				//���� ������ ���� ���ߺ���
	player*						_player;				//��Ʈ

	UINT						_rangeStartX;			//������ �����ִ� ���� ��ŭ�� �����ϱ� ���ؼ� ���� ���� ����(����)
	UINT						_rangeStartY;			//������ �����ִ� ���� ��ŭ�� �����ϱ� ���ؼ� ���� ���� ����(����)
	UINT						_rangeMaxX;				//������ �����ִ� ���� ��ŭ�� �����ϱ� ���ؼ� ���� ���� ����(��)
	UINT						_rangeMaxY;				//������ �����ִ� ���� ��ŭ�� �����ϱ� ���ؼ� ���� ���� ����(��)

	vector<tagPortal*>					_portal;

	//�������� ����Ҷ� �ʿ��� ������
	int						_saveFrameCount;				//������ �̹����� ���� �ִ� ����
	int						_saveFrameImgIndX;				//������ ��ȣ X
	int						_saveFrameImgIdxY;				//������ ��ȣ Y

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

	//��ũ
	virtual void setPlayerMemoryAdressLink(player* p) { _player = p; }

};

