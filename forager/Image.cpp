#include "Image.h"
#include "Animation.h"


HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;

	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBlendBit =
		(HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;	// AC_SRC_ALPHA;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	return E_NOTIMPL;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBlendBit =
		(HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	ReleaseDC(g_hWnd, hdc);

	this->isTrans = isTrans;
	this->transColor = transColor;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;	// AC_SRC_ALPHA;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBlendBit =
		(HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// �ִϸ��̼� ����
	imageInfo->currFrameX = 0;
	imageInfo->currFrameY = 0;
	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->frameWidth = imageInfo->width / maxFrameX;
	imageInfo->frameHeight = imageInfo->height / maxFrameY;

	ReleaseDC(g_hWnd, hdc);

	this->isTrans = isTrans;
	this->transColor = transColor;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;	// AC_SRC_ALPHA;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hBlendDC, imageInfo->hOldBlendBit);
		DeleteObject(imageInfo->hBlendBitmap);
		DeleteDC(imageInfo->hBlendDC);

		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		delete imageInfo;
		imageInfo = nullptr;
	}

}

void Image::Render(HDC hdc, int destX, int destY)
{
	//imageInfo->x = destX - (imageInfo->width / 2);
	//imageInfo->y = destY - (imageInfo->height / 2);

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX, destY,
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			destX, destY,		// ���� ���� ��ġ
			imageInfo->width,	// �������� ����� ���� ũ��
			imageInfo->height,	// �������� ����� ���� ũ��

			imageInfo->hMemDC,	// ���� DC
			0, 0,				// �������� ���� ���� ��ġ
			SRCCOPY				// ���� �ɼ�
		);
	}

}

void Image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth,
			sourHeight,

			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),		// ���� ���� ��ġ
			sourWidth,			// �������� ����� ���� ũ��
			sourHeight,			// �������� ����� ���� ũ��
			imageInfo->hMemDC,	// ���� DC
			sourX, sourY,		// �������� ���� ���� ��ġ
			SRCCOPY				// ���� �ɼ�
		);
	}
}

void Image::Render(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			currFrameX,
			currFrameY,

			imageInfo->hMemDC,
			0, 0,
			currFrameX, currFrameY,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			destX,
			destY,		// ���� ���� ��ġ
			currFrameX,			// �������� ����� ���� ũ��
			currFrameY,			// �������� ����� ���� ũ��
			imageInfo->hMemDC,	// ���� DC
			0, 0,		// �������� ���� ���� ��ġ
			SRCCOPY				// ���� �ɼ�
		);
	}
}

void Image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int half)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth / half,
			sourHeight / half,

			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),		// ���� ���� ��ġ
			sourWidth / half,			// �������� ����� ���� ũ��
			sourHeight / half,			// �������� ����� ���� ũ��
			imageInfo->hMemDC,	// ���� DC
			sourX, sourY,		// �������� ���� ���� ��ġ
			SRCCOPY				// ���� �ɼ�
		);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
	imageInfo->currFrameX = currFrameX;
	imageInfo->currFrameY = currFrameY;

	imageInfo->x = destX - (imageInfo->frameWidth / 2);
	imageInfo->y = destY - (imageInfo->frameHeight / 2);

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			imageInfo->x, imageInfo->y,
			imageInfo->frameWidth, imageInfo->frameHeight,

			imageInfo->hMemDC,
			imageInfo->currFrameX* imageInfo->frameWidth,
			imageInfo->currFrameY* imageInfo->frameHeight,
			imageInfo->frameWidth, imageInfo->frameHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			imageInfo->x, imageInfo->y,		// ���� ���� ��ġ
			imageInfo->frameWidth,	// �������� ����� ���� ũ��
			imageInfo->frameHeight,	// �������� ����� ���� ũ��

			imageInfo->hMemDC,	// ���� DC
			imageInfo->currFrameX * imageInfo->frameWidth,
			imageInfo->currFrameY * imageInfo->frameHeight,
			SRCCOPY				// ���� �ɼ�
		);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, int half)
{
	imageInfo->currFrameX = currFrameX;
	imageInfo->currFrameY = currFrameY;

	imageInfo->x = destX - (imageInfo->frameWidth / 2) / half;
	imageInfo->y = destY - (imageInfo->frameHeight / 2) / half;

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			imageInfo->x, imageInfo->y,
			imageInfo->frameWidth / half, imageInfo->frameHeight / half,

			imageInfo->hMemDC,
			imageInfo->currFrameX* imageInfo->frameWidth,
			imageInfo->currFrameY* imageInfo->frameHeight,
			imageInfo->frameWidth, imageInfo->frameHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			imageInfo->x, imageInfo->y,		// ���� ���� ��ġ
			imageInfo->frameWidth / half,	// �������� ����� ���� ũ��
			imageInfo->frameHeight / half,	// �������� ����� ���� ũ��

			imageInfo->hMemDC,	// ���� DC
			imageInfo->currFrameX * imageInfo->frameWidth,
			imageInfo->currFrameY * imageInfo->frameHeight,
			SRCCOPY				// ���� �ɼ�
		);
	}
}

void Image::FrameRenderMask(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, RECT mask)
{
	imageInfo->currFrameX = currFrameX;
	imageInfo->currFrameY = currFrameY;

	imageInfo->x = destX - (imageInfo->frameWidth / 2);
	imageInfo->y = destY - (imageInfo->frameHeight / 2);

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			imageInfo->x + mask.left, imageInfo->y + mask.top,
			mask.right - mask.left, mask.bottom - mask.top,

			imageInfo->hMemDC,
			imageInfo->currFrameX * imageInfo->frameWidth + mask.left,
			imageInfo->currFrameY * imageInfo->frameHeight + mask.top,
			mask.right - mask.left, mask.bottom - mask.top,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			imageInfo->x + mask.left, imageInfo->y + mask.top,		// ���� ���� ��ġ
			mask.right - mask.left, mask.top - mask.bottom,			// ���� ũ��

			imageInfo->hMemDC,	// ���� DC
			imageInfo->currFrameX* imageInfo->frameWidth + mask.left,
			imageInfo->currFrameY* imageInfo->frameHeight + mask.top,
			SRCCOPY				// ���� �ɼ�
		);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;
	if (isTrans)
	{
		// ���� �۾� : blendDC, blendBitmap�� �غ�

		// 1. ������ DC�� �׷��� �ִ� ������ blendDC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		// 2. ����� �̹���DC�� blendDC�� ������ ������ �����ϸ鼭 ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			transColor);

		// 3. blendDC�� ������ ������ DC�� ���� ���� �Լ��� ���� 
		AlphaBlend(hdc, destX, destY, imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;
	if (isTrans)
	{
		// ���� �۾� : blendDC, blendBitmap�� �غ�

		// 1. ������ DC�� �׷��� �ִ� ������ blendDC�� ����
		BitBlt(imageInfo->hBlendDC,
			0, 0,
			sourWidth,
			sourHeight,
			hdc, 
			destX - (sourWidth / 2),
			destY - (sourHeight / 2), 
			SRCCOPY);

		// 2. ����� �̹���DC�� blendDC�� ������ ������ �����ϸ鼭 ����
		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			sourWidth,
			sourHeight,
			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			transColor);

		// 3. blendDC�� ������ ������ DC�� ���� ���� �Լ��� ���� 
		AlphaBlend(hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth,
			sourHeight,
			imageInfo->hBlendDC,
			0, 0,
			sourWidth,
			sourHeight,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth,
			sourHeight,
			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int half, BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;
	if (isTrans)
	{
		// ���� �۾� : blendDC, blendBitmap�� �غ�

		// 1. ������ DC�� �׷��� �ִ� ������ blendDC�� ����
		BitBlt(imageInfo->hBlendDC,
			0, 0,
			sourWidth / half,
			sourHeight / half,
			hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			SRCCOPY);

		// 2. ����� �̹���DC�� blendDC�� ������ ������ �����ϸ鼭 ����
		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			sourWidth / half,
			sourHeight / half,
			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			transColor);

		// 3. blendDC�� ������ ������ DC�� ���� ���� �Լ��� ���� 
		AlphaBlend(hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth / half,
			sourHeight / half,
			imageInfo->hBlendDC,
			0, 0,
			sourWidth / half,
			sourHeight / half,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth / half,
			sourHeight / half,
			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth ,
			sourHeight,
			blendFunc);
	}
}

void Image::AnimationRender(HDC hdc, int destX, int destY, Animation* ani)
{
	Render(hdc, destX, destY, ani->GetFramePoint().x, ani->GetFramePoint().y,
		imageInfo->frameWidth, imageInfo->frameHeight);
}

void Image::AnimationAlphaRender(HDC hdc, int destX, int destY, Animation* ani, BYTE alpha)
{
	AlphaRender(hdc, destX, destY, ani->GetFramePoint().x, ani->GetFramePoint().y,
		imageInfo->frameWidth, imageInfo->frameHeight, alpha);
}

void Image::AnimationRender(HDC hdc, int destX, int destY, int half, Animation* ani)
{
	Render(hdc, destX, destY, ani->GetFramePoint().x, ani->GetFramePoint().y,
		imageInfo->frameWidth, imageInfo->frameHeight, half);
}

void Image::AnimationAlphaRender(HDC hdc, int destX, int destY, int half, Animation* ani, BYTE alpha)
{
	AlphaRender(hdc, destX, destY, ani->GetFramePoint().x, ani->GetFramePoint().y,
		imageInfo->frameWidth, imageInfo->frameHeight, half, alpha);
}

Image::Image()
{
}


Image::~Image()
{
}
