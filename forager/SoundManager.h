#pragma once
#include "pch.h"
#include "Singleton.h"

// FMOD ����
#pragma comment (lib, "lib/fmodex_vc.lib")//32��Ʈ ���α׷����� 64��Ʈ ���̺귯���� ��������
#include "inc/fmod.hpp"

using namespace FMOD;

#define SOUNDBUFFER		10

class SoundManager : public Singleton<SoundManager>
{
private:
	System* system;		// FMOD ���̺귯�� ����
	Sound** sounds;		// ����
	Channel** channels;	// ��� ���� ����

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

