#pragma once
#include "GameNode.h"

class Objek;
class Player;
class ObjRE;
class ObjManager;
class CollisionManager : public GameNode
{
private:
	//GameNode* target;
	//GameNode* obj;

	vector<Objek*>				vecObject;
	vector<Objek*>::iterator	itObject;

	list< ObjRE*>				liObjek;
	list< ObjRE*>::iterator		itObjek;

	Player* player;

	ObjManager* objM;

public: 
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	bool CheckCollision(RECT rc);
	void CheckColObj(int X, int Y);
	void AddObjek(Objek* addObj);

	int GetListSize() { return this->liObjek.size(); }
	void AddList(ObjRE* addObj);

	void SetObjM(ObjManager* objM) { this->objM = objM; }

	void SetPlayer(Player* player) { this->player = player; }

	CollisionManager() {};
	~CollisionManager() {};
};

