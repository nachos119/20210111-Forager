#pragma once
#include "GameNode.h"

class Image;
class Animation;
class Button;
class Player;
class Menu : public GameNode
{
private:
	Image* menuUp;
	Image* muneBack;
	Image* menuCan;
	Image* menuKey;
	Animation* menuKeyAni;
	Image* bulid;
	Image* menuBuy;
	Image* menuBuild;
	Image* menuEq;
	Image* menuItem;
	Image* menuSet;
	Image* menuExit;
	Image* exitSel;
	Image* landBuy;

	Image* wood;
	Image* citrus;
	Image* berry2;
	Image* rock2;
	Image* coal;
	Image* fiber;
	Image* number;

	RECT rc[5];

	Button* EixtButton;

	RECT rc5;

	RECT rc4[25];
	int x = 0, moveX = 0, y = 0, moveY = 0;
	bool mapIt[25];
	bool mapIt2[25];

	RECT rc2[16];
	bool rc2map[16];
	OBJEKRESULT rc2obj[16];
	int objNum[16];

	int menuNum;

	bool exitGo;

	TILE_INFO* tile;

	Player* player;

	bool doubleCehck;
	float doubleTimer;

public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);				// 프레임 단위 출력 (이미지, 텍스트 등)
	void Render(HDC hdc, int X, int Y, int MoveX, int MoveY);				// 프레임 단위 출력 (이미지, 텍스트 등)

	int GetMenu() { return this->menuNum; }
	bool GetExit() { return this->exitGo; }
	void SetMenu(int num) { this->menuNum = num; }

	RECT GetRc4(int index) { return { rc4[index].left - (x * TILE_SIZE / 2) - moveX, rc4[index].top - (y * TILE_SIZE / 2) - moveY, rc4[index].right - (x * TILE_SIZE / 2) - moveX, rc4[index].bottom - (y * TILE_SIZE / 2) - moveY }; }

	void SetMap(TILE_INFO* tile) { this->tile = tile; }
	void SetMapIt(int index) { mapIt[index] = true; }
	void SetPlayer(Player* player) { this->player = player; }
	bool GetMapIt(int index) { return this->mapIt[index]; }
	bool GetMapIt2(int index) { return this->mapIt2[index]; }

	void numberRender(HDC hdc, int k);

	Menu() {};
	~Menu() {};
};

