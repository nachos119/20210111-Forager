#include "TileMapToolScene.h"
#include "Image.h"
#include "Tile.h"
#include "Button.h"
#include "ButtonFunction.h"

// ���� ���ε��� ����

HRESULT TileMapToolScene::Init()
{
	SetWindowSize(0, 0, WINSIZE_MAP_X, WINSIZE_MAP_Y);

	sampleTile = ImageManager::GetSingleton()->FindImage("SampleTile");
	selectTileEdge = ImageManager::GetSingleton()->FindImage("SelectTileEdge");
	sampleTileSub = ImageManager::GetSingleton()->FindImage("SampleTileSub");


	// ������ ���� Ÿ���� ������ ����
	rcSample.left = WINSIZE_MAP_X - sampleTile->GetWidth() - 50;
	rcSample.right = rcSample.left + sampleTile->GetWidth();
	rcSample.top = 50;
	rcSample.bottom = rcSample.top + sampleTile->GetHeight();

	// ����Ÿ�� ����
	sampleTileInfo = new TILE_INFO[SAMPLE_TILE_X * SAMPLE_TILE_Y]();

	// ����Ÿ�� ����
	for (int y = 0; y < SAMPLE_TILE_Y; y++)
	{
		for (int x = 0; x < SAMPLE_TILE_X; x++)
		{
			sampleTileInfo[y * SAMPLE_TILE_X + x].terrain = LAND;
			sampleTileInfo[y * SAMPLE_TILE_X + x].frame = { x, y };
		}
	}

	// ����
	//rcSampleSub.left = WINSIZE_TILE_MAP_X - sampleTileSub->GetWidth() - 50;
	//rcSampleSub.right = rcSampleSub.left + sampleTileSub->GetWidth();
	//rcSampleSub.top = 250;
	//rcSampleSub.bottom = rcSampleSub.top + sampleTileSub->GetHeight();

	// ����Ÿ�� ����
	sampleSubTileInfo = new TILE_INFO[2]();

	// ����Ÿ�� ����
	for (int x = 0; x < 2; x++)
	{
		sampleSubTileInfo[x].terrain = WATER;
		if(x == 1)
			sampleSubTileInfo[x].terrain = CLIFF;

		sampleSubTileInfo[x].frame = { x, 0 };
	}

	// ���� ��ܿ� ���� Ÿ���� ������ ����
	rcMain.left = TILE_SIZE;
	rcMain.top = TILE_SIZE;
	rcMain.right = rcMain.left + TILE_X * TILE_SIZE;
	rcMain.bottom = rcMain.top + TILE_Y * TILE_SIZE;

	tileInfo = new TILE_INFO[TILE_X * (TILE_Y + 1)]();
	for (int i = 0; i < TILE_X * (TILE_Y + 1); i++)
	{
		tileInfo[i].terrain = WATER;
		tileInfo[i].frame = sampleSubTileInfo[0].frame;
		tileInfo[i].object = nullptr;//OBJEK::XXX;
	}

	//stageNumBox = ImageManager::GetSingleton()->FindImage("Box");
	//numbers = ImageManager::GetSingleton()->FindImage("Number");

	// ����Ʈ ���� �ʱ�ȭ
	selectTileInfo.frame.left = -100;
	selectTileInfo.frame.right = -100;
	selectTileInfo.frame.top = -100;
	selectTileInfo.frame.bottom = -100;


	// ���̺�, �ε� ������ ��ư
	saveButton = new Button();
	saveButton->Init("SaveLoadExitButtonF", rcSample.left - 200, sampleTile->GetHeight() + 400, { 0, 1 }, { 0, 0 });
	saveButton->SetButtonFunc(ButtonFunction::TileInfoSave, Argument_Kind::Argument2, new Argument2(tileInfo, 0));

	loadButton = new Button();
	loadButton->Init("SaveLoadExitButtonF", rcSample.left, sampleTile->GetHeight() + 400, { 1, 1 }, { 1, 0 });
	loadButton->SetButtonFunc(ButtonFunction::TileInfoLoad, Argument_Kind::Argument2, new Argument2(tileInfo, 0));

	exitButton = new Button();
	exitButton->Init("SaveLoadExitButtonF", rcSample.left - 100, sampleTile->GetHeight() + 500, { 2, 1 }, { 2, 0 });
	Argument1* arg1 = new Argument1();
	arg1->sceneName = "Ÿ��Ʋ";
	arg1->loadingSceneName = "";
	exitButton->SetButtonFunc(ButtonFunction::ChangeScene, Argument_Kind::Argument1, arg1);


	return S_OK;
}

void TileMapToolScene::Release()
{
	SAFE_RELEASE(saveButton);
	SAFE_RELEASE(loadButton);
	SAFE_RELEASE(exitButton);
	//SAFE_RELEASE(stageLeftButton);
	//SAFE_RELEASE(stageRightButton);
	SAFE_ARR_DELETE(tileInfo);
	SAFE_ARR_DELETE(sampleSubTileInfo);
	SAFE_ARR_DELETE(sampleTileInfo);
}

void TileMapToolScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		SceneManager::GetSingleton()->ChangeScene("Ÿ��Ʋ");
		return;
	}


#pragma region ���� ����
	// ���� Ÿ�� ���� �� ���� Ȯ��
	if (sampleSelectStart)
	{
		g_ptMouse.x = Clamp(g_ptMouse.x, rcSample.left, rcSample.right);
		g_ptMouse.y = Clamp(g_ptMouse.y, rcSample.top, rcSample.bottom - 1);
	}

	if (PtInRect(&rcSample, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcSample.left;
			int posY = g_ptMouse.y - rcSample.top;
			int idX = posX / TILE_SIZE;
			int idY = posY / TILE_SIZE;

			selectTileInfo.frame.left = idX;
			selectTileInfo.frame.right = idX;
			selectTileInfo.frame.top = idY;
			selectTileInfo.frame.bottom = idY;

			selectStartFrame = { idX, idY };
			sampleSelectStart = true;
		}

		if (sampleSelectStart)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{
				int posX = g_ptMouse.x - rcSample.left;
				int posY = g_ptMouse.y - rcSample.top;
				int idX = posX / TILE_SIZE;
				int idY = posY / TILE_SIZE;

				if (selectStartFrame.x <= idX)
				{
					selectTileInfo.frame.left = selectStartFrame.x;
					selectTileInfo.frame.right = idX;
				}
				else
				{
					selectTileInfo.frame.right = selectStartFrame.x;
					selectTileInfo.frame.left = idX;
				}
				if (selectStartFrame.y <= idY)
				{
					selectTileInfo.frame.top = selectStartFrame.y;
					selectTileInfo.frame.bottom = idY;
				}
				else
				{
					selectTileInfo.frame.bottom = selectStartFrame.y;
					selectTileInfo.frame.top = idY;
				}
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			sampleSelectStart = false;
		}
	}

#pragma endregion

#pragma region ���� ����
	if (PtInRect(&rcMain, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - 5;
			int posY = g_ptMouse.y - 5;
			int idX = posX / TILE_SIZE;
			int idY = posY / TILE_SIZE;

			for (int y = 0; y <= selectTileInfo.frame.bottom - selectTileInfo.frame.top; y++)
			{
				for (int x = 0; x <= selectTileInfo.frame.right - selectTileInfo.frame.left; x++)
				{
					//���� ���� �ȿ� �־�� ����
					if (idX + x > TILE_X - 1)
						continue;

					if ((idX + x) + (idY + y) * TILE_X < TILE_X * TILE_Y)
					{
						TILE_INFO info = sampleTileInfo[x + selectTileInfo.frame.left + (y + selectTileInfo.frame.top) * SAMPLE_TILE_X];
						tileInfo[(idX + x) + (idY + y) * TILE_X].frame = info.frame;
						tileInfo[(idX + x) + (idY + y) * TILE_X].terrain = info.terrain;
					}
				}
			}
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
		{
			int posX = g_ptMouse.x - 5;
			int posY = g_ptMouse.y - 5;
			int idX = posX / TILE_SIZE;
			int idY = posY / TILE_SIZE;

			for (int y = 0; y <= selectTileInfo.frame.bottom - selectTileInfo.frame.top; y++)
			{
				for (int x = 0; x <= selectTileInfo.frame.right - selectTileInfo.frame.left; x++)
				{
					//���� ���� �ȿ� �־�� ����
					if (idX + x > TILE_X - 1)
						continue;

					if ((idX + x) + (idY + y) * TILE_X < TILE_X * TILE_Y)
					{
						tileInfo[(idX + x) + (idY + y) * TILE_X].frame = sampleSubTileInfo[0].frame;
						tileInfo[(idX + x) + (idY + y) * TILE_X].terrain = sampleSubTileInfo[0].terrain;
					}
				}
			}
		}
	}

	// �ε�������
	for (int y = 1; y < (TILE_Y + 1); y++)
	{
		for (int x = 0; x < TILE_X; x++)
		{
			if (tileInfo[y * TILE_X + x].terrain == CLIFF && tileInfo[(y - 1) * TILE_X + x].terrain == WATER ||
				tileInfo[y * TILE_X + x].terrain == CLIFF && tileInfo[(y - 1) * TILE_X + x].terrain == CLIFF)
			{
				tileInfo[y * TILE_X + x].frame = sampleSubTileInfo[0].frame;
				tileInfo[y * TILE_X + x].terrain = sampleSubTileInfo[0].terrain;
			}

		}
	}

	// �˻��ؼ� �������� �ٲ��ֱ�
	for (int y = 1; y < (TILE_Y + 1); y++)
	{
		for (int x = 0; x < TILE_X; x++)
		{
			if (tileInfo[(y - 1) * TILE_X + x].terrain == LAND && tileInfo[y * TILE_X + x].terrain == WATER)
			{
				tileInfo[y * TILE_X + x].frame = sampleSubTileInfo[1].frame;
				tileInfo[y * TILE_X + x].terrain = sampleSubTileInfo[1].terrain;
			}
		}
	}

#pragma endregion
	if (saveButton)
		saveButton->Update();

	if (loadButton)
		loadButton->Update();

	if (exitButton)
		exitButton->Update();

}

void TileMapToolScene::Render(HDC hdc)
{

	HBRUSH BackBrush = CreateSolidBrush(RGB(48, 149, 252));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, BackBrush);
	PatBlt(hdc, 0, 0, WINSIZE_MAP_X, WINSIZE_MAP_Y, PATCOPY); // BackBrush

	SelectObject(hdc, oldBrush);
	DeleteObject(BackBrush);


	if (sampleTile)
	{
		HBRUSH brush2 = (HBRUSH)GetStockObject(NULL_BRUSH); // CreateSolidBrush(NULL_BRUSH); �� �ȵǳ�?
		HBRUSH oldBrush2 = (HBRUSH)SelectObject(hdc, brush2);
		// ���� Ÿ��
		sampleTile->Render(hdc, WINSIZE_MAP_X - sampleTile->GetWidth() - 50, 50);
		//sampleTileSub->Render(hdc, WINSIZE_TILE_MAP_X - sampleTileSub->GetWidth() - 50, 300);

		// ���� Ÿ��
		RECT rc;
		// �׸��� ũ�⸦ �����ؿ�

		for (int i = 0; i < TILE_X * (TILE_Y + 1); i++)
		{
			rc = { TILE_SIZE * (i % TILE_X) + 20,				TILE_SIZE * (i / TILE_X) + 20,
					TILE_SIZE * (i % TILE_X) + (TILE_SIZE + 20),	TILE_SIZE * (i / TILE_X) + (TILE_SIZE + 20) };

			if (tileInfo[i].terrain == WATER || tileInfo[i].terrain == CLIFF)
			{
				sampleTileSub->FrameRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2), tileInfo[i].frame.x, tileInfo[i].frame.y);
			}
			else
			{
				sampleTile->FrameRender(hdc, rc.left + (TILE_SIZE / 2), rc.top + (TILE_SIZE / 2), tileInfo[i].frame.x, tileInfo[i].frame.y);
			}

			if (i < 144)
			{
				//Ÿ�� ������ �Ȱ��� ������ŭ ����� �ؿ�
				 Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			}
		}

		// ���õ� Ÿ�ϵ�
		for (int i = 0; i <= selectTileInfo.frame.bottom - selectTileInfo.frame.top; i++)
		{
			for (int j = 0; j <= selectTileInfo.frame.right - selectTileInfo.frame.left; j++)
			{
				sampleTile->FrameRender(hdc,
					g_ptMouse.x + (j * TILE_SIZE),
					g_ptMouse.y + (i * TILE_SIZE),
					j + selectTileInfo.frame.left,
					i + selectTileInfo.frame.top);
			}
		}
		selectTileEdge->FrameRender(hdc, rcSample.left + (selectTileInfo.frame.left * TILE_SIZE) + TILE_SIZE / 2 - 2,
			rcSample.top + (selectTileInfo.frame.top * TILE_SIZE) + TILE_SIZE / 2 - 2, 0, 0);		// ������
		selectTileEdge->FrameRender(hdc, rcSample.left + (selectTileInfo.frame.right * TILE_SIZE) + TILE_SIZE / 2 + 2,
			rcSample.top + (selectTileInfo.frame.top * TILE_SIZE) + TILE_SIZE / 2 - 2, 1, 0);		// ������
		selectTileEdge->FrameRender(hdc, rcSample.left + (selectTileInfo.frame.left * TILE_SIZE) + TILE_SIZE / 2 - 2,
			rcSample.top + (selectTileInfo.frame.bottom * TILE_SIZE) + TILE_SIZE / 2 + 2, 0, 1);// �޾Ʒ�
		selectTileEdge->FrameRender(hdc, rcSample.left + (selectTileInfo.frame.right * TILE_SIZE) + TILE_SIZE / 2 + 2,
			rcSample.top + (selectTileInfo.frame.bottom * TILE_SIZE) + TILE_SIZE / 2 + 2, 1, 1);// �����Ʒ�

		SelectObject(hdc, oldBrush2);
		DeleteObject(brush2);
	}

	// ���̺�, �ε�, ������ ��ư
	saveButton->Render(hdc);
	loadButton->Render(hdc);
	exitButton->Render(hdc);

}


TileMapToolScene::TileMapToolScene()
	: tileInfo(nullptr)
	, sampleTileInfo(nullptr)
	, saveButton(nullptr)
	, loadButton(nullptr)
{
}
