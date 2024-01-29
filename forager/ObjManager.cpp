#include "ObjManager.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"
#include "Objek.h"
#include "Tile.h"
#include "Player.h"
#include "CollisionManager.h"
#include "ObjRE.h"

HRESULT ObjManager::Init()
{
	objectInit();

	return S_OK;
}

void ObjManager::Release()
{
	for (int i = 0; i < WINSIZE_TILE_MAP; i++)//Y
	{
		for (int j = 0; j < WINSIZE_TILE_MAP; j++)//X
		{
			if (tileInfo[i * WINSIZE_TILE_MAP + j].object == nullptr)
				continue;
			else
				SAFE_RELEASE(tileInfo[i * WINSIZE_TILE_MAP + j].object);

		}
	}
}

void ObjManager::Update()
{
	// 오브젝트
	for (int i = 0; i < 15; i++)//Y
	{
		for (int j = 0; j < 24; j++)//X
		{
			if ((i + (setCamera->GetCenterY()) / TILE_SIZE) < 0 || (j + (setCamera->GetCenterX()) / TILE_SIZE) < 0 || (i + (setCamera->GetCenterY()) / TILE_SIZE) > 61 || (j + (setCamera->GetCenterX()) / TILE_SIZE) > 61)
				continue;
			if (tileInfo[(i + (setCamera->GetCenterY()) / TILE_SIZE) * WINSIZE_TILE_MAP + (j + (setCamera->GetCenterX()) / TILE_SIZE)].object == nullptr)
				continue;
			if (tileInfo[(i + (setCamera->GetCenterY()) / TILE_SIZE) * WINSIZE_TILE_MAP + (j + (setCamera->GetCenterX()) / TILE_SIZE)].object->GetHp() <= 0)
			{
				//삭제해주기
				objNum--;
				SAFE_RELEASE(tileInfo[(i + (setCamera->GetCenterY()) / TILE_SIZE) * WINSIZE_TILE_MAP + (j + (setCamera->GetCenterX()) / TILE_SIZE)].object);
			}
			//if (tileInfo[(i + (setCamera->GetCenterY() - PLAYER_CENTER_Y) / TILE_SIZE) * WINSIZE_TILE_MAP + (j + (setCamera->GetCenterX() - PLAYER_CENTER_X) / TILE_SIZE)].object == nullptr)
			//	continue;
			//if (tileInfo[(i + (setCamera->GetCenterY() - PLAYER_CENTER_Y) / TILE_SIZE) * WINSIZE_TILE_MAP + (j + (setCamera->GetCenterX() - PLAYER_CENTER_X) / TILE_SIZE)].object->GetHp() <= 0)
			//	//삭제해주기
			//	SAFE_RELEASE(tileInfo[(i + (setCamera->GetCenterY() - PLAYER_CENTER_Y) / TILE_SIZE) * WINSIZE_TILE_MAP + (j + (setCamera->GetCenterX() - PLAYER_CENTER_X) / TILE_SIZE)].object);
		}
	}

	for (int j = 0; j < 100; j++)
	{
		if (ReObj[j] == nullptr)
			continue;
		if (ReObj[j]->GetCheck())
		{
			ReObj[j] = nullptr;
		}
	}
}

void ObjManager::Render(HDC hdc)
{
}

HRESULT ObjManager::Init(TILE_INFO * tileInfo, Camera * setCamera, CollisionManager * colMar, Player * player)
{
	this->tileInfo = tileInfo;
	this->setCamera = setCamera;
	this->colMar = colMar;
	this->player = player;

	randNum1 = 0;
	randNum2 = 0;
	randOb = 0;
	objNum = 0;
	objectInit();

	for (int j = 0; j < 100; j++)
	{
		ReObj[j] = nullptr;
	}

	return S_OK;
}

void ObjManager::Render(HDC hdc, int X, int Y)
{
	// 오브젝트
	for (int i = 0; i < 15; i++)//Y
	{
		for (int j = 0; j < 24; j++)//X
		{
			if (i + Y < 0 || (j + X) < 0 || (i + Y) > 61 || (j + X) > 61)
				continue;
			if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].object == nullptr)
				continue;

			tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].object->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
		}
	}
	for (int i = 0; i < 15; i++)//Y
	{
		for (int j = 0; j < 24; j++)//X
		{
			if (i + Y < 0 || (j + X) < 0 || (i + Y) > 61 || (j + X) > 61)
				continue;
			if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].object == nullptr)
				continue;

			tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].object->HPRender(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
		}
	}

	for (int j = 0; j < 100; j++)
	{
		if (ReObj[j] == nullptr)
			continue;

		ReObj[j]->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
	}
}

void ObjManager::Render(HDC hdc, int X, int Y, int MoveX, int MoveY, int half)
{
	RECT rc;
	// 오브젝트
	for (int i = 0; i + Y < WINSIZE_TILE_MAP; i++)//Y
	{
		for (int j = 0; j + X < WINSIZE_TILE_MAP; j++)//X
		{
			if (i + Y < 0 || (j + X) < 0 || (i + Y) > 61 || (j + X) > 61)
				continue;
			if (tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].object == nullptr)
				continue;
			rc = { j * (TILE_SIZE / 2) - MoveX,	i *  (TILE_SIZE / 2) - MoveY, j *  (TILE_SIZE / 2) + (TILE_SIZE / 2) - MoveX, i *  (TILE_SIZE / 2) + (TILE_SIZE / 2) - MoveY };
			tileInfo[(i + Y) * WINSIZE_TILE_MAP + (j + X)].object->Render(hdc, rc, (setCamera->GetCenterX()), (setCamera->GetCenterY()), half);
		}
	}
}

void ObjManager::subRender(HDC hdc)
{
	int leftIndX = (player->GetRc().bottom / TILE_SIZE) * WINSIZE_TILE_MAP + (player->GetRc().left / TILE_SIZE);
	int rightIndX = (player->GetRc().bottom / TILE_SIZE) * WINSIZE_TILE_MAP + (player->GetRc().right / TILE_SIZE);
	int leftIndX2 = (player->GetRc().bottom / TILE_SIZE + 1) * WINSIZE_TILE_MAP + (player->GetRc().left / TILE_SIZE);
	int rightIndX2 = (player->GetRc().bottom / TILE_SIZE + 1) * WINSIZE_TILE_MAP + (player->GetRc().right / TILE_SIZE);
	int leftIndX3 = (player->GetRc().bottom / TILE_SIZE + 2) * WINSIZE_TILE_MAP + (player->GetRc().left / TILE_SIZE);
	int rightIndX3 = (player->GetRc().bottom / TILE_SIZE + 2) * WINSIZE_TILE_MAP + (player->GetRc().right / TILE_SIZE);
	// 현재 위치 or 다음위치
	if (tileInfo[leftIndX].object != nullptr) {
		if (leftIndX > 0 && leftIndX < 3844) {
			tileInfo[leftIndX].object->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
		}
	}
	if (leftIndX != rightIndX) {
		if (tileInfo[rightIndX].object != nullptr) {
			if (rightIndX > 0 && rightIndX < 3844)
				tileInfo[rightIndX].object->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
		}
	}
	// 다음
	if (tileInfo[leftIndX2].object != nullptr) {
		if (leftIndX2 > 0 && leftIndX2 < 3844) {
			if (tileInfo[leftIndX2].object->GetObjek() == OBJEK::TREE) {
				tileInfo[leftIndX2].object->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
			}
		}
	}
	if (leftIndX2 != rightIndX2) {
		if (tileInfo[rightIndX2].object != nullptr) {
			if (rightIndX2 > 0 && rightIndX2 < 3844) {
				if (tileInfo[rightIndX2].object->GetObjek() == TREE)
					tileInfo[rightIndX2].object->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
			}
		}
	}
	// 그다음
	if (tileInfo[leftIndX3].object != nullptr) {
		if (leftIndX3 > 0 && leftIndX3 < 3844) {
			if (tileInfo[leftIndX3].object->GetObjek() == OBJEK::TREE) {
				tileInfo[leftIndX3].object->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
			}
		}
	}
	if (leftIndX3 != rightIndX3) {
		if (tileInfo[rightIndX3].object != nullptr) {
			if (rightIndX3 > 0 && rightIndX3 < 3844) {
				if (tileInfo[rightIndX3].object->GetObjek() == TREE)
					tileInfo[rightIndX3].object->Render(hdc, (setCamera->GetCenterX()), (setCamera->GetCenterY()));
			}
		}
	}
}

void ObjManager::objectInit()
{
	//int X = (setCamera->GetCenterX()) / TILE_SIZE;//9
	//int Y = (setCamera->GetCenterY()) / TILE_SIZE;//14

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		randNum1 = rand() % WINSIZE_TILE_MAP;
		randNum2 = rand() % WINSIZE_TILE_MAP;	// 3 + 1;

		RECT tempRc;
		RECT tempRc2 = { (randNum2)* TILE_SIZE, (randNum1)* TILE_SIZE,
			(randNum2)* TILE_SIZE + TILE_SIZE, (randNum1)* TILE_SIZE + TILE_SIZE };


		if (tileInfo[(randNum1)* WINSIZE_TILE_MAP + (randNum2)].terrain == WATER || tileInfo[(randNum1)* WINSIZE_TILE_MAP + (randNum2)].terrain == CLIFF)
		{
			i--;
			continue;
		}
		else if (IntersectRect(&tempRc, &player->GetRc(), &tempRc2))
		{
			i--;
			continue;
		}

		randOb = rand() % 4 + 1;

		if (tileInfo[(randNum1)* WINSIZE_TILE_MAP + (randNum2)].terrain == LAND)
		{
			if (tileInfo[(randNum1)* WINSIZE_TILE_MAP + (randNum2)].object != nullptr)
			{
				i--;
			}
			else
			{
				//tileInfo[(randNum1 + Y) * WINSIZE_TILE_MAP + (randNum2 + X)].object = (OBJEK)randOb;
				int posy = (randNum1)* TILE_SIZE;		//WINSIZE_TILE_MAP + (randNum2 + X)) * TILE_SIZE;
				int posx = (randNum2)* TILE_SIZE;
				tileInfo[(randNum1)* WINSIZE_TILE_MAP + (randNum2)].object = new Objek((OBJEK)randOb, posx, posy);
				tileInfo[(randNum1)* WINSIZE_TILE_MAP + (randNum2)].object->SetPlayer(player);
				colMar->AddObjek(tileInfo[(randNum1)* WINSIZE_TILE_MAP + (randNum2)].object);
			}
		}

	}
}

void ObjManager::objectInit(int X, int Y)
{
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		randNum1 = rand() % 12;
		randNum2 = rand() % 12;	// 3 + 1;

		RECT tempRc;
		RECT tempRc2 = { (X + randNum2)* TILE_SIZE, (Y + randNum1)* TILE_SIZE,
			(X + randNum2)* TILE_SIZE + TILE_SIZE, (Y + randNum1)* TILE_SIZE + TILE_SIZE };


		if (tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].terrain == WATER || tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].terrain == CLIFF)
		{
			i--;
			continue;
		}
		else if (IntersectRect(&tempRc, &player->GetRc(), &tempRc2))
		{
			i--;
			continue;
		}

		randOb = rand() % 4 + 1;

		if (tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].terrain == LAND)
		{
			if (tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].object != nullptr)
			{
				i--;
			}
			else
			{
				//tileInfo[(randNum1 + Y) * WINSIZE_TILE_MAP + (randNum2 + X)].object = (OBJEK)randOb;
				int posy = (Y + randNum1)* TILE_SIZE;		//WINSIZE_TILE_MAP + (randNum2 + X)) * TILE_SIZE;
				int posx = (X + randNum2)* TILE_SIZE;
				tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].object = new Objek((OBJEK)randOb, posx, posy);
				tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].object->SetPlayer(player);
				colMar->AddObjek(tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].object);
			}
		}

	}
}

void ObjManager::objectInit(int X, int Y, int num)
{
	if (objNum < 50) {
		srand(time(NULL));

		for (int i = 0; i < 1; i++)
		{
			randNum1 = rand() % 12;
			randNum2 = rand() % 12;	// 3 + 1;

			RECT tempRc;
			RECT tempRc2 = { (X + randNum2)* TILE_SIZE, (Y + randNum1)* TILE_SIZE,
				(X + randNum2)* TILE_SIZE + TILE_SIZE, (Y + randNum1)* TILE_SIZE + TILE_SIZE };


			if (tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].terrain == WATER || tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].terrain == CLIFF)
			{
				i--;
				continue;
			}
			else if (IntersectRect(&tempRc, &player->GetRc(), &tempRc2))
			{
				i--;
				continue;
			}

			randOb = rand() % 4 + 1;

			if (tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].terrain == LAND)
			{
				if (tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].object != nullptr)
				{
					i--;
				}
				else
				{
					//tileInfo[(randNum1 + Y) * WINSIZE_TILE_MAP + (randNum2 + X)].object = (OBJEK)randOb;
					int posy = (Y + randNum1)* TILE_SIZE;		//WINSIZE_TILE_MAP + (randNum2 + X)) * TILE_SIZE;
					int posx = (X + randNum2)* TILE_SIZE;
					objNum++;
					tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].object = new Objek((OBJEK)randOb, posx, posy);
					tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].object->SetPlayer(player);
					colMar->AddObjek(tileInfo[(Y + randNum1)* WINSIZE_TILE_MAP + (X + randNum2)].object);
				}
			}

		}
	}
}

void ObjManager::objectListInit(int X, int Y, OBJEK obj)
{
	srand(time(NULL));

	// 3 + 1;
	int numNum = (rand() % 3) + 1;
	OBJEKRESULT obj2;
	int numNum2;
	for (int i = 0; i < numNum; i++)
	{
		int	randX = (rand() % 15);
		int	randY = (rand() % 15);
		if (obj == OBJEK::TREE)
		{
			numNum2 = (rand() % 3);
			if (numNum2 == 0)
			{
				obj2 = OBJEKRESULT::SHIP;
			}
			else
				obj2 = OBJEKRESULT::WOOD;
		}
		else if (obj == OBJEK::GRASS) {
			obj2 = OBJEKRESULT::BERRY;
		}
		else if (obj == OBJEK::STONE) {
			numNum2 = (rand() % 3);
			if (numNum2 == 0)
			{
				obj2 = OBJEKRESULT::COAL2;
			}
			else
				obj2 = OBJEKRESULT::ROCK;
		}
		else if (obj == OBJEK::FLOWER) {

			obj2 = OBJEKRESULT::FIBER;
		}
		int XX;
		int YY;
		if (i == 0)
		{
			XX = X + randX;
			YY = Y + randY;
		}
		else if (i == 1)
		{
			XX = X + randX;
			YY = Y - randY;
		}
		else if (i == 2)
		{
			XX = X + randY;
			YY = Y;
		}
		else
		{
			XX = X;
			YY = Y + randY;
		}
		ReObj[(colMar->GetListSize())] = new ObjRE(obj2, XX, YY);
		colMar->AddList(ReObj[(colMar->GetListSize())]);
	}
}
