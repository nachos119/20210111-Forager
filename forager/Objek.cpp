#include "Objek.h"
#include "Image.h"
#include "Animation.h"
#include "Tile.h"
#include "Player.h"

HRESULT Objek::Init()
{
	return S_OK;
}

void Objek::Release()
{

}

void Objek::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		attackGauge += TimerManager::GetSingleton()->GetElapsedTime();
		if (attackGauge >= 0.48f)
		{
			hp--;
			player->SetStamina(250);
			attackGauge = 0;
		}
	}

	if (hp <= 0)
	{
		player->SetEx(Ex);
	}
}

void Objek::Render(HDC hdc, float X, float Y) //, int obj)
{
	HBRUSH NULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, NULLBrush);
	if (this->objekk == TREE)
	{
		img->FrameRender(hdc, (rc.left - X - 7) + (TILE_SIZE / 2), (rc.top - Y - 18) + (TILE_SIZE / 2) - TILE_SIZE, 0, 0);
		// Rectangle(hdc, rc.left - X, rc.top - Y, rc.right - X, rc.bottom - Y);
	}
	else
	{
		img->FrameRender(hdc, (rc.left - X - 4) + (TILE_SIZE / 2), (rc.top - Y - 8) + (TILE_SIZE / 2), 0, 0);
		// Rectangle(hdc, rc.left - X, rc.top - Y, rc.right - X, rc.bottom - Y);
	}
	SelectObject(hdc, oldBrush);
}

void Objek::Render(HDC hdc, RECT rc1, float X, float Y, int half) //, int obj)
{
	//HBRUSH NULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, NULLBrush);
	if (this->objekk == TREE)
	{
		if (img)
			img->FrameRender(hdc, (rc1.left) + (TILE_SIZE/2), (rc1.top ) + (TILE_SIZE/2 ) - (TILE_SIZE / half), 0, 0, half);
		//Rectangle(hdc, rc.left - X, rc.top - Y, rc.right - X, rc.bottom - Y);
		//Rectangle(hdc, rc1.left + 7.5f, rc1.top + 27, rc1.right - 7.5f, rc1.bottom - 3);
	}
	else
	{
		if (img)
			img->FrameRender(hdc, (rc1.left) + (TILE_SIZE/2), (rc1.top ) + (TILE_SIZE/2), 0, 0, half);
		//Rectangle(hdc, rc.left - X, rc.top - Y, rc.right - X, rc.bottom - Y);
		//Rectangle(hdc, rc1.left + 3.5f, rc1.top + 6, rc1.right - 3.5f, rc1.bottom - 3);
	}
	//SelectObject(hdc, oldBrush);
}

void Objek::HPRender(HDC hdc, float X, float Y)
{
	HBRUSH NULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, NULLBrush);
	if (this->objekk == TREE)
	{
		if (hp < hpM)
		{
			objhp->Render(hdc, rc.left - X - 4, rc.bottom - Y + 16);
			objhpbar->Render(hdc, rc.left - X, rc.bottom - Y + 20, hp * 41 / hpM, 9);
		}
	}
	else
	{
		if (hp < hpM)
		{
			objhp->Render(hdc, rc.left - X - 1, rc.bottom - Y + 16);
			objhpbar->Render(hdc, rc.left - X + 3, rc.bottom - Y + 20, hp * 41 / hpM, 9);
		}
	}
	SelectObject(hdc, oldBrush);
}

Objek::Objek(OBJEK obj, int posx, int posy)
{
	switch (obj)
	{
	case OBJEK::TREE:
		img = ImageManager::GetSingleton()->FindImage("tree");
		objhp = ImageManager::GetSingleton()->FindImage("objhp");
		objhpbar = ImageManager::GetSingleton()->FindImage("objhpbar");
		objekk = obj;
		pos = { posx , posy };
		poss = { posx , posy };
		sizeX = 49;
		sizeY = 53;//29
		hp = 10;
		hpM = 10;
		attackGauge = 0;
		Ex = 4;
		rc = { posx + 7, posy + 18, posx + sizeX, posy + sizeY };
		break;
	case OBJEK::GRASS:
		img = ImageManager::GetSingleton()->FindImage("berry");
		objhp = ImageManager::GetSingleton()->FindImage("objhp");
		objhpbar = ImageManager::GetSingleton()->FindImage("objhpbar");
		objekk = obj;
		pos = { posx , posy };
		poss = { posx , posy };
		hp = 2;
		hpM = 2;
		sizeX = 52;
		sizeY = 53;//54;
		attackGauge = 0;
		Ex = 1;
		rc = { posx + 4, posy + 8, posx + sizeX, posy + sizeY };
		break;
	case OBJEK::STONE://8 ö10
		img = ImageManager::GetSingleton()->FindImage("rock");
		objhp = ImageManager::GetSingleton()->FindImage("objhp");
		objhpbar = ImageManager::GetSingleton()->FindImage("objhpbar");
		objekk = obj;
		pos = { posx , posy };
		poss = { posx , posy };
		hp = 8;
		hpM = 8;
		sizeX = 52;
		sizeY = 53;//54;
		attackGauge = 0;
		Ex = 4;
		rc = { posx + 4, posy + 8, posx + sizeX, posy + sizeY };
		break;
	case OBJEK::FLOWER://8 ö10
		img = ImageManager::GetSingleton()->FindImage("Flower");
		objhp = ImageManager::GetSingleton()->FindImage("objhp");
		objhpbar = ImageManager::GetSingleton()->FindImage("objhpbar");
		objekk = obj;
		pos = { posx , posy };
		poss = { posx , posy };
		hp = 2;
		hpM = 2;
		sizeX = 52;
		sizeY = 53;//54;
		attackGauge = 0;
		Ex = 1;
		rc = { posx + 4, posy + 8, posx + sizeX, posy + sizeY };
		break;
	}
}
