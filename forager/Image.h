#pragma once
#include "pch.h"

class Animation;
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,
		FILE,
		EMPTY,
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// ���ҽ��� ������ ���̵�
		HDC		hMemDC;		// �׸��⸦ �ְ��ϴ� �ڵ� (�޸� ����)
		HBITMAP	hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int		width;		// �̹��� ���� ũ��
		int		height;		// �̹��� ���� ũ��
		BYTE	loadType;	// �ε� Ÿ��

		// Blend
		HDC		hBlendDC;
		HBITMAP hBlendBitmap;
		HBITMAP hOldBlendBit;

		// Animation�� �ʿ��� ����
		int maxFrameX;		// �ִ� ������ �ε���
		int maxFrameY;
		int currFrameX;		// ���� ������ �ε���
		int currFrameY;
		int frameWidth;		// ������ �� ũ��
		int frameHeight;

		// Animation ���� �� ��ġ
		float x, y;

		tagImageInfo() {
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			hBlendDC = NULL;
			hBlendBitmap = NULL;
			hOldBlendBit = NULL;

			maxFrameX = 0;
			maxFrameY = 0;
			currFrameX = 0;
			currFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;

			x = y = 0.0f;
		};

	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO*	imageInfo;		// �̹��� ���� ����ü ������
	//LPIMAGE_INFO imageInfo;

	char* fileName;				// ���� ��� + �̸�
	bool isTrans;				// ����ȭ ����
	COLORREF transColor;		// ����ȭ�� ��

	BLENDFUNCTION	blendFunc;

public:	
	//�� ��Ʈ�� �̹����� �����.
	HRESULT Init(int width, int height);

	// ���ҽ��κ��� �����͸� �о ��Ʈ���� �����.
	HRESULT Init(const DWORD resID, int width, int height,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о ��Ʈ���� �����.
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о ��Ʈ���� �����. (�ִϸ��̼�)
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	// �޸� ����
	void Release();

	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void Render(HDC hdc, int destX, int destY, int currFrameX, int currFrameY);
	void FrameRender(HDC hdc, int destX, int destY,	int currFrameX, int currFrameY);
	void FrameRenderMask(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, RECT mask);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void AnimationRender(HDC hdc, int destX, int destY, Animation* ani);
	void AnimationAlphaRender(HDC hdc, int destX, int destY, Animation* ani, BYTE alpha);

	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, int half);
	void AnimationAlphaRender(HDC hdc, int destX, int destY, int half, Animation* ani, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int half, BYTE alpha);
	void AnimationRender(HDC hdc, int destX, int destY, int half, Animation* ani);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int half);


	HDC GetMemDC()			{ return imageInfo->hMemDC; }
	int GetMaxFrameX()		{ return imageInfo->maxFrameX; }
	int GetWidth()			{ return imageInfo->width; }
	int GetHeight()			{ return imageInfo->height; }
	int GetFrameWidth()		{ return imageInfo->frameWidth; }
	int GetFrameHeight()	{ return imageInfo->frameHeight; }
	int GetCurrentFrameX()	{ return imageInfo->currFrameX; }

	Image();
	~Image();
};

