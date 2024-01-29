#include "Map.h"
#include "Image.h"
#include "Tile.h"

HRESULT Map::Init(int stageNum)
{	
	string fileName = "Save/saveMapData" + to_string(stageNum) + ".map";

	DWORD readByte;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//ReadFile(hFile, size, sizeof(int) * 2, &readByte, NULL);
	tileXSize = TILE_X;
	tileYSize = TILE_Y;
	tile_info = new TILE_INFO[tileXSize * tileYSize];
	ReadFile(hFile, tile_info, sizeof(TILE_INFO) * tileXSize * tileYSize, &readByte, NULL);
		
	CloseHandle(hFile);

	
	////tileCount = TILE_X * TILE_Y;

	//if(tile_info == nullptr)
	//	tile_info = new TILE_INFO[TILE_X * TILE_Y]();


	//if (tiles == nullptr)
	//{
	//	tiles = new Tile* [TILE_X * TILE_Y];
	//	for (int i = 0; i < TILE_X * TILE_Y; i++)
	//	{
	//		tiles[i] = new Tile();
	//	}
	//}

	//shovelTime = 0;
	//shoveling = false;

	return S_OK;
}

void Map::Update()
{
	
}

void Map::Release()
{
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		tiles[i] = nullptr;
	}
	SAFE_ARR_DELETE(tiles);
}

Tile Map::GetTile(int index)
{
	return *tiles[index];
}

Tile* Map::GetTilePtr(int index)
{
	return tiles[index];
}

bool Map::IsEaglesAllDead()
{
	
	return true;
}

void Map::Shovel()
{
	
}

Map::Map()
	: tile_info(nullptr)
	, tiles(nullptr)
{
}

Map::~Map()
{
}
