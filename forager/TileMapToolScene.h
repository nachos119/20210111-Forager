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

	// 메인 타일의 정보
	RECT rcMain;
	TILE_INFO* tileInfo;

	// 샘플 타일의 정보
	RECT rcSample;
	TILE_INFO* sampleTileInfo;

	// 보조
	Image* sampleTileSub;
	RECT rcSampleSub;
	TILE_INFO* sampleSubTileInfo;
	
	// 선택된 타일의 정보
	SELECT_TILE_INFO selectTileInfo;
	POINT selectStartFrame;
	bool sampleSelectStart;
	int selectUndestroyedPart;

	// 세이브, 로드 버튼
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

