#pragma once
#include "GameNode.h"
#include "Camera.h"

class Image;
class Animation;
class Player;
class Objek : public GameNode
{
private:
	Image* img;
	Image* objhp;
	Image* objhpbar;
	//������Ʈ ����
	int hp;
	int hpM;
	int Ex;
	int sizeX;
	int sizeY;
	OBJEK objekk;

	POINT pos;
	POINT poss;
	float attackGauge;

	Player* player;

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	//HRESULT Init(OBJEK obj);				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc, float X, float Y);//, int obj);				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void Render(HDC hdc, RECT rc1, float X, float Y, int half);
	void HPRender(HDC hdc, float X, float Y);

	void SetPlayer(Player* player) { this->player = player; }

	OBJEK GetObjek() { return this->objekk; }

	int GetHp() { return this->hp; }
	POINT GetPoss() { return this->poss; }
	void SetHp(int num) { this->hp -= num; }

	Objek(OBJEK obj, int posx, int posy);
	~Objek() {}
};

