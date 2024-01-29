#include "ObjRE.h"
#include "Image.h"
#include "Tile.h"
#include "Player.h"

HRESULT ObjRE::Init(CollisionManager* colMar)
{
	return E_NOTIMPL;
}

void ObjRE::Release()
{
}

void ObjRE::Update()
{
	if (!check)
		check = true;
}

void ObjRE::Render(HDC hdc, float X, float Y)
{
	img->Render(hdc, (pos.x - X) + (TILE_SIZE / 2), (pos.y - Y) + (TILE_SIZE / 2));
	//Rectangle(hdc, rc.left- X, rc.top-Y, rc.right-X, rc.bottom-Y);
}

ObjRE::ObjRE(OBJEKRESULT obj, int posx, int posy)
{
	switch (obj)
	{
	case OBJEKRESULT::WOOD:
		img = ImageManager::GetSingleton()->FindImage("wood");
		objRe = obj;
		pos = { posx , posy };
		rc = { posx + 30, posy + 30, posx + 75, posy + 70 };
		check = false;
		break;
	case OBJEKRESULT::SHIP:
		img = ImageManager::GetSingleton()->FindImage("citrus");
		objRe = obj;
		pos = { posx , posy };
		rc = { posx + 45, posy + 40, posx + 75, posy + 70 };
		check = false;
		break;
	case OBJEKRESULT::BERRY:
		img = ImageManager::GetSingleton()->FindImage("berry2");
		objRe = obj;
		pos = { posx , posy };
		rc = { posx + 45, posy + 40, posx + 75, posy + 70 };
		break;
	case OBJEKRESULT::ROCK:
		img = ImageManager::GetSingleton()->FindImage("rock2");
		objRe = obj;
		pos = { posx , posy };
		rc = { posx + 45, posy + 40, posx + 75, posy + 70 };
		check = false;
		break;
		//case OBJEKRESULT::GOLD2://8 ö10
		//	img = ImageManager::GetSingleton()->FindImage("rock");
		//	objRe = obj;
		//	pos = { posx , posy };
		//	rc = { posx, posy , posx, posy };
		//	break;
	case OBJEKRESULT::COAL2://8 ö10
		img = ImageManager::GetSingleton()->FindImage("coal");
		objRe = obj;
		pos = { posx , posy };
		rc = { posx + 45, posy + 40, posx + 75, posy + 70 };
		check = false;
		break;
		//case OBJEKRESULT::IRON2://8 ö10
		//	img = ImageManager::GetSingleton()->FindImage("rock");
		//	objRe = obj;
		//	pos = { posx , posy };
		//	rc = { posx, posy , posx, posy };
		//	break;
	case OBJEKRESULT::FIBER://8 ö10
		img = ImageManager::GetSingleton()->FindImage("fiber");
		objRe = obj;
		pos = { posx , posy };
		rc = { posx + 45, posy + 40, posx + 75, posy + 70 };
		check = false;
		break;
	}
}
