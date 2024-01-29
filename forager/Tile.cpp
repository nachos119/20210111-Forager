#include "Tile.h"
#include "Image.h"

HRESULT Tile::Init()
{
	//objType = OBJECT_TYPE_TILE;
	sampleTile = ImageManager::GetSingleton()->FindImage("»ùÇÃÅ¸ÀÏ");
	waterAndEagle = ImageManager::GetSingleton()->FindImage("WaterAndEagle");
	active = false;
	time = 0;
	return S_OK;
}

void Tile::Release()
{
}

void Tile::Update()
{
}

void Tile::FirstRender(HDC hdc)
{
}

void Tile::Render(HDC hdc)
{
}

void Tile::LateRender(HDC hdc)
{
	
}

void Tile::SetRect(int left, int top, int right, int bottom)
{
	rc.left = left;
	rc.top = top;
	rc.right = right;
	rc.bottom = bottom;
}

Tile::Tile()
{
}

Tile::~Tile()
{
}

