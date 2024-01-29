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
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


	PlayScene() {};
	virtual ~PlayScene() {};
};

