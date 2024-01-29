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
	virtual HRESULT Init() override;			// 멤버 변수 초기화, 메모리 할당
	virtual void Release() override;			// 메모리 해제
	virtual void Update() override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc) override;		// 프레임 단위 출력 (이미지, 텍스트 등)
	HRESULT Init(TILE_INFO* tileInfo, Camera* setCamera, CollisionManager* colMar, Player* player);			// 멤버 변수 초기화, 메모리 할당
	void Render(HDC hdc, int X, int Y);		// 프레임 단위 출력 (이미지, 텍스트 등)
	void Render(HDC hdc, int X, int Y, int MoveX, int MoveY, int half);

	void subRender(HDC hdc);

	void objectInit();
	void objectInit(int X, int Y);
	void objectInit(int X, int Y, int num);
	void objectListInit(int X, int Y, OBJEK obj);

	ObjManager() {};
	virtual ~ObjManager() {};
};
