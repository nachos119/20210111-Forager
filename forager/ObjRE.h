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
	HRESULT Init(CollisionManager* colMar);				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	//HRESULT Init(OBJEK obj);				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc, float X, float Y);//, int obj);				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void SetCheck(bool check) { this->check = check; }
	bool GetCheck() { return this->check; }

	OBJEKRESULT GetObjRe() { return this->objRe; }

	ObjRE(OBJEKRESULT obj, int posx, int posy);
	~ObjRE() {}
};


