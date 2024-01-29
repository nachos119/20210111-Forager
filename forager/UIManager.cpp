#include "UIManager.h"
#include "Animation.h"
#include "Image.h"
#include "Player.h"
#include "Menu.h"

HRESULT UIManager::Init()
{
	return E_NOTIMPL;
}

void UIManager::Release()
{
	SAFE_DELETE(lifeAni);
}

void UIManager::Update()
{
	lifeAni->UpdateFrame();
}

void UIManager::Render(HDC hdc)
{
}

HRESULT UIManager::Init(Player * player)
{
	this->player = player;
	PlayerUI();

	return S_OK;
}

void UIManager::Render(HDC hdc, bool menu)
{
	for (int i = 0; i < player->GetTotalLife(); i++)
	{
		if (i < player->GetPLife() - 1)
		{
			life1->Render(hdc, 8 + i * 38, 10);
		}
		else if (i == player->GetPLife() - 1)
		{
			life4->AnimationRender(hdc, 8 + i * 38 + 17, 10 + 15, lifeAni);
		}
		else
		{
			life2->Render(hdc, 8 + i * 38, 10);
			life3->AlphaRender(hdc, 8 + i * 38, 10, 170);
		}
	}


	if (!menu)
	{
		EX->Render(hdc, 240, 5);
		EXBar->Render(hdc, 244, 9, player->GetPEx() * 792 / player->GetMaxEx(), 22);
		LEVEL->Render(hdc, 530, 12);
		if (player->GetPLv() < 10)
			number->FrameRender(hdc, 627, 20, player->GetPLv() % 10, 0);
		else
		{
			number->FrameRender(hdc, 627, 20, player->GetPLv() / 10, 0);
			number->FrameRender(hdc, 641, 20, player->GetPLv() % 10, 0);
		}

		// °æÇèÄ¡
		if (player->GetMaxEx() > 999)
		{
			if (player->GetPEx() > 999)
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() / 100, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 14, 20, player->GetPEx() % 100 / 10, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 28, 20, player->GetPEx() % 10, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 42, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f + 42, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f + 42, 20, player->GetMaxEx() / 1000, 0);//
				number->FrameRender(hdc, ParPos.x + 38.5f + 56, 20, player->GetMaxEx() % 1000 / 100, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f + 56, 20, player->GetMaxEx() % 1000 % 100 / 10, 0);
				number->FrameRender(hdc, ParPos.x + 52.5f + 60, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63 + 60, 20, 1, 0);
			}
			else if (player->GetPEx() > 99)
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() / 100, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 14, 20, player->GetPEx() % 100 / 10, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 28, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f + 28, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f + 28, 20, player->GetMaxEx() / 1000, 0);//
				number->FrameRender(hdc, ParPos.x + 38.5f + 42, 20, player->GetMaxEx() % 1000 / 100, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f + 42, 20, player->GetMaxEx() % 1000 % 100 / 10, 0);
				number->FrameRender(hdc, ParPos.x + 52.5f + 56, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63 + 56, 20, 1, 0);
			}
			else if (player->GetPEx() > 9)
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() / 10, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 14, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f + 14, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f + 14, 20, player->GetMaxEx() / 1000, 0);//
				number->FrameRender(hdc, ParPos.x + 38.5f + 28, 20, player->GetMaxEx() % 1000 / 100, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f + 28, 20, player->GetMaxEx() % 1000 % 100 / 10, 0);
				number->FrameRender(hdc, ParPos.x + 52.5f + 42, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63 + 42, 20, 1, 0);
			}
			else
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f, 20, player->GetMaxEx() / 1000, 0);//
				number->FrameRender(hdc, ParPos.x + 38.5f + 14, 20, player->GetMaxEx() % 1000 / 100, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f + 14, 20, player->GetMaxEx() % 1000 % 100 / 10, 0);
				number->FrameRender(hdc, ParPos.x + 52.5f + 28, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63 + 28, 20, 1, 0);
			}
		}
		else if (player->GetMaxEx() > 99)
		{
			if (player->GetPEx() > 99)
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() / 100, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 14, 20, player->GetPEx() % 100 / 10, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 28, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f + 28, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f + 28, 20, player->GetMaxEx() / 100, 0);//
				number->FrameRender(hdc, ParPos.x + 38.5f + 42, 20, player->GetMaxEx() % 100 / 10, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f + 42, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63 + 42, 20, 1, 0);
			}
			else if (player->GetPEx() > 9)
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() / 10, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 14, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f + 14, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f + 14, 20, player->GetMaxEx() / 100, 0);//
				number->FrameRender(hdc, ParPos.x + 38.5f + 28, 20, player->GetMaxEx() % 100 / 10, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f + 28, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63 + 28, 20, 1, 0);
			}
			else
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f, 20, player->GetMaxEx() / 100, 0);//
				number->FrameRender(hdc, ParPos.x + 38.5f + 14, 20, player->GetMaxEx() % 100 / 10, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f + 14, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63 + 14, 20, 1, 0);
			}
		}
		else
		{
			if (player->GetPEx() > 9)
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() / 10, 0); //+ 7
				number->FrameRender(hdc, ParPos.x + 12.5f + 14, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f + 14, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f + 14, 20, player->GetMaxEx() / 10, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f + 14, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63 + 14, 20, 1, 0);
			}
			else
			{
				Par->FrameRender(hdc, ParPos.x, 20, 0, 0);//4.5f
				number->FrameRender(hdc, ParPos.x + 12.5f, 20, player->GetPEx() % 10, 0); //+ 7
				slush->FrameRender(hdc, ParPos.x + 25.5f, 20, 0, 0);//+6
				number->FrameRender(hdc, ParPos.x + 38.5f, 20, player->GetMaxEx() / 10, 0);//
				number->FrameRender(hdc, ParPos.x + 52.5f, 20, player->GetMaxEx() % 10, 0);
				Par->FrameRender(hdc, ParPos.x + 63, 20, 1, 0);
			}
		}
	}

	Sta->Render(hdc, 9, 47);
	StaBar->Render(hdc, 13, 51, (player->GetPSt() * 66 / player->GetMaxSt()), 18);

}

void UIManager::PlayerUI()
{
	life1 = ImageManager::GetSingleton()->FindImage("life1");
	life2 = ImageManager::GetSingleton()->FindImage("life2");
	life3 = ImageManager::GetSingleton()->FindImage("life3");
	life4 = ImageManager::GetSingleton()->FindImage("lifeMove");
	lifeAni = new Animation();
	lifeAni->Init(life4->GetWidth(), life4->GetHeight(), life4->GetFrameWidth(), life4->GetFrameHeight());
	lifeAni->SetPlayFrame(true, true);
	lifeAni->SetKeyFrameUpdateTime(0.1f);
	lifeAni->Start();

	EX = ImageManager::GetSingleton()->FindImage("EX1");
	EXBar = ImageManager::GetSingleton()->FindImage("EX2");
	Sta = ImageManager::GetSingleton()->FindImage("Sta1");
	StaBar = ImageManager::GetSingleton()->FindImage("Sta2");

	EXBarMax.x = 10;
	StaBarMax.x = 66;

	LEVEL = ImageManager::GetSingleton()->FindImage("LEVEL");
	Par = ImageManager::GetSingleton()->FindImage("Par");
	number = ImageManager::GetSingleton()->FindImage("number");
	slush = ImageManager::GetSingleton()->FindImage("slush");
	ParPos.x = 660;
}
