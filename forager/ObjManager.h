#pragma once
#include "GameNode.h"

class Map;
class Camera;
class Player;
class Animation;
class Objek;
class CollisionManager;
class ObjRE;
class ObjManager : public GameNode
{
private:
	TILE_INFO* tileInfo;

	Camera* setCamera;

	CollisionManager* colMar;

	Player* player;

	HBRUSH BackBrush;
	HBRUSH NULLBrush;
	HBRUSH oldBrush;

	ObjRE* ReObj[100];

	int randNum1, randNum2;
	int randOb;
	int objNum;
	
public:
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	HRESULT Init(TILE_INFO* tileInfo, Camera* setCamera, CollisionManager* colMar, Player* player);			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Render(HDC hdc, int X, int Y);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void Render(HDC hdc, int X, int Y, int MoveX, int MoveY, int half);

	void subRender(HDC hdc);

	void objectInit();
	void objectInit(int X, int Y);
	void objectInit(int X, int Y, int num);
	void objectListInit(int X, int Y, OBJEK obj);

	ObjManager() {};
	virtual ~ObjManager() {};
};
