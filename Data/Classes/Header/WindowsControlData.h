#pragma once
#include "Pch.h"

class WindowsControlData
{
	bool EndState = false;
	int CurrentWindows = 0;
	float MusicVolume; //21
	bool GameStarted; //22
	bool Pause; //23
public:
	bool IsPause();
	bool IsStarted();
	void Resume();
	void PauseGame();
	void Restart();
	void StartGame();
	float GetMusicVolume();
	void SetMusicVolume(float input);
	int GetWindow();
	void SetWindow(int input);
	void Init();
	bool GetEndState();
	void SetEndState(bool input);
};

