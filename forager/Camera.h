#pragma once
#include "GameNode.h"

class Menu;
class TileMap;
class Player;
class Camera : public GameNode
{
private:
	int centerX;
	int centerY;

	bool startCenter;

	POINT pos;

	Player* target;

	int SetX;
	int SetY;

	int gold;

	int buyCenterX;
	int buyCenterY;

	POINT XY[25];

	Menu* menu;

	TileMap* tile;


public:
	virtual HRESULT Init() override;			// 멤버 변수 초기화, 메모리 할당
	virtual void Release() override;			// 메모리 해제
	virtual void Update() override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc) override;		// 프레임 단위 출력 (이미지, 텍스트 등)
	void Update(int num);				// 프레임 단위 게임 로직 실행 (데이터 변경)

	int GetCenterX() { return this->centerX; }
	int GetCenterY() { return this->centerY; }
	void SetCenterX(int centerX) { this->centerX += centerX; }
	void SetCenterY(int centerY) { this->centerY += centerY; }

	int GetGold() { return this->gold; }
	void SetTarget(Player* target) { this->target = target; }
	void SetMenu(Menu* menu) { this->menu = menu; }
	void SetCamera(float X, float Y);
	void SetCamera2(int XX, int YY);
	void SetTile(TileMap* tile) { this->tile = tile; }

	Camera() {};
	virtual ~Camera() {};
};

