#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Tile.h"
#include "CollisionManager.h"
#include "Menu.h"

HRESULT Player::Init()
{
	PStand = ImageManager::GetSingleton()->FindImage("PlayerStand");
	PRun = ImageManager::GetSingleton()->FindImage("PlayerRun");
	PRoll = ImageManager::GetSingleton()->FindImage("PlayerRoll");
	PAttack = ImageManager::GetSingleton()->FindImage("PlayerAttack");
	PARoll = ImageManager::GetSingleton()->FindImage("PlayerARoll");

	PState = STATE::STAND;

	StandAni = new Animation();
	StandAni->Init(PStand->GetWidth(), PStand->GetHeight(), PStand->GetFrameWidth(), PStand->GetFrameHeight());
	StandAni->SetPlayFrame(0, 9, true, true);
	StandAni->SetKeyFrameUpdateTime(0.025f);
	StandAni->Start();

	RunAni = new Animation();
	RunAni->Init(PRun->GetWidth(), PRun->GetHeight(), PRun->GetFrameWidth(), PRun->GetFrameHeight());
	RunAni->SetPlayFrame(0, 7, true, false);
	RunAni->SetKeyFrameUpdateTime(0.06f);
	RunAni->Start();

	RollAni = new Animation();
	RollAni->Init(PRoll->GetWidth(), PRoll->GetHeight(), PRoll->GetFrameWidth(), PRoll->GetFrameHeight());
	RollAni->SetPlayFrame(0, 9, false, false);
	RollAni->SetKeyFrameUpdateTime(0.05f);

	AttackAni = new Animation();
	AttackAni->Init(PAttack->GetWidth(), PAttack->GetHeight(), PAttack->GetFrameWidth(), PAttack->GetFrameHeight());
	AttackAni->SetPlayFrame(0, 5, true, false);
	AttackAni->SetKeyFrameUpdateTime(0.1f);

	ARollAni = new Animation();
	ARollAni->Init(PARoll->GetWidth(), PARoll->GetHeight(), PARoll->GetFrameWidth(), PARoll->GetFrameHeight());
	ARollAni->SetPlayFrame(0, 9, false, false);
	ARollAni->SetKeyFrameUpdateTime(0.05f);

	Mouse = false;
	roll = false;
	rollTimer = 0;
	Stamina = 700;
	checkLife = 0;

	// µ·
	gold = 0;

	pos.x = MAP_CENTER;
	pos.y = MAP_CENTER;

	PlayerLv = 1;
	PlayerEx = 0;
	PlayerMaxEx = 80;
	PlayerSt = 66;
	PlayerMaxSt = 66;
	PlayerTotalLife = 3;
	PlayerLife = 3;
	speed = 300.0f;
	scaledSpeed = 0;

	//frc = { pos.x - 13, pos.y + 6, pos.x + 13, pos.y + 25 };
	rc = { (LONG)pos.x - 13, (LONG)pos.y + 6, (LONG)pos.x + 13, (LONG)pos.y + 25 };
	tempRc = { 0, 0, 0, 0 };

	return S_OK;
}

void Player::Release()
{
	SAFE_DELETE(StandAni);
	SAFE_DELETE(RunAni);
	SAFE_DELETE(RollAni);
	SAFE_DELETE(AttackAni);
}

void Player::Update()
{
}

void Player::Render(HDC hdc, float X, float Y)
{
	if (PState == STATE::STAND)
	{
		PStand->AnimationRender(hdc, rc.left - X + 13, rc.top - Y - 6, StandAni);
		PAttack->AnimationRender(hdc, rc.left - X + 13, rc.top - Y - 6, AttackAni);
	}
	else if (PState == STATE::RUN)
	{
		PRun->AnimationRender(hdc, rc.left - X + 13, rc.top - Y - 6, RunAni);
		PAttack->AnimationRender(hdc, rc.left - X + 13, rc.top - Y - 6, AttackAni);
	}
	else if (PState == STATE::ROLL)
	{
		PRoll->AnimationRender(hdc, rc.left - X + 13, rc.top - Y - 6, RollAni);
		PARoll->AnimationRender(hdc, rc.left - X + 13, rc.top - Y - 6, ARollAni);
	}
	HBRUSH NULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, NULLBrush);
	//Rectangle(hdc, frc.left - X, frc.top - Y, frc.right - X, frc.bottom - Y);
	// Rectangle(hdc, rc.left - X, rc.top - Y, rc.right - X, rc.bottom - Y);
	SelectObject(hdc, oldBrush);

}

void Player::Render(HDC hdc, int X, int Y, int MoveX, int MoveY, int half)
{
	int XX = pos.x / (TILE_SIZE);
	int YY = pos.y / (TILE_SIZE);
	int i = XX - X;
	int j = YY - Y;

	PStand->AnimationRender(hdc, i*(TILE_SIZE / 2) - MoveX + 30,
		j *(TILE_SIZE / 2) - MoveY + 26, half, StandAni);

}

void Player::Update(bool menu)
{
	//frc = { pos.x - 13, pos.y + 6, pos.x + 13, pos.y + 25 };
	if (!menu)
	{
		rc = { (LONG)pos.x - 13, (LONG)pos.y + 6, (LONG)pos.x + 13, (LONG)pos.y + 25 };

		LEVELUP();
		if (Stamina <= 0)
		{
			PlayerSt--;
			Stamina = 500;
		}
		if (PlayerSt < 0)
		{
			if (checkLife < 5)
			{
				checkLife++;
				PlayerSt = 0;
			}
			else
			{
				checkLife = 0;
				PlayerSt = PlayerMaxSt / 2;
				PlayerLife--;
			}
		}

		scaledSpeed = this->speed * TimerManager::GetSingleton()->GetElapsedTime();
		if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_W))
		{
			int leftIdX = ((int)(rc.left) / TILE_SIZE);
			int leftIdY = ((int)(rc.top - scaledSpeed) / TILE_SIZE) * WINSIZE_TILE_MAP;
			int rightIdX = ((int)(rc.right) / TILE_SIZE);
			int rightIdY = ((int)(rc.top - scaledSpeed) / TILE_SIZE) * WINSIZE_TILE_MAP;

			if (tileInfo[leftIdX + leftIdY].terrain != TERRAIN::LAND
				|| tileInfo[rightIdX + rightIdY].terrain != TERRAIN::LAND) {
				if (PState != STATE::ROLL)
					PState = STATE::STAND;
			}
			else
			{
				tempRc = { (LONG)pos.x - 13, (LONG)(pos.y + 6 - scaledSpeed), (LONG)pos.x + 13, (LONG)pos.y + 25 };
				if (Collision->CheckCollision(tempRc))
				{
				}
				else
				{
					Stamina--;
					Run();
					pos.y -= scaledSpeed;
				}
			}
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_A))
		{
			int topIdX = ((int)(rc.left - scaledSpeed) / TILE_SIZE);
			int topIdY = ((int)rc.top / TILE_SIZE) * WINSIZE_TILE_MAP;
			int bottomIdX = ((int)(rc.left - scaledSpeed) / TILE_SIZE);
			int bottomIdY = ((int)rc.bottom / TILE_SIZE) * WINSIZE_TILE_MAP;

			if (tileInfo[topIdX + topIdY].terrain != TERRAIN::LAND
				|| tileInfo[bottomIdX + bottomIdY].terrain != TERRAIN::LAND) {
				if (PState != STATE::ROLL)
					PState = STATE::STAND;
			}
			else
			{
				tempRc = { (LONG)(pos.x - 13 - scaledSpeed), (LONG)pos.y + 6, (LONG)pos.x + 13, (LONG)pos.y + 25 };
				if (Collision->CheckCollision(tempRc))
				{
				}
				else
				{
					Stamina--;
					Run();
					pos.x -= scaledSpeed;
				}
			}
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_S))
		{
			int leftIdX = ((int)rc.left / TILE_SIZE);
			int leftIdY = ((int)ceil(rc.bottom + scaledSpeed) / TILE_SIZE) * WINSIZE_TILE_MAP;
			int rightIdX = ((int)rc.right / TILE_SIZE);
			int rightIdY = ((int)ceil(rc.bottom + scaledSpeed) / TILE_SIZE) * WINSIZE_TILE_MAP;

			if (tileInfo[leftIdX + leftIdY].terrain != TERRAIN::LAND
				|| tileInfo[rightIdX + rightIdY].terrain != TERRAIN::LAND) {
				if (PState != STATE::ROLL)
					PState = STATE::STAND;
				//if (rc.left <= ((int)rc.left / TILE_SIZE) * TILE_SIZE)
				//{
				//	if (tileInfo[((int)(rc.bottom) / TILE_SIZE) * WINSIZE_TILE_MAP + ((int)(rc.right + scaledSpeed) / TILE_SIZE)].terrain == TERRAIN::LAND)
				//		pos.x += scaledSpeed;
				//}
				//else if (rc.right >= ((int)rc.right / TILE_SIZE) * TILE_SIZE)
				//{
				//	if (tileInfo[((int)(rc.bottom) / TILE_SIZE) * WINSIZE_TILE_MAP + ((int)(rc.left - scaledSpeed) / TILE_SIZE)].terrain == TERRAIN::LAND)
				//		pos.x -= scaledSpeed;
				//}
			}
			else
			{
				tempRc = { (LONG)pos.x - 13, (LONG)pos.y + 6, (LONG)pos.x + 13, (LONG)(pos.y + 25 + scaledSpeed) };
				if (Collision->CheckCollision(tempRc))
				{
				}
				else
				{
					Stamina--;
					Run();
					pos.y += scaledSpeed;
				}
			}
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_D))
		{
			int topIdX = ((int)ceil(rc.right + scaledSpeed) / TILE_SIZE);
			int topIdY = ((int)rc.top / TILE_SIZE) * WINSIZE_TILE_MAP;
			int bottomIdX = ((int)ceil(rc.right + scaledSpeed) / TILE_SIZE);
			int bottomIdY = ((int)rc.bottom / TILE_SIZE) * WINSIZE_TILE_MAP;

			if (tileInfo[topIdY + topIdX].terrain != TERRAIN::LAND
				|| tileInfo[bottomIdX + bottomIdY].terrain != TERRAIN::LAND) {
				if (PState != STATE::ROLL)
					PState = STATE::STAND;
			}
			else
			{
				tempRc = { (LONG)pos.x - 13, (LONG)pos.y + 6, (LONG)(pos.x + 13 + scaledSpeed), (LONG)pos.y + 25 };
				if (Collision->CheckCollision(tempRc))
				{
				}
				else
				{
					Stamina--;
					Run();
					pos.x += scaledSpeed;
				}
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(KEY_W))
		{
			Stand();
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(KEY_A))
		{
			Stand();
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(KEY_S))
		{
			Stand();
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(KEY_D))
		{
			Stand();
		}
		if (!roll)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				if (AttackAni->GetIsPlaying() == false)
					AttackAni->Start();
			}
			if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
			{
				AttackAni->Stop();
			}
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
			{
				if (PState != STATE::ROLL)
				{
					speed = 500.0f;
					RollAni->Start();
					ARollAni->Start();
					AttackAni->Stop();
					tempState = PState;
					PState = STATE::ROLL;
					roll = true;
				}
			}
		}
		else if (roll)
		{
			rollTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (rollTimer >= 0.5f)
			{
				if (speed > 300.0f)
				{
					speed = 300.0f;
					PState = STATE::STAND;
				}
				if (rollTimer >= 0.9f)
				{
					rollTimer = 0;
					roll = false;
				}
			}
		}

		if (Mouse)
		{
			if (g_ptMouse.x > PLAYER_CENTER_X)
			{
				SetAni(Mouse);
				Mouse = false;
			}
		}
		else if (!Mouse)
		{
			if (g_ptMouse.x < PLAYER_CENTER_X)
			{
				SetAni(Mouse);
				Mouse = true;
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(0x31))
		{
			PlayerEx += 10;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(0x32))
		{
			PlayerSt++;
			if (PlayerSt > PlayerMaxSt)
			{
				PlayerSt = PlayerMaxSt;
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(0x33))
		{
			gold += 1000;
		}
	}

	if (PState == STATE::STAND)
	{
		StandAni->UpdateFrame();
	}
	if (PState == STATE::RUN)
	{
		RunAni->UpdateFrame();
	}
	if (PState == STATE::ROLL)
	{
		RollAni->UpdateFrame();
	}

	ARollAni->UpdateFrame();
	AttackAni->UpdateFrame();

}

void Player::Run()
{
	if (!roll)
	{
		if (PState != STATE::RUN)
			PState = STATE::RUN;
	}
}

void Player::Stand()
{
	if (!roll)
	{
		if (PState != STATE::STAND)
			PState = STATE::STAND;
	}
}

void Player::SetBerry(int num)
{
	if (inven.find(BERRY) == inven.end())
	{
	}
	else
	{
		PlayerSt += 2;
		if (PlayerSt >= 66)
		{
			PlayerSt = 66;
		}
		inven.find(BERRY)->second--;
		if (inven.find(BERRY)->second <= 0)
		{
			inven.erase(BERRY);
		}
	}
}

void Player::SetCitrus(int num)
{
	if (inven.find(SHIP) == inven.end())
	{
	}
	else
	{
		PlayerSt += 4;
		if (PlayerSt >= 66)
		{
			PlayerSt = 66;
		}
		inven.find(SHIP)->second--;
		if (inven.find(SHIP)->second <= 0)
		{
			inven.erase(SHIP);
		}
	}
}

void Player::SetAni(bool set)
{
	if (set)
	{
		StandAni->SetPlayFrame(0, 9, true, true);
		RunAni->SetPlayFrame(0, 7, true, true);
		RollAni->SetPlayFrame(0, 9, false, false);
		AttackAni->SetPlayFrame(0, 5, true, false);
		ARollAni->SetPlayFrame(0, 9, false, false);
	}
	else if (!set)
	{
		StandAni->SetPlayFrame(10, 19, true, true);
		RunAni->SetPlayFrame(8, 15, true, true);
		RollAni->SetPlayFrame(10, 19, false, false);
		AttackAni->SetPlayFrame(6, 11, true, false);
		ARollAni->SetPlayFrame(10, 19, false, false);
	}
}

void Player::invenIt(OBJEKRESULT objj)
{
	if (inven.find(objj) == inven.end())
	{
		inven.insert(make_pair(objj, 1));
	}
	else
	{
		inven.find(objj)->second++;
	}
}

void Player::LEVELUP()
{
	if (PlayerEx >= PlayerMaxEx)
	{
		PlayerEx = PlayerEx - PlayerMaxEx;
		PlayerMaxEx += (10 + (2 * PlayerLv));
		PlayerLv++;
	}
}

