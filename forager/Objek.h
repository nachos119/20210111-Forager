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
	//오브젝트 정보
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
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	//HRESULT Init(OBJEK obj);				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc, float X, float Y);//, int obj);				// 프레임 단위 출력 (이미지, 텍스트 등)
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

