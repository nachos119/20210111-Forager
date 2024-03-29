#pragma once
#include "pch.h"
#include "Singleton.h"

// FMOD 관련
#pragma comment (lib, "lib/fmodex_vc.lib")//32비트 프로그램에는 64비트 라이브러리를 쓰지말자
#include "inc/fmod.hpp"

using namespace FMOD;

#define SOUNDBUFFER		10

class SoundManager : public Singleton<SoundManager>
{
private:
	System* system;		// FMOD 라이브러리 제어
	Sound** sounds;		// 음원
	Channel** channels;	// 출력 사운드 관리

	map<string, Sound**>	mapSoundData;

public:
	SoundManager();
	virtual ~SoundManager() {};

	HRESULT	Init();
	void Release();
	void Update();

	void AddSound(string key, string fileName, bool isBGM = false, bool isLoop = false);
	void Play(string key, float volume = 1.0f);		// 0.0f ~ 1.0f
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
};

