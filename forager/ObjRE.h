#pragma once
#include "GameNode.h"
#include "Camera.h"

class Image;
class Animation;
class Player;
class CollisionManager;
class ObjRE : public GameNode
{
private:
	Image* img;

	OBJEKRESULT objRe;

	POINT pos;


	CollisionManager* colMar;

	bool check;

public:
	HRESULT Init(CollisionManager* colMar);				// 멤버 변수 초기화, 메모리 할당
	//HRESULT Init(OBJEK obj);				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc, float X, float Y);//, int obj);				// 프레임 단위 출력 (이미지, 텍스트 등)

	void SetCheck(bool check) { this->check = check; }
	bool GetCheck() { return this->check; }

	OBJEKRESULT GetObjRe() { return this->objRe; }

	ObjRE(OBJEKRESULT obj, int posx, int posy);
	~ObjRE() {}
};


