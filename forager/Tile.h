#pragma once
#include "pch.h"
#include "ObjeK.h"

typedef struct tagTile
{
	TERRAIN terrain;
	//OBJEK object;
	Objek* object;
	POINT frame;
} TILE_INFO;

class Image;
class Player;
class Tile //: public Object
{
	TERRAIN terrain;
	OBJEK object;
	POINT frame;
	RECT phisicsRect;

	Image* sampleTile;
	Image* waterAndEagle;
	float time;
	bool active;
	RECT rc;

	// ÂüÁ¶¿ë
	Player* player;

public:
	HRESULT Init();
	void Release();
	void Update();
	void FirstRender(HDC hdc);
	void Render(HDC hdc);
	void LateRender(HDC hdc);

	void SetRect(int left, int top, int right, int bottom);
	POINT GetFrame()		{ return frame; }
	TERRAIN GetTerrain()	{ return terrain; }
	OBJEK GetOb() { return object; }

	Tile();
	~Tile();
};


