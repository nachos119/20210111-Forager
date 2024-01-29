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
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init(Camera* setCamera) ;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void Render(HDC hdc, int X,int Y, int MoveX, int MoveY, int num);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void LoadMap(int MapNum, int MapLo);

	void LoadMap(int MapNum, int MapLo, int i);

	TILE_INFO* GettileInfo() { return this->tileInfo; }

	void SetObjM(ObjManager* objM) { this->objM = objM; }

	void WaveInit();

	TileMap() {};
	virtual ~TileMap() {};

};

