#pragma once
#include "GameNode.h"

class Image;
class Animation;
class CollisionManager;
class Menu;
class Player : public GameNode
{
private:
	float speed;

	Image* PStand;
	Image* PRun;
	Animation* StandAni;
	Animation* RunAni;
	Image* PRoll;
	Animation* RollAni;
	Image* PAttack;
	Animation* AttackAni;
	Image* PARoll;
	Animation* ARollAni;

	STATE PState;
	STATE tempState;

	//FRECT frc;
	
	bool roll;
	float rollTimer;

	bool Mouse;

	TILE_INFO* tileInfo;

	// ĳ���� ����
	int PlayerLv;
	int PlayerEx;
	int PlayerMaxEx;
	int PlayerSt;
	int PlayerMaxSt;
	int PlayerTotalLife;
	int PlayerLife;

	int gold;

	int Stamina;
	int checkLife;
	float scaledSpeed;

	CollisionManager* Collision;

	RECT tempRc;

	Menu* menuIn;

	map< OBJEKRESULT, int> inven;
	map< OBJEKRESULT, int>::iterator itrinven;


public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc, float X, float Y);				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void Render(HDC hdc, int X, int Y, int MoveX, int MoveY, int half);				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void Update(bool menu);				// ������ ���� ���� ���� ���� (������ ����)

	void Run();
	void Stand();

	map< OBJEKRESULT, int> GetInven() { return inven; }

	void SetBerry(int num);
	void SetCitrus(int num);
	void SetAni(bool set);

	void SetPosX(int X) { this->pos.x = X; }
	void SetPosY(int Y) { this->pos.y = Y; }

	void invenIt(OBJEKRESULT objj);
	
	void SetTileInfo(TILE_INFO* tile) { this->tileInfo = tile; }

	int GetPLv() { return this->PlayerLv; }
	int GetPEx() { return this->PlayerEx; }
	int GetMaxEx() { return this->PlayerMaxEx; }
	int GetPSt() { return this->PlayerSt; }
	int GetMaxSt() { return this->PlayerMaxSt; }
	int GetPLife() { return this->PlayerLife; }
	int GetTotalLife() { return this->PlayerTotalLife; }

	int GetGold() { return this->gold; }
	void SetGold(int num) { this->gold -= num; }
	void SetEx(int num) { this->PlayerEx += num; }
	void SetStamina(int num) { this->Stamina -= num; }
	void SetCollision(CollisionManager* col) { this->Collision = col; }
	void LEVELUP();

	void SetMenu(Menu* menuIn) { this->menuIn = menuIn; }

	Player() {};
	~Player() {};
};

