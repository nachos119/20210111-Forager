#pragma once
#include "GameNode.h"

class Tile;
typedef struct tagTile TILE_INFO;
class Map : public GameNode
{
	Tile** tiles;
	TILE_INFO* tile_info;

	int tileCount;

	float time;
	float shovelTime;
	bool shoveling;


	int tileXSize;
	int tileYSize;

public:
	virtual HRESULT Init(int stageNum);
	virtual void Update();
	virtual void Release();

	Tile GetTile(int index);
	Tile* GetTilePtr(int index);
	bool IsEaglesAllDead();
	int GetTileCount()		{ return tileCount; }

	void Shovel();

	Map();
	virtual ~Map();
};
