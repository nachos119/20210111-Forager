#include "ButtonFunction.h"
#include "TileMapToolScene.h"
#include "Tile.h"

void ButtonFunction::AddValue(void* arg)
{
	Argument2* val = (Argument2*)arg;
	TileInfoLoad(arg);
}

void ButtonFunction::ChangeScene(void* arg)
{
	Argument1* argu = (Argument1*)arg;

	SceneManager::GetSingleton()->ChangeScene(argu->sceneName.c_str(), argu->loadingSceneName.c_str());
}

void ButtonFunction::QuitProgram(void* arg)
{
	//int* point = (int*)arg;
	//if (MessageBox(g_hWnd, string("������ �����Ͻðڽ��ϱ�?" + to_string(*point)).c_str(), "���� Ȯ��", MB_OKCANCEL) == IDOK)
	if (MessageBox(g_hWnd, "������ �����Ͻðڽ��ϱ�?", "���� Ȯ��", MB_OKCANCEL) == IDOK)
	{
		PostQuitMessage(0);
	}
}

void ButtonFunction::TileInfoSave(void* arg)
{
	Argument2* args = (Argument2*)arg;

	char sz_Text[300];
	OPENFILENAME OFN;
	char lpstrFile[MAX_PATH] = "";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Map File\0*.map;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "Save";
	if (GetSaveFileName(&OFN) != 0) {
		wsprintf(sz_Text, "%s ������ �����߽��ϴ�.", OFN.lpstrFile);
		MessageBox(g_hWnd, sz_Text, "���� ���� ����", MB_OK);
		string str = (string)OFN.lpstrFile + ".map";

		DWORD writtenByte;
		HANDLE hFile = CreateFile(str.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		//WriteFile(hFile, sizeof(int) * 2, &writtenByte, NULL);

		WriteFile(hFile, args->tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenByte, NULL);
		CloseHandle(hFile);
	}
	//string fileName = "Save/saveMapData" + to_string(*(args->currentStage)) + ".map";

	//DWORD writtenByte;
	//HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//WriteFile(hFile, args->tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenByte, NULL);

	//CloseHandle(hFile);
}

void ButtonFunction::TileInfoLoad(void* arg)
{
	Argument2* args = (Argument2*)arg;

	char sz_Text[300];
	OPENFILENAME OFN;
	char lpstrFile[MAX_PATH] = "";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "Save/saveMapData";

	if (GetOpenFileName(&OFN) != 0) {
		wsprintf(sz_Text, "%s ������ �������ϴ�.", OFN.lpstrFile);
		MessageBox(g_hWnd, sz_Text, "���� ���� ����", MB_OK);
		string str = (string)OFN.lpstrFile;
		DWORD readByte;
		HANDLE hFile = CreateFile(str.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//int size[2];
		//ReadFile(hFile, size, sizeof(int) * 2, &readByte, NULL);

		//wsprintf(sz_Text, "%d, %d", size[0], size[1]);
	//	MessageBox(g_hWnd, sz_Text, "�ε������", MB_OK);
		//TILE_INFO* tile = GameManger::GetSingleton()->GetTileMapToolScene()->GetTileInfo();

		//delete[] tile;
		//GameManger::GetSingleton()->GetTileMapToolScene()->SetTileInfo(0);
		//GameManger::GetSingleton()->GetTileMapToolScene()->SetTileSize(size[0], size[1]);
		//GameManger::GetSingleton()->GetTileMapToolScene()->SetTileInfo(new TILE_INFO[size[0] * size[1]]);
		//GameManger::GetSingleton()->GetTileMapToolScene()->TileInit();
		//tile = GameManger::GetSingleton()->GetTileMapToolScene()->GetTileInfo();
		ReadFile(hFile, args->tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);

		CloseHandle(hFile);
	}
	/*string fileName = "Save/saveMapData" + to_string(*(args->currentStage)) + ".map";

	DWORD readByte;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, args->tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);

	CloseHandle(hFile);*/
}
