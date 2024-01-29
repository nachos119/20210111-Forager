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
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	HRESULT Init(Player* player);			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Render(HDC hdc, bool menu);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void PlayerUI();

	UIManager() {};
	virtual ~UIManager() {};
};

