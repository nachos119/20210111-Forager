#include "CollisionManager.h"
#include "Objek.h"
#include "Player.h"
#include "ObjManager.h"
#include "ObjRE.h"

HRESULT CollisionManager::Init()
{
	return E_NOTIMPL;
}

void CollisionManager::Release()
{
	vecObject.clear();
}

void CollisionManager::Update()
{
	for (itObject = vecObject.begin(); itObject != vecObject.end(); itObject++)
	{
		if ((*itObject)->GetHp() <= 0)
			vecObject.erase(itObject);
	}
}

void CollisionManager::Render(HDC hdc)
{
}

bool CollisionManager::CheckCollision(RECT rc)
{
	RECT tempRc;

	for (itObject = vecObject.begin(); itObject != vecObject.end(); itObject++)
	{
		if ((*itObject)->GetObjek() == OBJEK::FLOWER)
			continue;
		if (IntersectRect(&tempRc, &rc, &(*itObject)->GetRc()))
		{
			return true;
		}
	}

	return false;
}

void CollisionManager::CheckColObj(int X, int Y)
{
	for (itObject = vecObject.begin(); itObject != vecObject.end(); itObject++)
	{
		if ((abs)(player->GetPos().x - (g_ptMouse.x + X)) < 105 && (abs)(player->GetPos().y - (g_ptMouse.y + Y)) < 105)
		{
			if (PtInRect(&(*itObject)->GetRc(), { g_ptMouse.x + X, g_ptMouse.y + Y }))
			{
				(*itObject)->Update();
				if ((*itObject)->GetHp() <= 0)
				{
					objM->objectListInit((*itObject)->GetPoss().x, (*itObject)->GetPoss().y, (*itObject)->GetObjek());
					vecObject.erase(itObject);
					break;
				}
			}
		}
	}

	for (itObjek = liObjek.begin(); itObjek != liObjek.end(); itObjek++)
	{
		RECT NUM;
		if (PtInRect(&(*itObjek)->GetRc(), { g_ptMouse.x + X, g_ptMouse.y + Y }))
		{
			player->invenIt((*itObjek)->GetObjRe());
			(*itObjek)->Update();
			liObjek.erase(itObjek);
			break;
		}
		else if (IntersectRect(&NUM, &(*itObjek)->GetRc(), &player->GetRc()))
		{
			player->invenIt((*itObjek)->GetObjRe());
			(*itObjek)->Update();
			liObjek.erase(itObjek);
			break;
		}
	}
}

void CollisionManager::AddObjek(Objek* addObj)
{
	vecObject.push_back(addObj);
}

void CollisionManager::AddList(ObjRE * addObj)
{
	liObjek.push_back(addObj);
}
