#include "TileMap.h"
#include "Map.h"
#include "Tile.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"
#include "ObjManager.h"

HRESULT TileMap::Init()
{
	sampleTileSub = ImageManager::GetSingleton()->FindImage("SampleTileSub");
	sampleTile = ImageManager::GetSingleton()->FindImage("SampleTile");

	// 샘플타일 개수
	sampleTileInfo = new TILE_INFO[SAMPLE_TILE_X * SAMPLE_TILE_Y]();

	// 샘플타일 정의
	for (int y = 0; y < SAMPLE_TILE_Y; y++)
	{
		for (int x = 0; x < SAMPLE_TILE_X; x++)
		{
			sampleTileInfo[y * SAMPLE_TILE_X + x].terrain = LAND;
			sampleTileInfo[y * SAMPLE_TILE_X + x].frame = { x, y };
		}
	}
	// 보조타일 개수
	sampleSubTileInfo = new TILE_INFO[2]();

	// 보조타일 정의
	for (int x = 0; x < 2; x++)
	{
		sampleSubTileInfo[x].terrain = WATER;
		if (x == 1)
			sampleSubTileInfo[x].terrain = CLIFF;

		sampleSubTileInfo[x].frame = { x, 0 };
	}

	tileInfo = new TILE_INFO[WINSIZE_TILE_MAP * WINSIZE_TILE_MAP]();//WINSIZE_TILE_MAP*WINSIZE_TILE_MAP
	for (int y = 0; y < WINSIZE_TILE_MAP; y++)
	{
		for (int x = 0; x < WINSIZE_TILE_MAP; x++)
		{
			tileInfo[y * WINSIZE_TILE_MAP + x].terrain = WATER;
			tileInfo[y * WINSIZE_TILE_MAP + x].frame = sampleSubTileInfo[0].frame;
			tileInfo[y * WINSIZE_TILE_MAP + x].object = nullptr;
		}
	}


	wave = ImageManager::GetSingleton()->FindImage("Wave");
	WaveInit();

	LoadCliff = false;

	LoadMap(1, 13);

	BackBrush = CreateSolidBrush(RGB(48, 149, 252));
	NULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	return S_OK;
}

HRESULT TileMap::Init(Camera * setCamera)
{
	this->setCamera = setCamera;

	sampleTileSub = ImageManager::GetSingleton()->FindImage("SampleTileSub");
	sampleTile = ImageManager::GetSingleton()->FindImage("SampleTile");

	// 샘플타일 개수
	sampleTileInfo = new TILE_INFO[SAMPLE_TILE_X * SAMPLE_TILE_Y]();

	// 샘플타일 정의
	for (int y = 0; y < SAMPLE_TILE_Y; y++)
	{
		for (int x = 0; x < SAMPLE_TILE_X; x++)
		{
			sampleTileInfo[y * SAMPLE_TILE_X + x].terrain = LAND;
			sampleTileInfo[y * SAMPLE_TILE_X + x].frame = { x, y };
		}
	}
	// 보조타일 개수
	sampleSubTileInfo = new TILE_INFO[2]();

	// 보조타일 정의
	for (int x = 0; x < 2; x++)
	{
		sampleSubTileInfo[x].terrain = WATER;
		if (x == 1)
			sampleSubTileInfo[x].terrain = CLIFF;

		sampleSubTileInfo[x].frame = { x, 0 };
	}

	tileInfo = new TILE_INFO[WINSIZE_TILE_MAP * WINSIZE_TILE_MAP]();//WINSIZE_TILE_MAP*WINSIZE_TILE_MAP
	for (int y = 0; y < WINSIZE_TILE_MAP; y++)
	{
		for (int x = 0; x < WINSIZE_TILE_MAP; x++)
		{
			tileInfo[y * WINSIZE_TILE_MAP + x].terrain = WATER;
			tileInfo[y * WINSIZE_TILE_MAP + x].frame = sampleSubTileInfo[0].frame;
			tileInfo[y * WINSIZE_TILE_MAP + x].object = nullptr;
		}
	}

	wave = ImageManager::GetSingleton()->FindImage("Wave");
	WaveInit();

	LoadCliff = false;

	//for (int i = 1; i < 26; i++) {
	//	LoadMap(1, i);
	//}

	LoadMap(1, 13);

	BackBrush = CreateSolidBrush(RGB(48, 149, 252));
	NULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	return S_OK;
}

void TileMap::Release()
{
	DeleteObject(BackBrush);
	DeleteObject(NULLBrush);
	DeleteObject(oldBrush);
	SAFE_DELETE(waveAni1);
	SAFE_DELETE(waveAni2);
	SAFE_DELETE(waveAni3);
	SAFE_DELETE(waveAni4);
	SAFE_DELETE(waveAni5);
	SAFE_ARR_DELETE(sampleSubTileInfo);
	SAFE_ARR_DELETE(sampleTileInfo);
	SAFE_ARR_DELETE(tileInfo);
}

void TileMap::Update()
{
	// 검사해서 절벽으로 바꿔주기
	if (LoadCliff)
	{
		for (int y = 0; y < WINSIZE_TILE_MAP; y++)
		{
			for (int x = 0; x < WINSIZE_TILE_MAP; x++)
			{
				if (tileInfo[(y - 1) * WINSIZE_TILE_MAP + x].terrain == LAND && tileInfo[y * WINSIZE_TILE_MAP + x].terrain == WATER)
				{
					tileInfo[y * WINSIZE_TILE_MAP + x].frame = sampleSubTileInfo[1].frame;
					tileInfo[y * WINSIZE_TILE_MAP + x].terrain = sampleSubTileInfo[1].terrain;
				}
			}
		}
		LoadCliff = false;
	}

	waveAni1->UpdateFrame();
	waveAni2->UpdateFrame();
	waveAni3->UpdateFrame();
	waveAni4->UpdateFrame();
	waveAni5->UpdateFrame();
}

void TileMap::Render(HDC hdc)
{

}

void TileMap::Render(HDC hdc, int X, int Y, int MoveX, int MoveY, int num)
{
	oldBrush = (HBRUSH)SelectObject(hdc, NULLBrush);

	if (num == 4)
	{
		RECT rc;

		for (int i = -1; i + Y < WINSIZE_TILE_MAP; i++)//Y
		{
			for (int j = -1; j + X < WINSIZE_TILE_MAP; j++)//X
			{
				if (i + Y < 1 || (j + X) < 1 || (i + Y) > 61 || (j + X) > 61)
					continue;
				if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].terrain == WATER)
					continue;
				rc = { j * (TILE_SIZE / 2) - MoveX,				i *  (TILE_SIZE / 2) - MoveY,
						j *  (TILE_SIZE / 2) + (TILE_SIZE / 2) - MoveX,	i *  (TILE_SIZE / 2) + (TILE_SIZE / 2) - MoveY };

				if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].terrain == CLIFF)
				{
					sampleTileSub->FrameRender(hdc,
						rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2),
						tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].frame.x,
						tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].frame.y, 2);

					switch ((j + X) % 9)
					{
					case 0: case 8:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE - (TILE_SIZE / 4)), rc.top + (TILE_SIZE - (TILE_SIZE / 4)), 2, waveAni1, 170);
						break;
					case 1: case 7:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE - (TILE_SIZE / 4)), rc.top + (TILE_SIZE - (TILE_SIZE / 4)), 2, waveAni2, 170);
						break;
					case 2: case 6:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE - (TILE_SIZE / 4)), rc.top + (TILE_SIZE - (TILE_SIZE / 4)), 2, waveAni3, 170);
						break;
					case 3: case 5:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE - (TILE_SIZE / 4)), rc.top + (TILE_SIZE - (TILE_SIZE / 4)), 2, waveAni4, 170);
						break;
					case 4:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE - (TILE_SIZE / 4)), rc.top + (TILE_SIZE - (TILE_SIZE / 4)), 2, waveAni5, 170);
						break;
					default:
						break;
					}
				}
				if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].terrain == LAND)
				{
					sampleTile->FrameRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2),
						tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].frame.x, tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].frame.y, 2);
				}

			}
		}

		SelectObject(hdc, oldBrush);


	}
	else
	{
		RECT rc;
		for (int i = 0; i < 15; i++)//Y
		{
			for (int j = 0; j < 24; j++)//X
			{
				if (i + Y < 1 || (j + X) < 1 || (i + Y) > 61 || (j + X) > 61)
					continue;
				if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].terrain == WATER)
					continue;
				rc = { j * TILE_SIZE - MoveX,				i * TILE_SIZE - MoveY ,
						j * TILE_SIZE + TILE_SIZE - MoveX ,	i * TILE_SIZE + TILE_SIZE - MoveY };

				if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].terrain == CLIFF)
				{
					sampleTileSub->FrameRender(hdc,
						rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2),
						tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].frame.x,
						tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].frame.y);

					switch ((j + X) % 9)
					{
					case 0: case 8:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2), waveAni1, 170);
						break;
					case 1: case 7:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2), waveAni2, 170);
						break;
					case 2: case 6:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2), waveAni3, 170);
						break;
					case 3: case 5:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2), waveAni4, 170);
						break;
					case 4:
						wave->AnimationAlphaRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2), waveAni5, 170);
						break;
					default:
						break;
					}
				}
				if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].terrain == LAND)
				{
					sampleTile->FrameRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2), tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].frame.x, tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].frame.y);
				}
				//타일 인포와 똑같은 갯수만큼 출력을 해여
				// Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

				//char szText[128] = "";
				//wsprintf(szText, "%d,  %d", X + j, Y + i);
				//TextOut(hdc, j * TILE_SIZE + 5 - MoveX, i * TILE_SIZE + 5 - MoveY, szText, strlen(szText));
				//wsprintf(szText, "%d", (i + Y) * WINSIZE_TILE_MAP + (j + X));
				//TextOut(hdc, j * TILE_SIZE + 10 - MoveX, i * TILE_SIZE + 30 - MoveY, szText, strlen(szText));

			}
		}


	}

	SelectObject(hdc, oldBrush);
}

void TileMap::LoadMap(int MapNum, int MapLo)
{
	string fileName = "Save/" + to_string(MapNum) + ".map";

	int TileXNum;
	int TileYNum;

	switch (MapLo)
	{
	case 1:
		TileXNum = 1;
		TileYNum = 1;
		break;
	case 2:
		TileXNum = 13;
		TileYNum = 1;
		break;
	case 3:
		TileXNum = 25;
		TileYNum = 1;
		break;
	case 4:
		TileXNum = 37;
		TileYNum = 1;
		break;
	case 5:
		TileXNum = 49;
		TileYNum = 1;
		break;
	case 6:
		TileXNum = 1;
		TileYNum = 13;
		break;
	case 7:
		TileXNum = 13;
		TileYNum = 13;
		break;
	case 8:
		TileXNum = 25;
		TileYNum = 13;
		break;
	case 9:
		TileXNum = 37;
		TileYNum = 13;
		break;
	case 10:
		TileXNum = 49;
		TileYNum = 13;
		break;
	case 11:
		TileXNum = 1;
		TileYNum = 25;
		break;
	case 12:
		TileXNum = 13;
		TileYNum = 25;
		break;
	case 13:
		TileXNum = 25;
		TileYNum = 25;
		break;
	case 14:
		TileXNum = 37;
		TileYNum = 25;
		break;
	case 15:
		TileXNum = 49;
		TileYNum = 25;
		break;
	case 16:
		TileXNum = 1;
		TileYNum = 37;
		break;
	case 17:
		TileXNum = 13;
		TileYNum = 37;
		break;
	case 18:
		TileXNum = 25;
		TileYNum = 37;
		break;
	case 19:
		TileXNum = 37;
		TileYNum = 37;
		break;
	case 20:
		TileXNum = 49;
		TileYNum = 37;
		break;
	case 21:
		TileXNum = 1;
		TileYNum = 49;
		break;
	case 22:
		TileXNum = 13;
		TileYNum = 49;
		break;
	case 23:
		TileXNum = 25;
		TileYNum = 49;
		break;
	case 24:
		TileXNum = 37;
		TileYNum = 49;
		break;
	case 25:
		TileXNum = 49;
		TileYNum = 49;
		break;
	default:
		break;
	}

	DWORD readByte;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	TILE_INFO* tile_info = new TILE_INFO[TILE_X * TILE_Y]();
	ReadFile(hFile, tile_info, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			//tileInfo[(i + TileYNum) * WINSIZE_TILE_MAP + (j + TileXNum)].terrain = tile_info[i * TILE_X + j].terrain;
			//tileInfo[(i + TileYNum) * WINSIZE_TILE_MAP + (j + TileXNum)].frame = tile_info[i * TILE_X + j].frame;
			tileInfo[(i + TileYNum) * WINSIZE_TILE_MAP + (j + TileXNum)] = tile_info[i * TILE_X + j];
		}
	}

	CloseHandle(hFile);

	SAFE_ARR_DELETE(tile_info);

	LoadCliff = true;
}

void TileMap::LoadMap(int MapNum, int MapLo, int i)
{
	string fileName = "Save/" + to_string(MapNum) + ".map";

	int TileXNum;
	int TileYNum;

	switch (MapLo)
	{
	case 1:
		TileXNum = 1;
		TileYNum = 1;
		break;
	case 2:
		TileXNum = 13;
		TileYNum = 1;
		break;
	case 3:
		TileXNum = 25;
		TileYNum = 1;
		break;
	case 4:
		TileXNum = 37;
		TileYNum = 1;
		break;
	case 5:
		TileXNum = 49;
		TileYNum = 1;
		break;
	case 6:
		TileXNum = 1;
		TileYNum = 13;
		break;
	case 7:
		TileXNum = 13;
		TileYNum = 13;
		break;
	case 8:
		TileXNum = 25;
		TileYNum = 13;
		break;
	case 9:
		TileXNum = 37;
		TileYNum = 13;
		break;
	case 10:
		TileXNum = 49;
		TileYNum = 13;
		break;
	case 11:
		TileXNum = 1;
		TileYNum = 25;
		break;
	case 12:
		TileXNum = 13;
		TileYNum = 25;
		break;
	case 13:
		TileXNum = 25;
		TileYNum = 25;
		break;
	case 14:
		TileXNum = 37;
		TileYNum = 25;
		break;
	case 15:
		TileXNum = 49;
		TileYNum = 25;
		break;
	case 16:
		TileXNum = 1;
		TileYNum = 37;
		break;
	case 17:
		TileXNum = 13;
		TileYNum = 37;
		break;
	case 18:
		TileXNum = 25;
		TileYNum = 37;
		break;
	case 19:
		TileXNum = 37;
		TileYNum = 37;
		break;
	case 20:
		TileXNum = 49;
		TileYNum = 37;
		break;
	case 21:
		TileXNum = 1;
		TileYNum = 49;
		break;
	case 22:
		TileXNum = 13;
		TileYNum = 49;
		break;
	case 23:
		TileXNum = 25;
		TileYNum = 49;
		break;
	case 24:
		TileXNum = 37;
		TileYNum = 49;
		break;
	case 25:
		TileXNum = 49;
		TileYNum = 49;
		break;
	default:
		break;
	}

	DWORD readByte;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	TILE_INFO* tile_info = new TILE_INFO[TILE_X * TILE_Y]();
	ReadFile(hFile, tile_info, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			//tileInfo[(i + TileYNum) * WINSIZE_TILE_MAP + (j + TileXNum)].terrain = tile_info[i * TILE_X + j].terrain;
			//tileInfo[(i + TileYNum) * WINSIZE_TILE_MAP + (j + TileXNum)].frame = tile_info[i * TILE_X + j].frame;
			tileInfo[(i + TileYNum) * WINSIZE_TILE_MAP + (j + TileXNum)] = tile_info[i * TILE_X + j];
		}
	}

	CloseHandle(hFile);

	SAFE_ARR_DELETE(tile_info);

	objM->objectInit(TileXNum, TileYNum);

	LoadCliff = true;
}

void TileMap::WaveInit()
{
	waveAni1 = new Animation();
	waveAni1->Init(wave->GetWidth(), wave->GetHeight(), wave->GetFrameWidth(), wave->GetFrameHeight());
	waveAni1->SetPlayFrame(true, false);
	waveAni1->SetKeyFrameUpdateTime(0.1f);
	waveAni1->Start();

	waveAni2 = new Animation();
	waveAni2->Init(wave->GetWidth(), wave->GetHeight(), wave->GetFrameWidth(), wave->GetFrameHeight());
	waveAni2->SetPlayFrame(1, 0, true, false);
	waveAni2->SetKeyFrameUpdateTime(0.1f);
	waveAni2->Start();

	waveAni3 = new Animation();
	waveAni3->Init(wave->GetWidth(), wave->GetHeight(), wave->GetFrameWidth(), wave->GetFrameHeight());
	waveAni3->SetPlayFrame(2, 1, true, false);
	waveAni3->SetKeyFrameUpdateTime(0.1f);
	waveAni3->Start();

	waveAni4 = new Animation();
	waveAni4->Init(wave->GetWidth(), wave->GetHeight(), wave->GetFrameWidth(), wave->GetFrameHeight());
	waveAni4->SetPlayFrame(3, 2, true, false);
	waveAni4->SetKeyFrameUpdateTime(0.1f);
	waveAni4->Start();

	waveAni5 = new Animation();
	waveAni5->Init(wave->GetWidth(), wave->GetHeight(), wave->GetFrameWidth(), wave->GetFrameHeight());
	waveAni5->SetPlayFrame(4, 3, true, false);
	waveAni5->SetKeyFrameUpdateTime(0.1f);
	waveAni5->Start();
}
