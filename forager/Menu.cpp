#include "Menu.h"
#include "Image.h"
#include "Animation.h"
#include "Button.h"
#include "ButtonFunction.h"
#include "Tile.h"
#include "Player.h"

HRESULT Menu::Init()
{
	menuUp = ImageManager::GetSingleton()->FindImage("menuUp");
	muneBack = ImageManager::GetSingleton()->FindImage("muneBack");
	menuCan = ImageManager::GetSingleton()->FindImage("menuCan");
	menuKey = ImageManager::GetSingleton()->FindImage("menuKey");
	menuKeyAni = new Animation;
	menuKeyAni->Init(menuKey->GetWidth(), menuKey->GetHeight(), menuKey->GetFrameWidth(), menuKey->GetFrameHeight());
	menuKeyAni->SetPlayFrame(true, true);
	menuKeyAni->SetKeyFrameUpdateTime(0.04f);
	menuKeyAni->Start();
	menuBuy = ImageManager::GetSingleton()->FindImage("menuBuy");
	menuBuild = ImageManager::GetSingleton()->FindImage("menuBuild");
	menuEq = ImageManager::GetSingleton()->FindImage("menuEq");
	menuItem = ImageManager::GetSingleton()->FindImage("menuItem");
	menuSet = ImageManager::GetSingleton()->FindImage("menuSet");
	menuExit = ImageManager::GetSingleton()->FindImage("menuExit");
	exitSel = ImageManager::GetSingleton()->FindImage("exitSel");
	exitGo = false;
	bulid = ImageManager::GetSingleton()->FindImage("bulid");
	landBuy = ImageManager::GetSingleton()->FindImage("landBuy");

	wood = ImageManager::GetSingleton()->FindImage("wood");
	citrus = ImageManager::GetSingleton()->FindImage("citrus");
	berry2 = ImageManager::GetSingleton()->FindImage("berry2");
	rock2 = ImageManager::GetSingleton()->FindImage("rock2");
	coal = ImageManager::GetSingleton()->FindImage("coal");
	fiber = ImageManager::GetSingleton()->FindImage("fiber");

	number = ImageManager::GetSingleton()->FindImage("number2");

	for (int i = 0; i < 5; i++)
	{
		rc[i] = { 414 + (i * 92), 16, 414 + 84 + (i * 92), 16 + 88 };
	}
	rc5 = { 440, 632, 440 + 380, 632 + 44 };
	EixtButton = new Button();
	EixtButton->Init("exitSel", 440 + 190, 632 + 22, { 0,0 }, { 0,0 });

	Argument1* argExit = new Argument1();
	argExit->sceneName = "타이틀";
	argExit->loadingSceneName = "";
	EixtButton->SetButtonFunc(&ButtonFunction::ChangeScene, Argument_Kind::Argument1, argExit);
	doubleCehck = false;
	doubleTimer = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			rc4[(i * 5) + j] = { 62 + (j * 336), 72 + (i * 336),  62 + (j * 336) + 296, 72 + (i * 336) + 296 };
			mapIt[(i * 5) + j] = false;
			mapIt2[(i * 5) + j] = false;
			if (((i * 5) + j) == 12)
			{
				mapIt[(i * 5) + j] = true;
				mapIt2[(i * 5) + j] = true;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			rc2[(i * 8) + j] = { 260 + (j * 96), 268 + (i * 96), 260 + (j * 96) + 88 , 268 + (i * 96) + 88 };
			rc2map[(i * 8) + j] = false;
			rc2obj[(i * 8) + j] = END4;
			objNum[(i * 8) + j] = 0;
		}
	}



	menuNum = 2;

	return E_NOTIMPL;
}

void Menu::Release()
{
	SAFE_RELEASE(EixtButton);
}

void Menu::Update()
{
	menuKeyAni->UpdateFrame();

	if (KeyManager::GetSingleton()->IsOnceKeyDown(KEY_E))
	{
		menuNum++;
		if (menuNum >= 6)
			menuNum = 1;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(KEY_Q))
	{
		menuNum--;
		if (menuNum <= 0)
			menuNum = 5;
	}
	for (int i = 0; i < 5; i++)
	{
		if (PtInRect(&rc[i], g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
				menuNum = i + 1;
		}
	}

	int k = 0;
	map< OBJEKRESULT, int>::iterator itrinven;
	if (!player->GetInven().empty())
	{
		map< OBJEKRESULT, int> playerInven = player->GetInven();
		for (itrinven = playerInven.begin(); itrinven != playerInven.end(); itrinven++)
		{
			if ((*itrinven).second <= 0)
			{
				rc2obj[k] = END4;
				objNum[k] = 0;
			}
			else
			{
				if ((*itrinven).first == WOOD)
				{
					rc2obj[k] = WOOD;
					objNum[k] = (*itrinven).second;
				}
				else if ((*itrinven).first == SHIP)
				{
					rc2obj[k] = SHIP;
					objNum[k] = (*itrinven).second;
				}
				else if ((*itrinven).first == BERRY)
				{
					rc2obj[k] = BERRY;
					objNum[k] = (*itrinven).second;
				}
				else if ((*itrinven).first == ROCK)
				{
					rc2obj[k] = ROCK;
					objNum[k] = (*itrinven).second;
				}
				else if ((*itrinven).first == COAL2)
				{
					rc2obj[k] = COAL2;
					objNum[k] = (*itrinven).second;
				}
				else if ((*itrinven).first == FIBER)
				{
					rc2obj[k] = FIBER;
					objNum[k] = (*itrinven).second;
				}
			}
			k++;
		}
	}
	if (menuNum == 5)
	{
		if (PtInRect(&rc5, g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
				exitGo = true;
		}
		/*if (EixtButton)
			EixtButton->Update();*/
	}

	if (menuNum == 4)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (mapIt[(i * 5) + j])
				{
					if (((i * 5) + j) % 5 != 0) {
						if (!mapIt[(i * 5) + j - 1]) // 좌
						{
							mapIt2[(i * 5) + j - 1] = true;
						}
					}
					if (((i * 5) + j) % 5 != 4) {
						if (!mapIt[(i * 5) + j + 1]) // 우
						{
							mapIt2[(i * 5) + j + 1] = true;
						}
					}
					if (((i * 5) + j) > 4) {
						if (!mapIt[(i * 5) + j - 5]) // 상
						{
							mapIt2[(i * 5) + j - 5] = true;
						}
					}
					if (((i * 5) + j) < 20) {
						if (!mapIt[(i * 5) + j + 5]) // 하
						{
							mapIt2[(i * 5) + j + 5] = true;
						}
					}
				}
			}
		}
	}

	if (menuNum == 2)
	{
		doubleTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (doubleTimer >= 0.3f)
		{
			if (doubleCehck)
				doubleCehck = false;

			doubleTimer = 0;
		}

		for (int i = 0; i < 16; i++)
		{
			if (rc2obj[i] == OBJEKRESULT::SHIP || rc2obj[i] == OBJEKRESULT::BERRY)
			{
				if (PtInRect(&rc2[i], g_ptMouse))
				{
					if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
					{
						if (!doubleCehck)
							doubleCehck = true;
						else
						{
							if (rc2obj[i] == OBJEKRESULT::SHIP)
							{
								player->SetCitrus(1);
							}
							else
							{
								player->SetBerry(1);
							}
						}
					}
				}
			}
		}
	}

}


void Menu::Render(HDC hdc)
{
	muneBack->AlphaRender(hdc, 0, 0, 190);
	menuUp->Render(hdc, 406, 8);
	menuKey->AnimationRender(hdc, 310 + 330, 8 + 52, menuKeyAni);

	switch (menuNum)
	{
	case 1:
		menuEq->Render(hdc, 406, 8);
		//	Rectangle(hdc, rc[0].left, rc[0].top, rc[0].right, rc[0].bottom);
		break;
	case 2:
		menuItem->Render(hdc, 406, 8);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				menuCan->Render(hdc, 260 + (j * 96), 268 + (i * 96));
			}
		}

		for (int k = 0; k < 16; k++)
		{
			if (rc2obj[k] == END4)
				continue;
			if (rc2obj[k] == WOOD)
			{
				wood->Render(hdc, rc2[k].left + 20, rc2[k].top + 20);
				numberRender(hdc, k);
			}
			else if (rc2obj[k] == SHIP)
			{
				citrus->Render(hdc, rc2[k].left + 20, rc2[k].top + 20);
				numberRender(hdc, k);
			}
			else if (rc2obj[k] == BERRY)
			{
				berry2->Render(hdc, rc2[k].left + 20, rc2[k].top + 20);
				numberRender(hdc, k);
			}
			else if (rc2obj[k] == ROCK)
			{
				rock2->Render(hdc, rc2[k].left + 20, rc2[k].top + 20);
				numberRender(hdc, k);
			}
			else if (rc2obj[k] == COAL2)
			{
				coal->Render(hdc, rc2[k].left + 20, rc2[k].top + 20);
				numberRender(hdc, k);
			}
			else if (rc2obj[k] == FIBER)
			{
				fiber->Render(hdc, rc2[k].left + 20, rc2[k].top + 20);
				numberRender(hdc, k);
			}
		}
		/*	for (int i = 0; i < 16; i++)
			{
				Rectangle(hdc, rc2[i].left, rc2[i].top, rc2[i].right, rc2[i].bottom);
			}*/
		break;
	case 3:
		menuBuild->Render(hdc, 406, 8);
		bulid->Render(hdc, WINSIZE_MAP_X - 290, 0);
		//	Rectangle(hdc, rc[2].left, rc[2].top, rc[2].right, rc[2].bottom);
		break;
	case 4:
		menuBuy->Render(hdc, 406, 8);
		//Rectangle(hdc, rc[3].left, rc[3].top, rc[3].right, rc[3].bottom);
		break;
	case 5:
		menuSet->Render(hdc, 406, 8);
		if (PtInRect(&rc5, g_ptMouse))
			exitSel->Render(hdc, 450, 632);//EixtButton->Render(hdc);

		menuExit->Render(hdc, 440, 132);
		//Rectangle(hdc, rc[4].left, rc[4].top, rc[4].right, rc[4].bottom);
		break;
	default:
		break;
	}

}

void Menu::Render(HDC hdc, int X, int Y, int MoveX, int MoveY)
{

	x = X;
	moveX = MoveX;
	y = Y;
	moveY = MoveY;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (mapIt[(i * 5) + j])// 내가
			{
				if (((i * 5) + j) % 5 != 0) {
					if (!mapIt[(i * 5) + j - 1]) // 좌
					{
						landBuy->Render(hdc, rc4[(i * 5) + j - 1].left - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j - 1].top - (Y* TILE_SIZE / 2) - MoveY);
						// Rectangle(hdc, rc4[(i * 5) + j - 1].left - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j - 1].top - (Y* TILE_SIZE / 2) - MoveY,
						//	rc4[(i * 5) + j - 1].right - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j - 1].bottom - (Y* TILE_SIZE / 2) - MoveY);

					}
				}
				if (((i * 5) + j) % 5 != 4) {
					if (!mapIt[(i * 5) + j + 1]) // 우
					{
						landBuy->Render(hdc, rc4[(i * 5) + j + 1].left - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j + 1].top - (Y* TILE_SIZE / 2) - MoveY);
						// Rectangle(hdc, rc4[(i * 5) + j + 1].left - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j + 1].top - (Y* TILE_SIZE / 2) - MoveY,
						//	rc4[(i * 5) + j + 1].right - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j + 1].bottom - (Y* TILE_SIZE / 2) - MoveY);
					}
				}
				if (((i * 5) + j) > 4) {
					if (!mapIt[(i * 5) + j - 5]) // 상
					{
						landBuy->Render(hdc, rc4[(i * 5) + j - 5].left - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j - 5].top - (Y* TILE_SIZE / 2) - MoveY);
						// Rectangle(hdc, rc4[(i * 5) + j - 5].left - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j - 5].top - (Y* TILE_SIZE / 2) - MoveY,
						//	rc4[(i * 5) + j - 5].right - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j - 5].bottom - (Y* TILE_SIZE / 2) - MoveY);
					}
				}
				if (((i * 5) + j) < 20) {
					if (!mapIt[(i * 5) + j + 5]) // 하
					{
						landBuy->Render(hdc, rc4[(i * 5) + j + 5].left - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j + 5].top - (Y* TILE_SIZE / 2) - MoveY);
						// Rectangle(hdc, rc4[(i * 5) + j + 5].left - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j + 5].top - (Y* TILE_SIZE / 2) - MoveY,
						//	rc4[(i * 5) + j + 5].right - (X * TILE_SIZE / 2) - MoveX, rc4[(i * 5) + j + 5].bottom - (Y* TILE_SIZE / 2) - MoveY);
					}
				}
			}

		}
	}
}

void Menu::numberRender(HDC hdc, int k)
{
	if (objNum[k] > 99)
	{
		number->FrameRender(hdc, rc2[k].left + 28, rc2[k].top + 15, objNum[k] / 100, 0);
		number->FrameRender(hdc, rc2[k].left + 52, rc2[k].top + 15, objNum[k] % 100 / 10, 0);
		number->FrameRender(hdc, rc2[k].left + 76, rc2[k].top + 15, objNum[k] % 10, 0);
	}
	else if (objNum[k] > 9)
	{
		number->FrameRender(hdc, rc2[k].left + 52, rc2[k].top + 15, objNum[k] / 10, 0);
		number->FrameRender(hdc, rc2[k].left + 76, rc2[k].top + 15, objNum[k] % 10, 0);
	}
	else
	{
		number->FrameRender(hdc, rc2[k].left + 76, rc2[k].top + 15, objNum[k] % 10, 0);
	}
}
