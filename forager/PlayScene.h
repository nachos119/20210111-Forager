#pragma once
#include "GameNode.h"

class Camera;
class Player;
class Menu;
class CollisionManager;
class UIManager;
class TileMap;
class ObjManager;
class Image;
class Animation;
class ObjRE;
class PlayScene : public GameNode
{
private:
	Camera* setCamera;

	CollisionManager* colMar;

	Player* player;

	ObjRE* objre;

	UIManager* UImanager;
	TileMap* Tilemap;
	ObjManager* Objmanager;

	Image* number2;
	Image* goldUI;
	Image* buyUI;
	Image* flagUI;
	Image* selUI;
	Animation* flagUIAni;
	Animation* selUIAni;

	float objTimer;

	HBRUSH BackBrush;
	HBRUSH NULLBrush;
	HBRUSH oldBrush;

	OBJECT_INFO objectInfo[END3];

	Menu* menuScene;
	bool menuOn;

public:
	virtual HRESULT Init() override;			// 멤버 변수 초기화, 메모리 할당
	virtual void Release() override;			// 메모리 해제
	virtual void Update() override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc) override;		// 프레임 단위 출력 (이미지, 텍스트 등)


	PlayScene() {};
	virtual ~PlayScene() {};
};

