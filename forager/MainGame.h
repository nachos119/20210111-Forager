#pragma once

/*
	전방선언, 전처리문 #include

	1. is a 관계 : 소나타는 차다.					-> #include
	2. has a 관계 : 소나타는 바퀴를 가지고 있다.	-> 전방선언
*/
#include "GameNode.h"

class Image;
class MainGame : public GameNode
{
private:
	HDC hdc;
	bool isInit;

	Image* backBuffer;
	Image* backGround;

public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render();				// 프레임 단위 출력 (이미지, 텍스트 등)

	void ImageInit();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

