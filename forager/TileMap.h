#pragma once
#include "GameNode.h"

class Map;
class Camera;
class Player;
class Animation;
class Objek;
class Menu;
class CollisionManager;
class ObjManager;
class TileMap : public GameNode
{
private:
	TILE_INFO* tileInfo;
	Map* map;
	Image* sampleTileSub;
	TILE_INFO* sampleSubTileInfo;

	Image* sampleTile;
	TILE_INFO* sampleTileInfo;

	Image* wave;
	Animation* waveAni1;
	Animation* waveAni2;
	Animation* waveAni3;
	Animation* waveAni4;
	Animation* waveAni5;

	HBRUSH BackBrush;
	HBRUSH NULLBrush;
	HBRUSH oldBrush;

	bool LoadCliff;
	Camera* setCamera;
	ObjManager* objM;

public:
	virtual HRESULT Init() override;			// 멤버 변수 초기화, 메모리 할당
	HRESULT Init(Camera* setCamera) ;			// 멤버 변수 초기화, 메모리 할당
	virtual void Release() override;			// 메모리 해제
	virtual void Update() override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc) override;		// 프레임 단위 출력 (이미지, 텍스트 등)
	void Render(HDC hdc, int X,int Y, int MoveX, int MoveY, int num);		// 프레임 단위 출력 (이미지, 텍스트 등)

	void LoadMap(int MapNum, int MapLo);

	void LoadMap(int MapNum, int MapLo, int i);

	TILE_INFO* GettileInfo() { return this->tileInfo; }

	void SetObjM(ObjManager* objM) { this->objM = objM; }

	void WaveInit();

	TileMap() {};
	virtual ~TileMap() {};

};

