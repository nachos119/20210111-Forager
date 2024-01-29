#include "Camera.h"
#include "Menu.h"
#include "TileMap.h"
#include "Player.h"

HRESULT Camera::Init()
{
	centerX = target->GetPos().x;
	centerY = target->GetPos().y;
	startCenter = false;
	SetX = 0;
	SetY = 0;
	buyCenterX = 2;
	buyCenterY = 2;

	gold = 30;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//XY[(i * 5) + j] = { -850 + (j * 672), -336 + (i * 672) };
			XY[(i * 5) + j] = { -514 + (j * (504)), -12 + (i * (510)) };
		}
	}

	return S_OK;
}

void Camera::Release()
{
}

void Camera::Update()
{

	centerX = target->GetPos().x - PLAYER_CENTER_X + (g_ptMouse.x - PLAYER_CENTER_X) * 0.3f;
	centerY = target->GetPos().y - PLAYER_CENTER_Y + (g_ptMouse.y - PLAYER_CENTER_Y) * 0.3f;

	//centerX = ((target->GetPos().x - PLAYER_CENTER_X) * 70 + (g_ptMouse.x) * 30) / 100 + PLAYER_CENTER_X / 2;
	//centerY = ((target->GetPos().y - PLAYER_CENTER_Y) * 70 + (g_ptMouse.y) * 30) / 100 + PLAYER_CENTER_Y/2;
	/*centerX = (target->GetPos().x * 80 + (g_ptMouse.x + pos.x) * 20) / 100 - WINSIZE_MAP_X / 2;
	centerY = (target->GetPos().y * 80 + (g_ptMouse.y + pos.y) * 20) / 100 - WINSIZE_MAP_Y / 2;*/

	/*if (abs(pos.x - destPosX) > 5.0f)
		pos.x = Lerp(pos.x, destPosX, TimerManager::GetSingleton()->GetElapsedTime() * 5);
	if (abs(pos.y - destPosY) > 5.0f)
		pos.y = Lerp(pos.y, destPosY, TimerManager::GetSingleton()->GetElapsedTime() * 5);*/
		//pos.y = (player->GetPos().y * 4 + g_ptMouse.y + pos.y) / 5 - WINSIZE_Y / 2;

	if (pos.x <= 0)
	{
		pos.x = 0;
	}

	if (pos.y <= 0)
	{
		pos.y = 0;
	}

	if (pos.x >= WINSIZE_TILE_MAP * TILE_SIZE - WINSIZE_MAP_X)
	{
		pos.x = WINSIZE_TILE_MAP * TILE_SIZE - WINSIZE_MAP_X;
	}

	if (pos.y >= WINSIZE_TILE_MAP * TILE_SIZE - WINSIZE_MAP_Y)
	{
		pos.y = WINSIZE_TILE_MAP * TILE_SIZE - WINSIZE_MAP_Y;
	}
	/*centerX = target->GetPos().x;
	centerY = target->GetPos().y;*/
}

void Camera::Render(HDC hdc)
{
	//char c[32];
	//wsprintf(c, "%d, %d", (int)g_ptMouse.x + (int)pos.x, (int)g_ptMouse.y + (int)pos.y);
	//TextOut(hdc, g_ptMouse.x, g_ptMouse.y, c, (int)strlen(c));

	//wsprintf(c, "%d, %d",
	//	(int)(target->GetPos().x + g_ptMouse.x + pos.x) / 2,
	//	(int)(target->GetPos().y + g_ptMouse.y + pos.y) / 2);
	//TextOut(hdc,
	//	(int)(target->GetPos().x + g_ptMouse.x - pos.x) / 2,
	//	(int)(target->GetPos().y + g_ptMouse.y - pos.y) / 2, c, (int)strlen(c));

	//wsprintf(c, "%d, %d", (int)target->GetPos().x, (int)target->GetPos().y);
	//TextOut(hdc, int(target->GetPos().x - GetPos().x), int(target->GetPos().y - GetPos().y), c, (int)strlen(c));
}

void Camera::Update(int num)
{
	if (num == 4)
	{
		if (!startCenter)
		{
			SetCamera(target->GetPos().x, target->GetPos().y);

			startCenter = true;
		}
		else
		{
			if (g_ptMouse.x > 150 && g_ptMouse.x < WINSIZE_MAP_X - 150 && g_ptMouse.y > 115 && g_ptMouse.y < WINSIZE_MAP_Y)
			{
				for (int i = 0; i < 25; i++)
				{
					RECT tempRC4;
					tempRC4 = menu->GetRc4(i);

					if (PtInRect(&tempRC4, g_ptMouse))
					{
						if (centerX != XY[i].x)
						{
							centerX = XY[i].x;
						}
						if (centerY != XY[i].y)
						{
							centerY = XY[i].y;
						}
						//Å¬¸¯
						if (!menu->GetMapIt(i))
						{
							if (menu->GetMapIt2(i))
							{
								if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
								{
									if (target->GetGold() >= gold)
									{
										srand(time(NULL));
										int num = (rand() % 4) + 1;
										menu->SetMapIt(i);
										target->SetGold(gold);
										tile->LoadMap(num, (i + 1), (i + 1));
										gold += gold;
									}
								}
							}
						}
					}
				}
			}

		}
	}
	else
	{
		if (startCenter)
			startCenter = false;

		centerX = target->GetPos().x - PLAYER_CENTER_X + (g_ptMouse.x - PLAYER_CENTER_X) * 0.3f;
		centerY = target->GetPos().y - PLAYER_CENTER_Y + (g_ptMouse.y - PLAYER_CENTER_Y) * 0.3f;
	}
	if (pos.x <= 0)
	{
		pos.x = 0;
	}

	if (pos.y <= 0)
	{
		pos.y = 0;
	}

	if (pos.x >= WINSIZE_TILE_MAP * TILE_SIZE - WINSIZE_MAP_X)
	{
		pos.x = WINSIZE_TILE_MAP * TILE_SIZE - WINSIZE_MAP_X;
	}

	if (pos.y >= WINSIZE_TILE_MAP * TILE_SIZE - WINSIZE_MAP_Y)
	{
		pos.y = WINSIZE_TILE_MAP * TILE_SIZE - WINSIZE_MAP_Y;
	}
	/*centerX = target->GetPos().x;
	centerY = target->GetPos().y;*/
}

void Camera::SetCamera(float X, float Y)
{
	int tempX = X / TILE_SIZE;
	int tempY = Y / TILE_SIZE;


	if (tempX < 13)
	{
		centerX = XY[0].x;
	}
	else if (tempX >= 13 && tempY < 25)
	{
		centerX = XY[1].x;
	}
	else if (tempX >= 25 && tempY < 37)
	{
		centerX = XY[2].x;
	}
	else if (tempX >= 37 && tempY < 49)
	{
		centerX = XY[3].x;
	}
	else if (tempX >= 49)
	{
		centerX = XY[4].x;
	}

	if (tempY < 13)
	{
		centerY = XY[0].y;
	}
	else if (tempY >= 13 && tempY < 25)
	{
		centerY = XY[5].y;
	}
	else if (tempY >= 25 && tempY < 37)
	{
		centerY = XY[10].y;
	}
	else if (tempY >= 37 && tempY < 49)
	{
		centerY = XY[15].y;
	}
	else if (tempY >= 49)
	{
		centerY = XY[20].y;
	}
}

void Camera::SetCamera2(int XX, int YY)
{

}