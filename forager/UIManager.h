#pragma once
#include "GameNode.h"

class Animation;
class Player;
class UIManager : public GameNode
{
private:

	Image* life1;
	Image* life2;
	Image* life3;
	Image* life4;
	Animation* lifeAni;

	Image* EX;
	Image* EXBar;
	Image* Sta;
	Image* StaBar;
	POINT EXBarMax;
	POINT StaBarMax;

	Image* LEVEL;
	Image* Par;
	Image* number;
	Image* slush;
	FPOINT ParPos;

	Player* player;

public:
	virtual HRESULT Init() override;			// 멤버 변수 초기화, 메모리 할당
	virtual void Release() override;			// 메모리 해제
	virtual void Update() override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc) override;		// 프레임 단위 출력 (이미지, 텍스트 등)
	HRESULT Init(Player* player);			// 멤버 변수 초기화, 메모리 할당
	void Render(HDC hdc, bool menu);		// 프레임 단위 출력 (이미지, 텍스트 등)

	void PlayerUI();

	UIManager() {};
	virtual ~UIManager() {};
};

