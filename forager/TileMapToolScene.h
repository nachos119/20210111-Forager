#pragma once
#include "GameNode.h"

typedef struct tagSelectTile
{
	RECT frame;
} SELECT_TILE_INFO;

class Image;
class Button;
typedef struct tagTile TILE_INFO;
class TileMapToolScene : public GameNode
{
private:
	Image* sampleTile;
	Image* selectTileEdge;

	// ���� Ÿ���� ����
	RECT rcMain;
	TILE_INFO* tileInfo;

	// ���� Ÿ���� ����
	RECT rcSample;
	TILE_INFO* sampleTileInfo;

	// ����
	Image* sampleTileSub;
	RECT rcSampleSub;
	TILE_INFO* sampleSubTileInfo;
	
	// ���õ� Ÿ���� ����
	SELECT_TILE_INFO selectTileInfo;
	POINT selectStartFrame;
	bool sampleSelectStart;
	int selectUndestroyedPart;

	// ���̺�, �ε� ��ư
	Button* saveButton;
	Button* loadButton;
	Button* exitButton;
	Button* stageLeftButton;
	Button* stageRightButton;

	//
	Image* stageNumBox;
	Image* numbers;

	int eagleIndex;

	HPEN pen;
	HPEN oldPen;

public:
	virtual HRESULT Init() override;	
	virtual void Release() override;	
	virtual void Update() override;		
	virtual void Render(HDC hdc) override;

	TileMapToolScene();
	virtual ~TileMapToolScene() {};
};

