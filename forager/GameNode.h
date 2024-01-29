#pragma once
#include "pch.h"

/*
	������ ������� ������ ���� �⺻���� ������ �Ǵ� Ŭ����
*/
class GameNode
{
private:
public:
	FPOINT pos;
	RECT rc;
	FRECT frc;
	virtual HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();				// �޸� ����
	virtual void Update();				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	FPOINT GetPos() { return this->pos; }
	RECT GetRc() { return this->rc; }
	FRECT GetFRc() { return this->frc; }

	GameNode();
	virtual ~GameNode();
};

