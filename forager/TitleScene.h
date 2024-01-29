#pragma once
#include "GameNode.h"

class Image;
class Button;
class TitleScene : public GameNode
{
private:
	Image* img;
	Image* imgLogo;
	
	POINT BackG1;
	POINT BackG2;

	Button* PlayerButton;
	Button* OptoinsButton;
	Button* MapToolButton;
	Button* EixtButton;

	float time;
public:
	virtual HRESULT Init() override;			// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() override;			// �޸� ����
	virtual void Update() override;				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	TitleScene() {};
	virtual ~TitleScene() {};

};

