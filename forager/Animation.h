#pragma once
#include "pch.h"

class Animation
{
private:
	vector<POINT> vecFrameList;		// key Frame 위치 리스트
	vector<int> vecPlayList;		// 플레이 리스트

	int frameCount;		// 전체 프레임 수
	int frameHeight;	// 프레임 세로 크기
	int frameWidth;		// 프레임 가로 크기

	bool isLoop;		// 반복 되는지 여부
	int nowPlayIdx;		// 현재 플레이 중인 프레임 인덱스
	bool isPlaying;		// 현재 플레이 중인지 여부

	float keyFrameUpdateTime;	// 업데이트 기준 시간
	float accumulateTime;		// 누적 시간

public:
	HRESULT Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight);
	void SetPlayFrame(bool isLoop = false, bool isReverse = false);
	void SetPlayFrame(int startFrame, int endFrame, bool isLoop = false, bool isReverse = false);
	void SetPlayFrame(int* arr, int arrLength, bool isLoop = false, bool isReverse = false);
	void SetStopFrame(int frame);
	void UpdateFrame();

	void Start();
	void Stop();
	void Pause();
	void Resume();
	
	//Get
	POINT GetFramePoint() {
		return vecFrameList[vecPlayList[nowPlayIdx]];
	}

	bool GetIsPlaying() { return this->isPlaying; }
	int GetNowPlayIdx() { return nowPlayIdx; }

	//Set
	void SetKeyFrameUpdateTime(float time) { keyFrameUpdateTime = time; }


	Animation();
	~Animation();
};

