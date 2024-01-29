#pragma once

#include <Windows.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <cstdlib>
#include <ctime>

#include "resource.h"

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

#define TILE_SIZE	56		// 타일 하나의 사이즈
#define TILE_X		12
#define TILE_Y		12
#define TILE(x)		((x - 1) * TILE_SIZE + TILE_SIZE/2)
#define TILE2(x, y)	{ TILE(x), TILE(y) }

#define WINSIZE_X	((TILE_X + 2) * TILE_SIZE)
#define WINSIZE_Y	((TILE_Y) * TILE_SIZE)
#define WINSIZE_TITLE_X		1600
#define WINSIZE_TITLE_Y		900
#define WINSIZE_TILE_MAP	62

#define WINSIZE_MAP_X	1280
#define WINSIZE_MAP_Y	750

#define PLAYER_CENTER_X 644
#define PLAYER_CENTER_Y 392
#define MAP_CENTER 1736

#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)

#define SAFE_DELETE(p)		{ if (p) { delete p; p = nullptr; } }
#define SAFE_ARR_DELETE(p)	{ if (p) { delete[] p; p = nullptr; } }
#define SAFE_RELEASE(p)		{ if (p) { p->Release(); delete p; p = nullptr; } }
#define MAGENTA		RGB(255, 0, 255)
// 타일 정보
#define SAMPLE_TILE_X	2		// 샘플 타일의 X 갯수
#define SAMPLE_TILE_Y	2		// 샘플 타일의 Y 갯수
#define MAX_STAGE_SIZE	10
#define IMAGE_ZOOM		4

#pragma region define키입력
#define KEY_SPACE		0x20
#define KEY_ENTER		0x0D
#define KEY_UP			0x26
#define KEY_DOWN		0x28
#define KEY_LEFT		0x25
#define KEY_RIGHT		0x27
#define KEY_A			0x41 
#define KEY_B			0x42
#define KEY_C			0x43
#define KEY_D			0x44
#define KEY_E			0x45
#define KEY_F			0x46
#define KEY_G			0x47
#define KEY_H			0x48
#define KEY_I			0x49
#define KEY_J			0x4A
#define KEY_K			0x4B
#define KEY_L			0x4C
#define KEY_M			0x4D
#define KEY_N			0x4E
#define KEY_O			0x4F
#define KEY_P			0x50
#define KEY_Q			0x51
#define KEY_R			0x52
#define KEY_S			0x53
#define KEY_T			0x54
#define KEY_U			0x55
#define KEY_V			0x56
#define KEY_W			0x57
#define KEY_X			0x58
#define KEY_Y			0x59
#define KEY_Z			0x5A
#define KEY_NUM1		0x31
#define KEY_NUM2		0x32
#define KEY_NUM3		0x33
#define KEY_NUM4		0x34
#define KEY_NUM5		0x35

enum TERRAIN 
{	
	LAND,	// 땅
	WATER,	// 물
	CLIFF,	// 절벽
	END 
};

enum STATE
{
	STAND,
	RUN,
	ROLL,
	ATTACK,
	END2
};

enum OBJEK
{
	XXX,	
	TREE,
	GRASS,
	STONE,
	FLOWER,	
	GOLD,
	COAL,
	IRON,
	END3
};

enum OBJEKRESULT
{
	WOOD,
	SHIP,
	BERRY,
	ROCK,
	GOLD2,
	COAL2,
	IRON2,
	FIBER,
	END4
};

struct OBJECT_INFO
{
	OBJEK type;
	float collisionSize;
	
};

struct FPOINT
{
    double x;
    double y;
};

enum class Argument_Kind {
	None,
	Argument1,
	Argument2,
};

struct Argument1
{
	string sceneName;
	string loadingSceneName;
};

typedef struct tagTile TILE_INFO;
struct Argument2
{
	TILE_INFO* tileInfo;
	int value;

	Argument2(TILE_INFO* tileInfo, int value) 
	{
		this->tileInfo = tileInfo;
		this->value = value;
	}
};

struct FRECT
{
	double    left;
	double    top;
	double    right;
	double    bottom;
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;

	// 실제 윈도우 크기 받아오기
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}

template <typename T>
inline T Clamp(T value, T min, T max)
{
	if (value > max) return max;
	else if (value < min) return min;
	return value;
}

// rect의 위치를 출력하는 함수	// 임시용
inline void PrintRect(HDC hdc, RECT rect)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, rect.left, rect.top, NULL);
	LineTo(hdc, rect.left, rect.bottom);
	LineTo(hdc, rect.right, rect.bottom);
	LineTo(hdc, rect.right, rect.top);
	LineTo(hdc, rect.left, rect.top);

	DeleteObject(SelectObject(hdc, hOldPen));
}