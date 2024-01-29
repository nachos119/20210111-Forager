// main.cpp

/*
	Win32 API
	: Application Programming Interface
	�ü���� �������α׷� ������ ���� �����ϴ� �Լ��� ����

	�ϵ���� ----------�ü��(Windows)---------- �������α׷�
						 ( API �Լ� )
*/
#include <Windows.h>
#include "MainGame.h"

// ��������
HINSTANCE	g_hInstance;		// ���α׷� �ν��Ͻ� �ڵ�
HWND		g_hWnd;				// ������ �ڵ�
LPSTR		g_lpszClass = (LPSTR)TEXT("Forager");
MainGame	g_mainGame;
POINT		g_ptMouse;
float		g_time;

// Ŭ���� ��ǥ�� �׸� �ȿ� �ִ��� Ȯ���ϴ� �Լ�
//bool IsInRect(RECT rc, MOUSE_DATA mouseData)
//{
//	if (rc.left <= mouseData.clickedPosX && mouseData.clickedPosX <= rc.right
//		&& rc.top <= mouseData.clickedPosY && mouseData.clickedPosY <= rc.bottom)
//	{
//		return true;
//	}
//
//	return false;
//}

// ��Ʈ�� ��Ʈ�� �浹�� Ȯ���ϴ� �Լ�
bool CheckRectCollision(RECT rc1, RECT rc2)
{
	if (rc1.right < rc2.left ||
		rc1.left > rc2.right ||
		rc1.top > rc2.bottom ||
		rc1.bottom < rc2.top)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

// �����Լ�
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	// �����츦 �����ϱ� ���� �⺻����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// Ŭ������ ���� �޸�
	wndClass.cbWndExtra = 0;	// �������� ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(g_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		50, 50, WINSIZE_X, WINSIZE_Y,
		NULL, NULL, g_hInstance, NULL);

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	// ���� �۾� ������� ����
	SetWindowSize(0, 0, WINSIZE_X, WINSIZE_Y);

	g_mainGame.Init();

	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)	break;

			TranslateMessage(&message);
			DispatchMessage(&message);	
		}
		else
		{
			TimerManager::GetSingleton()->Update();

			g_mainGame.Update();
			g_mainGame.Render();
		}
	}

	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	g_mainGame.Release();

	// Ÿ�̸� ����
	//KillTimer(g_hWnd, 0);

	return message.wParam;
}

// �ݹ��Լ� : ������ �޽���(�̺�Ʈ)�� ó���ϴ� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, 
	WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage,
		wParam, lParam);
}