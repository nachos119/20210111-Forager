#include "PlayScene.h"
#include "Camera.h"
#include "Player.h"
#include "Menu.h"
#include "CollisionManager.h"
#include "TileMap.h"
#include "UIManager.h"
#include "ObjManager.h"
#include "Image.h"
#include "Animation.h"
#include "ObjRE.h"

HRESULT PlayScene::Init()
{
	SetWindowSize(0, 0, WINSIZE_MAP_X, WINSIZE_MAP_Y);

	player = new Player;
	player->Init();

	setCamera = new Camera;
	setCamera->SetTarget(player);
	setCamera->Init();

	Tilemap = new TileMap;
	Tilemap->Init(setCamera);
	player->SetTileInfo(Tilemap->GettileInfo());

	UImanager = new UIManager;
	UImanager->Init(player);

	colMar = new CollisionManager;

	Objmanager = new ObjManager;
	Objmanager->Init(Tilemap->GettileInfo(), setCamera, colMar, player);

	player->SetCollision(colMar);
	colMar->SetPlayer(player);

	menuScene = new Menu;
	menuScene->Init();
	menuScene->SetMap(Tilemap->GettileInfo());
	player->SetMenu(menuScene);
	menuScene->SetPlayer(player);
	setCamera->SetMenu(menuScene);
	setCamera->SetTile(Tilemap);
	menuOn = false;

	colMar->SetObjM(Objmanager);

	Tilemap->SetObjM(Objmanager);

	number2 = ImageManager::GetSingleton()->FindImage("number2");
	goldUI = ImageManager::GetSingleton()->FindImage("goldUI");
	buyUI = ImageManager::GetSingleton()->FindImage("buyUI");
	flagUI = ImageManager::GetSingleton()->FindImage("flagUI");
	selUI = ImageManager::GetSingleton()->FindImage("selUI");
	flagUIAni = new Animation();
	flagUIAni->Init(flagUI->GetWidth(), flagUI->GetHeight(), flagUI->GetFrameWidth(), flagUI->GetFrameHeight());
	flagUIAni->SetPlayFrame(true, true);
	flagUIAni->SetKeyFrameUpdateTime(0.08f);
	flagUIAni->Start();
	selUIAni = new Animation();
	selUIAni->Init(selUI->GetWidth(), selUI->GetHeight(), selUI->GetFrameWidth(), selUI->GetFrameHeight());
	selUIAni->SetPlayFrame(true, true);
	selUIAni->SetKeyFrameUpdateTime(0.05f);
	selUIAni->Start();
	
	objTimer = 0;

	BackBrush = CreateSolidBrush(RGB(48, 149, 252));
	NULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	return S_OK;
}

void PlayScene::Release()
{
	DeleteObject(BackBrush);
	DeleteObject(NULLBrush);
	DeleteObject(oldBrush);
	SAFE_DELETE(Tilemap);
	SAFE_DELETE(UImanager);
	SAFE_DELETE(Objmanager);
	SAFE_DELETE(colMar);
	SAFE_DELETE(setCamera);
	SAFE_DELETE(player);
}

void PlayScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		/*SceneManager::GetSingleton()->ChangeScene("타이틀");
		return;*/

		if (menuOn)
		{
			menuOn = false;
			menuScene->SetMenu(2);
		}
		else if (!menuOn)
			menuOn = true;
	}

	

	player->SetTileInfo(Tilemap->GettileInfo());
	colMar->CheckColObj((setCamera->GetCenterX() /*- PLAYER_CENTER_X*/), (setCamera->GetCenterY() /*- PLAYER_CENTER_Y*/));
	setCamera->Update(menuScene->GetMenu());


	Tilemap->Update();
	UImanager->Update();
	Objmanager->Update();

	player->Update(menuOn);

	if (menuOn)
	{
		menuScene->Update();
		flagUIAni->UpdateFrame();
		selUIAni->UpdateFrame();

		if (menuScene->GetExit())
			SceneManager::GetSingleton()->ChangeScene("타이틀");
	}

	if (menuScene->GetMenu() != 4) 
	{
		objTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (objTimer >= 4)
		{
			Objmanager->objectInit((setCamera->GetCenterX()) / (TILE_SIZE), (setCamera->GetCenterY()) / (TILE_SIZE), 1);
			objTimer = 0;
		}
	}
}

void PlayScene::Render(HDC hdc)
{
	oldBrush = (HBRUSH)SelectObject(hdc, BackBrush);
	PatBlt(hdc, 0, 0, WINSIZE_MAP_X, WINSIZE_MAP_Y, PATCOPY); // BackBrush
	SelectObject(hdc, oldBrush);
	oldBrush = (HBRUSH)SelectObject(hdc, NULLBrush);

	//int X = (setCamera->GetCenterX() - PLAYER_CENTER_X) / TILE_SIZE;//9
	//int Y = (setCamera->GetCenterY() - PLAYER_CENTER_Y) / TILE_SIZE;//14

	//int MoveX = (setCamera->GetCenterX() - PLAYER_CENTER_X) % TILE_SIZE;
	//int MoveY = (setCamera->GetCenterY() - PLAYER_CENTER_Y) % TILE_SIZE;


	if (menuScene->GetMenu() == 4)
	{
		int X = (setCamera->GetCenterX()) / (TILE_SIZE);//9
		int Y = (setCamera->GetCenterY()) / (TILE_SIZE);//14

		//X -= (setCamera->GetCenterX()) / (TILE_SIZE * 2);
		//Y -= (setCamera->GetCenterY()) / (TILE_SIZE * 2);

		int MoveX = (setCamera->GetCenterX()) % (TILE_SIZE / 2);
		int MoveY = (setCamera->GetCenterY()) % (TILE_SIZE / 2);

		Tilemap->Render(hdc, X, Y, MoveX, MoveY, menuScene->GetMenu());

		Objmanager->Render(hdc, X, Y, MoveX, MoveY, 2);

		player->Render(hdc, X, Y, MoveX, MoveY, 2);

		menuScene->Render(hdc, X, Y, MoveX, MoveY);

		for (int i = 0; i < 25; i++)
		{
			RECT tempRC4;
			tempRC4 = menuScene->GetRc4(i);
			if (PtInRect(&tempRC4, g_ptMouse))
			{
				selUI->AnimationRender(hdc, tempRC4.left + 148, tempRC4.top + 148, selUIAni);

				if (!menuScene->GetMapIt(i))
				{
					if (menuScene->GetMapIt2(i))
					{
						flagUI->AnimationRender(hdc, tempRC4.left + 148, tempRC4.top + 80, flagUIAni);
						// 골드
						if (setCamera->GetGold() > 999)
						{
							number2->FrameRender(hdc, tempRC4.left + 186, tempRC4.top + 223, setCamera->GetGold() / 1000, 0);//
							number2->FrameRender(hdc, tempRC4.left + 210, tempRC4.top + 223, setCamera->GetGold() % 1000 / 100, 0);//
							number2->FrameRender(hdc, tempRC4.left + 234, tempRC4.top + 223, setCamera->GetGold() % 100 / 10, 0);//
							number2->FrameRender(hdc, tempRC4.left + 258, tempRC4.top + 223, setCamera->GetGold() % 10, 0);
							goldUI->Render(hdc, tempRC4.left + 140, tempRC4.top + 208);
						}
						else if (setCamera->GetGold() > 99)
						{
							number2->FrameRender(hdc, tempRC4.left + 196, tempRC4.top + 223, setCamera->GetGold() / 100, 0);//
							number2->FrameRender(hdc, tempRC4.left + 220, tempRC4.top + 223, setCamera->GetGold() % 100 / 10, 0);//
							number2->FrameRender(hdc, tempRC4.left + 244, tempRC4.top + 223, setCamera->GetGold() % 10, 0);
							goldUI->Render(hdc, tempRC4.left + 148, tempRC4.top + 208);
						}
						else
						{
							number2->FrameRender(hdc, tempRC4.left + 200, tempRC4.top + 223, setCamera->GetGold() / 10, 0);//
							number2->FrameRender(hdc, tempRC4.left + 224, tempRC4.top + 223, setCamera->GetGold() % 10, 0);
							goldUI->Render(hdc, tempRC4.left + 152, tempRC4.top + 208);
						}
						buyUI->Render(hdc, tempRC4.left + 34, tempRC4.top + 160);
					}
				}
			}
		}

	}
	else
	{
		int X = (setCamera->GetCenterX()) / TILE_SIZE;//9
		int Y = (setCamera->GetCenterY()) / TILE_SIZE;//14

		int MoveX = (setCamera->GetCenterX()) % TILE_SIZE;
		int MoveY = (setCamera->GetCenterY()) % TILE_SIZE;

		Tilemap->Render(hdc, X, Y, MoveX, MoveY, menuScene->GetMenu());

		Objmanager->Render(hdc, X, Y);

		//for (itObject = vecObject.begin(); itObject != vecObject.end(); itObject++)
		//{
		//	if ((abs)(player->GetPos().x - (g_ptMouse.x + setCamera->GetCenterX())) < 105 
		//		&& (abs)(player->GetPos().y - (g_ptMouse.y + setCamera->GetCenterY())) < 105)
		//	{
		//		if (PtInRect(&(*itObject)->GetRc(), { g_ptMouse.x + setCamera->GetCenterX(), g_ptMouse.y + setCamera->GetCenterY() }))
		//		{
		//			// 이미지 랜더
		//		}
		//	}
		//}


		player->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
		// Rectangle(hdc, player->GetRc().left, player->GetRc().top, player->GetRc().right, player->GetRc().bottom);
		Objmanager->subRender(hdc);

	}

	UImanager->Render(hdc, menuOn);


	if (menuOn)
		menuScene->Render(hdc);

	// 골드
	if (player->GetGold() > 9999)
	{
		number2->FrameRender(hdc, 55, WINSIZE_MAP_Y - 23, player->GetGold() / 10000, 0);//
		number2->FrameRender(hdc, 79, WINSIZE_MAP_Y - 23, player->GetGold() % 10000 / 1000, 0);//
		number2->FrameRender(hdc, 103, WINSIZE_MAP_Y - 23, player->GetGold() % 1000 / 100, 0);//
		number2->FrameRender(hdc, 127, WINSIZE_MAP_Y - 23, player->GetGold() % 100 / 10, 0);//
		number2->FrameRender(hdc, 151, WINSIZE_MAP_Y - 23, player->GetGold() % 10, 0);
		goldUI->Render(hdc, 8, WINSIZE_MAP_Y - 38);
	}
	else if (player->GetGold() > 999)
	{
		number2->FrameRender(hdc, 55, WINSIZE_MAP_Y - 23, player->GetGold() / 1000, 0);//
		number2->FrameRender(hdc, 79, WINSIZE_MAP_Y - 23, player->GetGold() % 1000 / 100, 0);//
		number2->FrameRender(hdc, 103, WINSIZE_MAP_Y - 23, player->GetGold() % 100 / 10, 0);//
		number2->FrameRender(hdc, 127, WINSIZE_MAP_Y - 23, player->GetGold() % 10, 0);
		goldUI->Render(hdc, 8, WINSIZE_MAP_Y - 38);
	}
	else if (setCamera->GetGold() > 99)
	{
		number2->FrameRender(hdc, 55, WINSIZE_MAP_Y - 23, player->GetGold() / 100, 0);//
		number2->FrameRender(hdc, 79, WINSIZE_MAP_Y - 23, player->GetGold() % 100 / 10, 0);//
		number2->FrameRender(hdc, 103, WINSIZE_MAP_Y - 23, player->GetGold() % 10, 0);
		goldUI->Render(hdc, 8, WINSIZE_MAP_Y - 38);
	}
	else
	{
		number2->FrameRender(hdc, 55, WINSIZE_MAP_Y - 23, player->GetGold() / 10, 0);//
		number2->FrameRender(hdc, 79, WINSIZE_MAP_Y - 23, player->GetGold() % 10, 0);
		goldUI->Render(hdc, 8, WINSIZE_MAP_Y - 38);
	}


	TimerManager::GetSingleton()->Render(hdc);

	SelectObject(hdc, oldBrush);
}




