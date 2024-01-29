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
	virtual HRESULT Init() override;			// 멤버 변수 초기화, 메모리 할당
	virtual void Release() override;			// 메모리 해제
	virtual void Update() override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc) override;		// 프레임 단위 출력 (이미지, 텍스트 등)

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

