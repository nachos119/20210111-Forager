#include "MainGame.h"
#include "Image.h"
#include "TitleScene.h"
#include "TileMapToolScene.h"
#include "PlayScene.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	// 매니저 초기화
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();

	// 씬 추가
	SceneManager::GetSingleton()->AddScene("타이틀", new TitleScene());
	SceneManager::GetSingleton()->AddScene("맵툴", new TileMapToolScene());
	SceneManager::GetSingleton()->AddScene("플레이", new PlayScene());

	// 사운드 추가
	//SoundManager::GetSingleton()->AddSound("TitleScene - On", "Sound/TitleScene - On.mp3", true, false);

	// 이미지 추가
	ImageInit();

	backBuffer = new Image();
	backBuffer->Init(max(WINSIZE_MAP_X, WINSIZE_MAP_X), max(WINSIZE_MAP_Y, WINSIZE_MAP_Y));

	backGround = new Image();
	backGround->Init(WINSIZE_MAP_X, WINSIZE_MAP_Y);
	/*if (FAILED(backGround->Init("Image/background.bmp", WINSIZE_X, WINSIZE_Y)))
	{
		// 예외처리
		MessageBox(g_hWnd, "빈 비트맵 생성에 실패했습니다.", "실패", MB_OK);
	}*/

	srand(time(NULL));
	SceneManager::GetSingleton()->ChangeScene("타이틀");

	isInit = true;

	return S_OK;
}

void MainGame::Release()
{
	SAFE_RELEASE(backGround);
	SAFE_RELEASE(backBuffer);

	SoundManager::GetSingleton()->Release();
	TimerManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	HDC backDC = backBuffer->GetMemDC();
	backGround->Render(backDC, 0, 0);

	//char szText[128] = "";

	//wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	//TextOut(backDC, 10, 5, szText, strlen(szText));

	//wsprintf(szText, "Clicked X : %d, Y : %d",
	//	mouseData.clickedPosX, mouseData.clickedPosY);
	//TextOut(backDC, 10, 30, szText, strlen(szText));

	SceneManager::GetSingleton()->Render(backDC);


	// 백버퍼 복사(출력)
	backBuffer->Render(hdc, 0, 0);
}

void MainGame::ImageInit()
{
	// 타이틀 이미지
	ImageManager::GetSingleton()->AddImage("ButPlayStart", "Image/start.bmp", 350, 100, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("ButMapTool", "Image/maptool.bmp", 95 * 3, 26 * 3, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("ButExit", "Image/exit.bmp", 50 * 3, 25 * 3, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("ButOptions", "Image/options.bmp", 68 * 3, 25 * 3, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("Logo", "Image/logo.bmp", 400, 250, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("MainImage", "Image/mainImage.bmp", 400 * IMAGE_ZOOM, 256 * IMAGE_ZOOM, 25, 16, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("TitleScene", "Image/titleScene.bmp", WINSIZE_MAP_X, WINSIZE_MAP_Y);
	ImageManager::GetSingleton()->AddImage("TitleSceneSelectTank", "Image/titleSceneSelectTank.bmp", 73, 94, 1, 2);

	ImageManager::GetSingleton()->AddImage("WaterAndEagle", "Image/waterAndEagle2x.bmp", 14 * IMAGE_ZOOM * 2, 14 * IMAGE_ZOOM * 2, 2, 2, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("SampleTile", "Image/ForagerTileMap.bmp", 14 * IMAGE_ZOOM * SAMPLE_TILE_X, 14 * IMAGE_ZOOM * SAMPLE_TILE_Y, SAMPLE_TILE_X, SAMPLE_TILE_Y, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("SampleTileSub", "Image/ForagerTileMapSub.bmp", 14 * IMAGE_ZOOM * SAMPLE_TILE_X, 14 * IMAGE_ZOOM * 1, SAMPLE_TILE_X, 1, true, MAGENTA);

	//타일맵툴 이미지
	ImageManager::GetSingleton()->AddImage("SelectTileEdge", "Image/selectTileEdge.bmp", 14 * IMAGE_ZOOM * 2, 14 * IMAGE_ZOOM * 2, 2, 2, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("SaveLoadExitButtonF", "Image/buttonForMap.bmp", 120 * 4, 30 * 4, 3, 2, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("BackG", "Image/background.bmp", WINSIZE_MAP_X, WINSIZE_MAP_Y, 1, 1);
	ImageManager::GetSingleton()->AddImage("Wave", "Image/WAVES.bmp", 56 * 24, 56, 24, 1, true, MAGENTA);

	// 플레이어 이미지
	ImageManager::GetSingleton()->AddImage("PlayerStand", "Image/player/stand.bmp", 640, 100, 10, 2, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("PlayerRun", "Image/player/run.bmp", 512, 100, 8, 2, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("PlayerRoll", "Image/player/roll.bmp", 840, 164, 10, 2, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("PlayerAttack", "Image/player/attack2.bmp", 390, 130, 6, 2, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("PlayerARoll", "Image/player/Aroll.bmp", 700, 200, 10, 2, true, MAGENTA);


	// ui
	ImageManager::GetSingleton()->AddImage("life1", "Image/UI/life1.bmp", 34, 30, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("life2", "Image/UI/life2.bmp", 34, 30, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("life3", "Image/UI/life3.bmp", 34, 30, 1, 1, true, MAGENTA);
	//ImageManager::GetSingleton()->AddImage("lifeMovee", "Image/lifeMove.bmp", 42*5, 38, 5, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("lifeMove", "Image/UI/lifeMovee.bmp", 42 * 4, 38, 4, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("EX1", "Image/UI/EX.bmp", 800, 30, 1, 1, false);
	ImageManager::GetSingleton()->AddImage("EX2", "Image/UI/EXBar.bmp", 792, 22, 1, 1, false);
	ImageManager::GetSingleton()->AddImage("Sta1", "Image/UI/Stamina.bmp", 74, 26, 1, 1, false);
	ImageManager::GetSingleton()->AddImage("Sta2", "Image/UI/StaminaBar.bmp", 66, 18, 1, 1, false);
	ImageManager::GetSingleton()->AddImage("LEVEL", "Image/UI/level.bmp", 70, 16, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("Par", "Image/UI/Parentheses.bmp", 18, 16, 2, 1, false);//9
	ImageManager::GetSingleton()->AddImage("number", "Image/UI/number.bmp", 140, 16, 10, 1, true, MAGENTA);//7
	ImageManager::GetSingleton()->AddImage("slush", "Image/UI/Slush.bmp", 12, 16, 1, 1, true, MAGENTA);//6
	ImageManager::GetSingleton()->AddImage("number2", "Image/UI/number2.bmp", 240, 30, 10, 1, true, MAGENTA);//7
	ImageManager::GetSingleton()->AddImage("goldUI", "Image/UI/gold.bmp", 30, 30, 1, 1, true, MAGENTA);//7
	ImageManager::GetSingleton()->AddImage("buyUI", "Image/UI/buyUI.bmp", 228, 78, 1, 1, true, MAGENTA);//7
	ImageManager::GetSingleton()->AddImage("flagUI", "Image/UI/flag.bmp", 510, 105, 5, 1, true, MAGENTA);//7
	ImageManager::GetSingleton()->AddImage("selUI", "Image/UI/sel.bmp", 2536, 324, 8, 1, true, MAGENTA);//7

	// 오브젝트
	ImageManager::GetSingleton()->AddImage("berry", "Image/object/berry.bmp", 56 * 2, 56, 2, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("rock", "Image/object/rock.bmp", 56 * 2, 56, 2, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("tree", "Image/object/Tree.bmp", 56 * 5, 56 * 3, 5, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("objhp", "Image/object/objhp.bmp", 49, 17, 1, 1, false);
	ImageManager::GetSingleton()->AddImage("objhpbar", "Image/object/objhpbar.bmp", 41, 9, 1, 1, false);


	ImageManager::GetSingleton()->AddImage("fiber", "Image/object/fiber.bmp", 56, 56, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("Flower", "Image/object/Flower.bmp", 56 * 2, 56, 2, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("rock2", "Image/object/rock2.bmp", 56, 56, 1, 1, true, MAGENTA);
	
	ImageManager::GetSingleton()->AddImage("berry2", "Image/object/berry2.bmp", 56, 56, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("citrus", "Image/object/citrus.bmp", 56, 56, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("coal", "Image/object/coal.bmp", 56, 56, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("wood", "Image/object/wood.bmp", 56, 56, 1, 1, true, MAGENTA);


	//메뉴
	ImageManager::GetSingleton()->AddImage("menuUp", "Image/menu/menu.bmp", 468, 104, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("menuBuy", "Image/menu/buyicon.bmp", 468, 104, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("menuBuild", "Image/menu/buildicon.bmp", 468, 104, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("menuEq", "Image/menu/eqicon.bmp", 468, 104, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("menuItem", "Image/menu/itemicon.bmp", 468, 104, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("menuSet", "Image/menu/seticon.bmp", 468, 104, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("muneBack", "Image/menu/MenuBack.bmp", WINSIZE_MAP_X, WINSIZE_MAP_Y, 1, 1, false);
	ImageManager::GetSingleton()->AddImage("menuCan", "Image/menu/can.bmp", 88, 88, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("menuKey", "Image/menu/menuKey.bmp", 6600, 104, 10, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("menuExit", "Image/menu/menuExit.bmp", 400, 573, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("exitSel", "Image/menu/exitSel.bmp", 380, 44, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("landBuy", "Image/menu/land.bmp", 296, 296, 1, 1, true, MAGENTA);
	ImageManager::GetSingleton()->AddImage("bulid", "Image/menu/bulid.bmp", 290, WINSIZE_MAP_Y, 1, 1, true, MAGENTA);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_WINDOWPOSCHANGED:
		if (isInit)
			Render();
		break;
	case WM_SYSCOMMAND:
		switch (wParam & 0xfff0) {
		case SC_MOVE:
		case SC_SIZE:
			TimerManager::GetSingleton()->SetIsSC_MOVE(true);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInit = false;
}


MainGame::~MainGame()
{
}
