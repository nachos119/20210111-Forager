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
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void Update(int num);				// ������ ���� ���� ���� ���� (������ ����)

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

