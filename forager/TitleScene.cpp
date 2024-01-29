#include "TitleScene.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"

HRESULT TitleScene::Init()
{
	SetWindowSize(0, 0, WINSIZE_MAP_X, WINSIZE_MAP_Y);

	img = ImageManager::GetSingleton()->FindImage("TitleScene");
	imgLogo = ImageManager::GetSingleton()->FindImage("Logo");

	BackG1 = { 0,0 };
	BackG2 = { -WINSIZE_MAP_X, 0 };


	PlayerButton = new Button();
	PlayerButton->Init("ButPlayStart", 230, 230, { 0,0 }, { 0,0 });

	//OptoinsButton = new Button();
	//OptoinsButton->Init("ButOptions", 240, 452, { 0,0 }, { 0,0 });

	MapToolButton = new Button();
	MapToolButton->Init("ButMapTool", 230, 388, { 0,0 }, { 0,0 });

	EixtButton = new Button();
	EixtButton->Init("ButExit", 230, 532, { 0,0 }, { 0,0 });

	Argument1* arg1 = new Argument1();
	arg1->sceneName = "플레이";
	arg1->loadingSceneName = "";
	PlayerButton->SetButtonFunc(&ButtonFunction::ChangeScene, Argument_Kind::Argument1, arg1);
	/*
		Argument1* arg2 = new Argument1();
		arg2->sceneName = "2인전투";
		arg2->loadingSceneName = "";
		twoPlayersButton->SetButtonFunc(&ButtonFunction::ChangeScene, Argument_Kind::Argument1, arg2);
	*/
	Argument1* arg3 = new Argument1();
	arg3->sceneName = "맵툴";
	arg3->loadingSceneName = "";
	MapToolButton->SetButtonFunc(&ButtonFunction::ChangeScene, Argument_Kind::Argument1, arg3);

	Argument1* argEixt = new Argument1();
	argEixt->sceneName = "종료";
	argEixt->loadingSceneName = "";
	EixtButton->SetButtonFunc(&ButtonFunction::QuitProgram, Argument_Kind::Argument1, argEixt);

	time = 0;

	return S_OK;
}

void TitleScene::Release()
{
	SAFE_RELEASE(EixtButton);
	SAFE_RELEASE(MapToolButton);
//	SAFE_RELEASE(OptoinsButton);
	SAFE_RELEASE(PlayerButton);
}

void TitleScene::Update()
{
	time += TimerManager::GetSingleton()->GetElapsedTime();
	if (time > 0.01f)
	{
		BackG1.x++;
		BackG2.x++;
		if (BackG1.x >= WINSIZE_MAP_X)
		{
			BackG1.x = -WINSIZE_MAP_X;
		}
		if (BackG2.x >= WINSIZE_MAP_X)
		{
			BackG2.x = -WINSIZE_MAP_X;
		}
		time = 0;
	}
	if (PlayerButton)
		PlayerButton->Update();

	//if (OptoinsButton)
	//	OptoinsButton->Update();

	if (MapToolButton)
		MapToolButton->Update();

	if (EixtButton)
		EixtButton->Update();
}

void TitleScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_MAP_X, WINSIZE_MAP_Y, BLACKNESS);

	if (img)
	{
		img->Render(hdc, BackG1.x, BackG1.y);
		img->Render(hdc, BackG2.x, BackG2.y);
	}

	if (imgLogo)
		imgLogo->Render(hdc, 440, 20);

	if (PlayerButton)
		PlayerButton->Render(hdc);

	/*if (OptoinsButton)
		OptoinsButton->Render(hdc);*/

	if (MapToolButton)
		MapToolButton->Render(hdc);

	if (EixtButton)
		EixtButton->Render(hdc);
}
